#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    const string letterMap[10] = {
        "",
        "",
        "abc",
        "def", 
        "ghi", 
        "jkl", 
        "mno", 
        "pqrs", 
        "tuv", 
        "wxyz", 
    };
    vector<string> result;
    string s;
    void backtracking(const string &digits, int index) {
        if (index == digits.size()) {
            result.push_back(s);
            return;
        }
        int digit = digits[index] - '0';
        string letter = letterMap[digit];
        for (int i = 0; i < letter.size(); i++) {
            s.push_back(letter[i]);
            backtracking(digits, index + 1);
            s.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        s.clear();
        result.clear();
        if (digits.size() == 0) {
            return result;
        }
        backtracking(digits, 0);
        return result;
    }
};

int main() {
    Solution s;
    string digits = "34";
    vector<string> ans = s.letterCombinations(digits);
}