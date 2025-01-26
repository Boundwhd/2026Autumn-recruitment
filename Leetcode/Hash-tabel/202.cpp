/*快乐数*/

#include "../leetcode.h"

bool isHappy(int n) {
    unordered_set<int> seen;
    while (n != 1) {
        n = getnum(n);
        if (seen.count(n)) return false;
        seen.insert(n);
    }
    return true;
}

int getnum(int num) {
    int sum = 0;
    while (num) {
        int digit = num % 10;
        sum += digit * digit;
        num /= 10;
    }
    return sum;
}


/*使用unorder_set记录重复数字*/