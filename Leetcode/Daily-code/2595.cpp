/*奇偶位数*/
#include "../leetcode.h"

vector<int> evenOddBit(int n) {
    vector<int> result(2, 0);
    int i = 0;
    while (n > 0) {
        int remain = n % 2;
        result[i] += remain;
        n /= 2;
        i = (i == 0) ? 1 : 0;
    }
    return result;
}


int main(){
    int n = 50;
    vector<int> ans = evenOddBit(n);
    return 0;
}