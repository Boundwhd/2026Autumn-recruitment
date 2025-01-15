/*Z字形变换*/
#include "../leetcode.h"

string convert(string s, int numRows) {
        if (numRows == 1 || s.length() <= numRows) {
        return s; // 特殊情况，直接返回原字符串
    }

    vector<string> rows(min(numRows, (int)s.length())); // 创建 numRows 个字符串
    int currRow = 0; // 当前行
    bool goingDown = false; // 当前方向（是否向下）

    for (char c : s) {
        rows[currRow] += c; // 将字符添加到当前行
        if (currRow == 0 || currRow == numRows - 1) {
            goingDown = !goingDown; // 到达顶部或底部，改变方向
        }
        currRow += goingDown ? 1 : -1; // 根据方向移动到下一行
    }

    // 拼接所有行，生成最终结果
    string result;
    for (string row : rows) {
        result += row;
    }
    return result;
}

/*
特殊情况处理：

如果 numRows == 1 或字符串长度小于等于行数，直接返回原字符串，因为无需进行 Z 字形排列。
使用 rows 存储每一行的字符：

rows 是一个字符串向量，每个元素表示 Z 字形中一行的内容。
字符遍历：

遍历字符串时，根据当前行和方向决定字符添加到哪一行，并更新行号和方向。
拼接结果：

将 rows 中的所有行拼接起来，得到最终的 Z 字形字符串。
*/