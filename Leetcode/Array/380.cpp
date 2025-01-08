/*O(1)时间插入删除和获取随机元素*/
#include "leetcode.h"

class RandomizedSet {
    unordered_map<int, int> hash;
    vector<int> nums;
public:
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        if(hash.count(val)){
            return false;
        }else{
            nums.push_back(val);
            hash[val] = nums.size() - 1;
            return true;
        }
    }
    
    bool remove(int val) {
        if(hash.count(val)){
            int index = hash[val];
            int last_element = nums.back();
            nums[index] = last_element;
            hash[last_element] = index;
            hash.erase(val);
            nums.pop_back();
            return true;
        }else{
            return false;
        }
    }
    
    int getRandom() {
        int rand_num = rand() % nums.size();
        return nums[rand_num];
    }
};

/*通过哈希表快速定位元素是否存在数组内，哈希表值是每个键在数组中的位置，方便删除。
删除采用，把他换成数组中最后元素，删除最后的元素*/