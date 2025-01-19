#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <iostream>
#include <algorithm>


void countingSort(std::vector<int>& arr, int exp) {
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


namespace sort {

void radix(std::vector<int>& arr) {
    int maxVal = *std::max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSort(arr, exp);

}

void insertion(std::vector<int>& arr) {

}

void quick(std::vector<int>& arr) {

}

void merge(std::vector<int>& arr) {

}

}

#endif // SORT_HPP