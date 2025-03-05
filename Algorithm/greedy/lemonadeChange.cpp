#include <vector>
using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int remain_5 = 0;
        int remain_10 = 0;
        for (int i = 0; i < bills.size(); i++) {
            if (bills[i] == 5) {
                remain_5++;
            } else if (bills[i] == 10) {
                if (remain_5 == 0) return false;
                else {
                    remain_5--;
                    remain_10++;
                }
            } else {
                if (remain_5 >= 1 && remain_10 >= 1) {
                    remain_5 -= 1;
                    remain_10 -= 1;
                } else if (remain_5 >= 3) {
                    remain_5 -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};