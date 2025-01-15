/*整数转罗马数字*/
#include "../leetcode.h"

string intToRoman(int num) {
    vector<pair<int, string>> roman_symbols = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"},
        {1, "I"}
    };

    string ans = "";
    for(const auto& [value, symbol] : roman_symbols){
        while(num >= value){
            ans += symbol;
            num -= value;
        }
    }
    return ans;
}