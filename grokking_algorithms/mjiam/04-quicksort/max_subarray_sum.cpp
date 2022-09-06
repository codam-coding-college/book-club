#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Problem:
// Given an integer array, find the maximum sum among all subarrays possible.

// Divide and Conquer solution:
// Divide the array into two equal subarrays.
// Recursively calculate the maximum subarray sum for the left subarray,
// Recursively calculate the maximum subarray sum for the right subarray,
// Find the maximum subarray sum that crosses the middle element.
// Return the maximum of the above three sums.

// Finds maximum sum of elements in nums (including mid element).
int findMaxCrossingSum(vector<int> nums, int first_index, int last_index,
                       int mid_index) {
  // finding biggest sum in left subarray (including mid element)
  int sum = 0;
  int left_max = INT32_MIN;
  for (int i = mid_index; i >= first_index; i--) {
    sum += nums[i];
    if (sum > left_max)
      left_max = sum;
  }

  // finding biggest sum in right subarray (excl. mid)
  sum = 0;
  int right_max = INT32_MIN;
  for (int i = mid_index + 1; i <= last_index; i++) {
    sum += nums[i];
    if (sum > right_max)
      right_max = sum;
  }

  return (left_max + right_max);
}

// Recursive summing of left and right subarrays.
int findMaxSum(vector<int> nums, int first_index, int last_index) {
  // base case
  if (first_index == last_index)
    return nums[first_index];

  int mid = (first_index + last_index) / 2;

  int max_left_right = max(findMaxSum(nums, first_index, mid),
                           findMaxSum(nums, mid + 1, last_index));

  return max(max_left_right,
             findMaxCrossingSum(nums, first_index, last_index, mid));
}

int main() {
  vector<int> nums = {2, -4, 1, 9, -6, 7, -3}; // 11
  // vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4}; // 6

  int max_sum = findMaxSum(nums, 0, nums.size() - 1);
  cout << "Max sum is: " << max_sum << endl;
}
