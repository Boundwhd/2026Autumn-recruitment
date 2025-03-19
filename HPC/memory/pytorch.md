## 自制 Pytorch 显存管理机制

#### 1. Block
- 管理内存块的基本单位，用于分配、释放内存块
- 内部维护 ptr, size, allocated, prev, next 成员变量

#### 2. BlockPool
- 用 set 存储 Block的指针，按照 (block->size, addr) 的大小顺序进行排列。
- 存放在 BlockPool 中的 Block 都是空闲的
- 维护两种 BlockPool: 用于加速合适块的查找
    - <1MB small BlockPool
    - >1MB large BlockPool

#### 3. Malloc
1. 根据请求 size 决定实际上的 alloc_size
    - 请求的 size 转换为最小单元的整数倍
    - 为小于 1MB 的 size 分配 2MB
    - 为 1M - 10MB 的 size 分配 20MB
    - 为 $>=$ 10MB 的 size 分配向上取整到2MB的整数倍 

2. 找到内存池中最合适的块
    - 以 log(n) 的时间复杂度找到第一个大于 size 的块
    - 将这个块从 BlockPool 中移除
    - 切分：
        1. 计算给出这个 Block 后的内存碎片大小
        2. 如果剩余内存大小大于最小单位 512KB 则需要切分。
        3. 创建一个 remaining 块，与当前 Block 组织进双双向链表 (以O(1)的时间复杂度查找到与当前块连续的空闲的显存地址并合并)
        4. 将 remaining 块加入正确的内存池中
        5. 将申请到的 block 加入到 Activated pool 中
    
3. 内存池中找不到合适的块
    1. 按照 alloc_size 分配显存
    2. 若显存不够，则一次性释放所有内存池中的显存，再次分配显存
    3. 由于 alloc_size 一般大于 size, 进行切分，Block 组织进双向链表

#### 4. Free
1. 忙碌显存池 ActivatedPool 使用 unordered_map 封装, 在 O(1) 时间复杂度内找到封装地址的 Block
2. 将 Block 中的 allocated 成员置为 False
3. 删除忙碌显存池中的 Block
4. 尝试在 BlockPool 中合并空闲连续地址，得到空闲的大显存块
    - 双向链表前后 while 合并