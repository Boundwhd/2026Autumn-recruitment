/*分发糖果*/
#include "../leetcode.h"

int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n == 0) return 0;

        vector<int> candies(n, 1);

        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }

        int totalCandies = 0;
        for (int i = 0; i < n; i++) {
            totalCandies += candies[i];
        }

        return totalCandies;
    }


/*正向遍历：
从左到右遍历，如果当前孩子的评分大于前一个孩子，则当前孩子的糖果数应为前一个孩子糖果数 + 1。

反向遍历：
从右到左遍历，如果当前孩子的评分大于后一个孩子，则当前孩子的糖果数应为 max(当前糖果数, 后一个孩子糖果数 + 1)，
这是因为糖果数可能已经在正向遍历时增加过。

总糖果数：
最后，所有孩子的糖果数之和即为所需的最小糖果数。
*/