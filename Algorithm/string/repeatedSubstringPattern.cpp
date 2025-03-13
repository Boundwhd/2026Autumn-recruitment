#include <string>
using namespace std;

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        string double_ss = s + s;
        double_ss.erase(double_ss.begin());
        double_ss.erase(double_ss.end()-1);
        return double_ss.find(s) != std::string::npos;
    }
};