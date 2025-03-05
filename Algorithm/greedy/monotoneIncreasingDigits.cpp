#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string S = to_string(n);
        int flag = S.size() - 1;
        for (int i = S.size() - 1; i > 0; i--) {
            if (S[i] < S[i - 1]) {
                flag = i;
                S[i - 1]--;
            }
        }
        for (int i = flag; i < S.size(); i++) {
            S[i] = '9';
        }
        return stoi(S);
    }
};
