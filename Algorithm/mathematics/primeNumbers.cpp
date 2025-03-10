/**
 * @brief 欧拉筛法
 * 一个合数只用它最小的质因数筛去
 */

#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<int> Prime(int n) {
    bool flag[n + 1];   //标记数组，flag[i] == 0表示i为素数，flag[i] == 1表示i为合数
    memset(flag, 0, sizeof(flag));
    vector<int> prime;
    int cnt = 0;    //素数个数
    for (int i = 2; i <= n; i++) {
        if (!flag[i]) {
            prime.push_back(i);
            cnt++;
        }

        for (int j = 0; j < cnt; ++j) {
            if (i * prime[j] > n) break;
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    return prime;
}


int main () {
    int n = 10;
    bool flag[n + 1];
    cout << sizeof(flag) << endl;
    cout << "Enter the range:" << endl;
    cin >> n;
    if (n < 0) {
        cout << "Wrong input!" << endl;
        return 0;
    }

    vector<int> prime = Prime(n);
    int cnt = prime.size();
    cout << "The number of prime numbers is:" << cnt << endl;
    return 0;
}
