#include <iostream>
#include <vector>
using namespace std;

// Function to count inversions using merge sort
int merge_and_count(vector<int>& arr, vector<int>& temp_arr, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp_arr[k] = arr[i];
            i++;
        }
        else {
            temp_arr[k] = arr[j];
            inv_count += (mid - i + 1);
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp_arr[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp_arr[k] = arr[j];
        j++;
        k++;
    }

    for (int i = left; i <= right; i++) {
        arr[i] = temp_arr[i];
    }

    return inv_count;
}

int merge_sort_and_count(vector<int>& arr, vector<int>& temp_arr, int left, int right) {
    int inv_count = 0;
    if (left < right) {
        int mid = (left + right) / 2;
        inv_count += merge_sort_and_count(arr, temp_arr, left, mid);
        inv_count += merge_sort_and_count(arr, temp_arr, mid + 1, right);
        inv_count += merge_and_count(arr, temp_arr, left, mid, right);
    }
    return inv_count;
}

int count_inversions(vector<int>& arr) {
    vector<int> temp_arr(arr.size());
    return merge_sort_and_count(arr, temp_arr, 0, arr.size() - 1);
}

int main() {
    vector<vector<int>> test_cases = {
        {1, 2, 3, 4, 5, 6},   // Sorted array (0 inversions)
        {1, 3, 5, 2, 4, 6},   // Random unsorted array
        {6, 5, 4, 3, 2, 1}    // Descending order (maximum inversions)
    };

    for (int i = 0; i < test_cases.size(); i++) {
        vector<int> arr = test_cases[i];
        int inversions = count_inversions(arr);
        cout << "Test case " << (char)('A' + i) << ": " << inversions << " inversions" << endl;
    }

    return 0;
}
