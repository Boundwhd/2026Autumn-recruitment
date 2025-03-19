#include <cuda_runtime_api.h>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <mutex>

constexpr size_t kMinBlockSize = 512;
constexpr size_t kSmallSize = 1048576;
constexpr size_t kSmallBuffer = 2097152;
constexpr size_t kLargeBuffer = 20971520;

struct Block {
    void* ptr;
    size_t size;
    bool allocated;
    Block* prev;
    Block* next;

    Block(size_t size, void* ptr) : ptr(ptr), size(size), allocated(false), prev(nullptr), next(nullptr) {}
};

class BlockPool {
public:
    std::set<Block*, bool(*)(Block*, Block*)> blocks;

    static bool CompareBlocks(Block* a, Block* b) {
        if (a->size != b->size) {
            return a->size < b->size;  // 优先按大小升序排列
        }
        return a->ptr < b->ptr;        // 大小相同则按地址排序
    }

    BlockPool() : blocks(CompareBlocks) {}
    

    void insert(Block* block) {
        blocks.insert(block);
    }

    Block* find_best_fit(size_t size) {
        Block key(size, nullptr);
        auto it = blocks.lower_bound(&key);
        return (it != blocks.end() && (*it)->size >= size) ? *it : nullptr;
    }

    void erase(Block* block) {
        blocks.erase(block);
    }
};

class CachingAllocator {
private:
    std::mutex mutex;
    BlockPool small_blocks;
    BlockPool large_blocks;

    std::unordered_map<void*, Block*> allocated_blocks;
    /**
     * 线程安全：std::lock_guard 确保在作用域内对共享资源的访问是线程安全的。
     * 自动管理：无需手动调用 lock() 和 unlock()，避免忘记解锁导致的死锁问题。
     * 作用域限制：std::lock_guard 的生命周期与作用域绑定，离开作用域后自动释放锁。
     */
    void* malloc_impl(size_t size) {
        std::lock_guard<std::mutex> lock(mutex);

        // 确定内存池
        BlockPool& pool = (size <= kSmallSize) ? small_blocks : large_blocks;
        size_t alloc_size = 0;
        
        
        if (size <= kSmallSize) {
            alloc_size = kSmallBuffer;
        } else if (size <= 10 * kSmallSize) {
            alloc_size = kLargeBuffer;
        } else {
            alloc_size = ((size + kSmallBuffer - 1) / kSmallBuffer) * kSmallBuffer;
        }


        if (Block* block = pool.find_best_fit(size)) {
            pool.erase(block);
            return split_block(block, size);
        }

        return allocate_new_block(size, alloc_size);
    }

    void* split_block(Block* block, size_t size) {
        if (block->size - size >= kMinBlockSize) {
            Block* remaining = new Block(block->size - size, static_cast<char*>(block->ptr) + size);

            remaining->prev = block;
            remaining->next = block->next;
            if (block->next) {
                block->next->prev = remaining;
            }
            block->next = remaining;
            block->size = size;

            (remaining->size <= kSmallSize ? small_blocks : large_blocks).insert(remaining);
        }

        block->allocated = true;
        allocated_blocks[block->ptr] = block;
        return block->ptr;
    }

    void* allocate_new_block(size_t req_size, size_t alloc_size) {
        void* ptr;
        cudaError_t err = cudaMalloc(&ptr, alloc_size);

        if (err != cudaSuccess) {
            cudaGetLastError();
            release_cached_memory();
            err = cudaMalloc(&ptr, alloc_size);
            if (err != cudaSuccess) throw std::bad_alloc();
        }
        
        Block* block = new Block(alloc_size, ptr);
        return split_block(block, req_size);
    }

    void release_cached_memory() {
        auto release_pool = [](BlockPool& pool) {
            std::vector<Block*> to_delete;
            for (Block* block : pool.blocks) {
                if (!block->allocated) {
                    cudaFree(block->ptr);
                    to_delete.push_back(block);
                }
            }
            for (Block* block : to_delete) {
                pool.erase(block);
                delete block;
            }
        };
    
        release_pool(small_blocks);
        release_pool(large_blocks);
    }

public:
    void* malloc(size_t size) {
        size = round_size(size);
        return malloc_impl(size);
    }

    void free(void* ptr) {
        std::lock_guard<std::mutex> lock(mutex);
        
        auto it = allocated_blocks.find(ptr);
        if (it == allocated_blocks.end()) return;
        
        Block* block = it->second;
        block->allocated = false;
        allocated_blocks.erase(it);
        
        // 合并相邻空闲块
        merge_blocks(block);
    }

private:
    static size_t round_size(size_t size) {
        if (size < kMinBlockSize) return kMinBlockSize;
        return kMinBlockSize * ((size + kMinBlockSize - 1) / kMinBlockSize);
    }

    void merge_blocks(Block* block) {

        BlockPool& pool = (block->size <= kSmallSize) ? small_blocks : large_blocks;

        while (block->prev && !block->prev->allocated) {
            Block* prev = block->prev;
            pool.erase(prev);  
            pool.erase(block);
            prev->size += block->size;
            prev->next = block->next;
            if (block->next) {
                block->next->prev = prev;
            }
            delete block;
            block = prev;
        }

        while (block->next && !block->next->allocated) {
            Block* next = block->next;
            pool.erase(block); 
            pool.erase(next);
            block->size += next->size;
            block->next = next->next;
            if (next->next) {
                next->next->prev = block;
            }
            delete next;
        }
        
        (block->size <= kSmallSize ? small_blocks : large_blocks).insert(block);
    }
};

static CachingAllocator allocator;

void* cuda_malloc(size_t size) { 
    return allocator.malloc(size); 
}

void cuda_free(void* ptr) { 
    allocator.free(ptr); 
}



int main() {
    std::cout << "Testing CachingAllocator..." << std::endl;

    // 1. 分配多个块，观察分配是否正确
    void* ptr1 = cuda_malloc(3 * 1024 * 1024);  // 3MB
    void* ptr2 = cuda_malloc(6 * 1024 * 1024);  // 6MB
    void* ptr3 = cuda_malloc(12 * 1024 * 1024); // 12MB（大于 10MB，应该向上对齐到 2MB 的倍数）
    void* ptr4 = cuda_malloc(1 * 1024 * 1024);  // 1MB
    
    std::cout << "Allocated blocks:" << std::endl;
    std::cout << "ptr1: " << ptr1 << " (3MB)" << std::endl;
    std::cout << "ptr2: " << ptr2 << " (6MB)" << std::endl;
    std::cout << "ptr3: " << ptr3 << " (12MB)" << std::endl;
    std::cout << "ptr4: " << ptr4 << " (1MB)" << std::endl;
    
    // 2. 释放部分块，观察是否正确回收
    cuda_free(ptr2);  // 释放 6MB
    cuda_free(ptr4);  // 释放 1MB
    std::cout << "Freed ptr2 (6MB) and ptr4 (1MB)" << std::endl;

    // 3. 再次分配，看看是否能重用空闲块
    void* ptr5 = cuda_malloc(2 * 1024 * 1024); // 2MB
    std::cout << "Allocated ptr5: " << ptr5 << " (2MB)" << std::endl;

    // 4. 释放所有分配的内存，测试合并
    cuda_free(ptr1);
    cuda_free(ptr3);
    cuda_free(ptr5);
    std::cout << "Freed all blocks." << std::endl;


    return 0;
}

