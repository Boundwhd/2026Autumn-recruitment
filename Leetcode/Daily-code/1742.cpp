/*盒子中小球的最大数量*/
#include "../leetcode.h"

class Solution {
    public:
        int countBalls(int lowLimit, int highLimit) {
            int result = 0;
            unordered_map<int, int> ht;
            for (int i = lowLimit; i <= highLimit; i++) {
                int box = get_add(i);
                ht[box]++;
            }
    
            for (const auto it : ht) {
                result = max(result, it.second);
            }
            return result;
        }
    
        int get_add(int number) {
            int result = 0;
            while (number) {
                result += number % 10;
                number /= 10;
            }
            return result;
        }
    };