#include <vector>
#include <iostream>
using namespace std;

int main() {
    int nums;
    int capacity;
    cout << "Enter the number of goods:";
    cin >> nums;
    cout << "Enter the capacity of bag:";
    cin >> capacity;
    vector<int> weight(nums + 1, 0);
    vector<int> value(nums + 1, 0);
    vector<vector<int>> dp(nums + 1, vector<int>(capacity + 1, 0));
    cout << "Enter the weight of goods:";
    for (int i = 1; i <= nums; i++) {
        cin >> weight[i];
    }
    cout << "Enter the value of goods:";
    for (int i = 1; i <= nums; i++) {
        cin >> value[i];
    }

    for (int i = 1; i <= nums; i++) {
        for (int j = 1; j <= capacity; j++) {
            if (weight[i] > j) {
                dp[i][j] = dp[i-1][j];
            } else {
                int remain_weight = j - weight[i];
                dp[i][j] = max(dp[i-1][j], dp[i-1][remain_weight] + value[i]); 
            }
        }
    }
    cout<< "Best value:" << dp[nums][capacity] << endl;
    return 0;
}