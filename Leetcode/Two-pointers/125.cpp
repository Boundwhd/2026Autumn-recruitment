/*验证回文串*/

#include "../leetcode.h"

bool isPalindrome(string s) {
    if (s.length() == 1) return true;

    int left = 0;
    int right = s.length() - 1;
    while(left < right){
        while(left < right && !isalnum(s[right])) right--;
        while(left < right && !isalnum(s[left])) left++;
        if(left < right){
            if(tolower(s[left]) == tolower(s[right])){
                left++;
                right--;
            }else{
                return false;
            }
        }
    }
    return true;
}

//  ASCLL码（10进制）：A-Z —— 65-90
//                    a-z —— 97-122
//                    0-9 —— 48-57
