/*罗马数字转整数*/
#include "../leetcode.h"

int romanToInt(string s) {
        unordered_map<char, int> romanDict = {
            {'I', 1}, {'V', 5}, {'X', 10},
            {'L', 50}, {'C', 100}, {'D', 500},
            {'M', 1000}
        };
        int total = 0;
        for(int i = 0; i < s.length(); i++){
            if(i + 1 < s.length() && romanDict[s[i]] < romanDict[s[i + 1]]){
                total -= romanDict[s[i]];
            }else{
                total += romanDict[s[i]];
            }
        }
        return total;
    }

/*只需要判断下一个数字是不是比自己大（并且存在下一个数字），如果是，则减去当前数字*/