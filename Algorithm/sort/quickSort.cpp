/**
 * 快速排序
 * 时间复杂度：最好情况O(nlogn) 最坏情况O(n^2)
 */
#include <vector>
#include <iostream>
using namespace std;


void quickSort(vector<int>& nums, int left, int right) {
    if (left >= right) return;
    int temp = nums[left];
    int i = left;
    int j = right;
    while (j > i) {
        while ((j > i) && nums[j] >= temp) {
            j--;
        }
        if (j > i) nums[i] = nums[j];
        while ((j > i) && nums[i] <= temp) {
            i++;
        }
        if (j > i) nums[j] = nums[i];
    }
    nums[i] = temp;
    quickSort(nums, left, i - 1);
    quickSort(nums, i + 1, right);
}


int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of elements!" << endl;
    }

    vector<int> nums(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    quickSort(nums, 0, n - 1);

    cout << "Sorted array: ";
    for (auto number : nums) {
        cout << number << " ";
    }
    cout << endl;

    return 0;
}