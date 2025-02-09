#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

// multi-threaded sorting utility
vector<int> mergesort_multi_thread(const vector<int>& nums);
void thread_sort(const vector<int>& nums, vector<int>& result);

// mergesort 
vector<int> mergesort(const vector<int>& nums);
vector<int> merge(const vector<int>& A, const vector<int>& B);

// debugger
void print(const vector<int>& nums);

int main() {
    vector<int> sorted_res = mergesort({4, 3, 1, 8, 9});
    print(sorted_res);
    return 0;
}

/**
 * Mergesort implementation (recursive divide and conquer)
 */
vector<int> mergesort(const vector<int>& nums) {
    int l = 0, r = nums.size();
    if (r > 1) {
        int m = l + (r - l) / 2;
        vector<int> lower(nums.begin(), nums.begin() + m);
        vector<int> upper(nums.begin() + m, nums.end());
        return merge(
            mergesort(lower),
            mergesort(upper)  
        );
    }
    return nums;
}

/**
 * Merge two vectors in sorted ascending order
 */
vector<int> merge(const vector<int>& A, const vector<int>& B) {
    int m = A.size(), n = B.size();
    vector<int> res(m+n, 0);

    int i = 0, j = 0, k = 0;
    while (i < m && j < n) {
        if (A[i] <= B[j]) {
            res[k] = A[i];
            i++;
        }
        else {
            res[k] = B[j];
            j++;
        }
        k++;
    }

    while (i < m)
        res[k++] = A[i++];

    while (j < n)
        res[k++] = B[j++];

    return res;
}

/**
 * Debug tool: print contents of vector to stdout
 */
void print(const vector<int>& nums) {
    for (int x : nums)
        cout << x << " ";
    cout << endl;
}
