#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;
class Solution {
private:
    //大的留着 小的出去
    struct cmp {
        bool operator() (pair<int, int> a, pair<int, int> b) {
            return a.second > b.second;
        }
    };
    
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if (nums.size() == 1) return {nums[0]};
        unordered_map<int, int> mapp;
        for (auto i : nums) {
            mapp[i]++;
        }

        priority_queue<pair<int, int>, vector<pair<int,int>>, cmp> max_heap;

        for (auto it = mapp.begin(); it != mapp.end(); it++) {
            max_heap.push(*it);
            if (max_heap.size() > k) {
                max_heap.pop();
            } 
        }

        vector<int> result(k);
        for (int i = k - 1; i >= 0; i--) {
            result[i] = max_heap.top().first;
            max_heap.pop();
        }
        return result;

    }
};