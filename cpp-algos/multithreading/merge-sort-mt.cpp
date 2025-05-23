#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <functional>
// #include <chrono>

using namespace std;


vector<int> mergesort_multi_thread(const vector<int>& nums);
void thread_sort(const vector<int>& partial_nums, vector<int>& result);
vector<int> mergesort(const vector<int>& nums);
vector<int> merge(const vector<int>& A, const vector<int>& B);
void print(const vector<int>& nums);

/**
 * ENTRY POINT OF PROGRAM
 */
int main() {
    vector<int> sorted_res = mergesort_multi_thread({4, 3, 1, 8, 9});
    print(sorted_res);
    sorted_res = mergesort_multi_thread(
        {99, 86, 54, 33, 47, 99, 100, 102, 4, 7, 19, 44, 57, 12, 13, 20, 45, 99, 83, 38}
    );
    print(sorted_res);
    return 0;
}
// ================================

/**
 * @brief Multithreaded version of mergesort
 * 
 * Due to management overhead of threads, performance boost
 * only with large collections of data 
 * 
 * @param nums input vector
 * @return sorted copy of input vec
 */
vector<int> mergesort_multi_thread(const vector<int>& nums) {
    int n = nums.size();
    if (n < 10) {
        cerr << "use single threaded merge sort for this task..." << endl;
        return {};
    }

    int one_third = n / 3; 
    int two_thirds = one_third + one_third;
    vector<int> arr1(nums.begin(), nums.begin() + one_third);
    vector<int> arr2(nums.begin() + one_third, nums.begin() + two_thirds);
    vector<int> arr3(nums.begin() + two_thirds, nums.end());
    
    vector<int> res1, res2, res3;

    // Launch 3 threads...
    thread t1(thread_sort, std::ref(arr1), std::ref(res1)); // NOTE: use std::ref because thread arguments always create a copy by default
    thread t2(thread_sort, std::ref(arr2), std::ref(res2));
    thread t3(thread_sort, std::ref(arr3), std::ref(res3));

    // Wait for all 3 to finish...
    t1.join();
    t2.join();
    t3.join();

    // merge and return results
    return merge(res1, merge(res2, res3));
}

///@brief utility function: assign sorting task to thread
void thread_sort(const vector<int>& partial_nums, vector<int>& result) {
    // Stagger execution (to show threads are not run sequentially)
    // std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    
    result = mergesort(partial_nums);
}

/**
 * @brief Mergesort implementation (recursive divide and conquer)
 * @param nums vector to sort
 * @return sorted copy of input vector
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
 * @brief Merge two vectors in sorted ascending order
 * 
 * @param A sorted lower half 
 * @param B sorted upper half
 * @return merged vector
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
 * @brief Debug tool: print contents of vector to stdout
 * @param nums input vector
 */
void print(const vector<int>& nums) {
    if (nums.empty()) {
        cout << "list is empty..." << endl;
        return;
    }
    
    for (int x : nums)
        cout << x << " ";
    cout << endl;
}


