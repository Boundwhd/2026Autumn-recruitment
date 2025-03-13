#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
private:
void getNext(vector<int>& next, const string& s) {
    int j = 0;
    for (int i = 1; i < s.size(); i++) {
        while (j > 0 && s[i] != s[j]) {
            j = next[j - 1];
        }
        if (s[i] == s[j]) j++;
        next[i] = j;
    }
}
public:
    int strStr(string haystack, string needle) {
        vector<int> next(needle.size(), 0);
        getNext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }

            if (haystack[i] == needle[j]) j++;

            if (j == needle.size()) {
                return i - j + 1;
            }
        }
        return -1;
    }
};

int main() {
    const string needle = "aabaaf";

    return 0;
}