#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <iostream>
#include <algorithm>

void countingSort(std::vector<int>& arr, int exp) { // For RADIX ---------------------
    int n = arr.size();
    std::vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}
int partition(std::vector<int>& arr, int low, int high) { // For QUICK ---------------
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}





namespace sort{





void radix(std::vector<int>& arr) {
 int maxVal = *std::max_element(arr.begin(), arr.end());

     for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSort(arr, exp);

}

void insertion(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void quick(std::vector<int>& arr, int low = 0, int high = -1) {
    if (high == -1) {
        high = arr.size() - 1;
    }
    if (low < high) {
        int pi = partition(arr, low, high);
        quick(arr, low, pi - 1);
        quick(arr, pi + 1, high);
    }
}
   
void merge(std::vector<int>& arr) {
    //if (left < right) {
        //int mid = left + (right - left) / 2;

        //merge(arr, left, mid);
       // merge(arr, mid + 1, right);

        //mergeHelp(arr, left, mid, right);
    //}
}

}
#endif // SORT_HPP