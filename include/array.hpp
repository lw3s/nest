#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <utility>
#include <cstdlib>
#include <exception>
#include <vector>

template <typename T>
std::pair<size_t, size_t> kadane(std::vector<T> arr) {
    if (arr.size() == 0) throw std::range_error("array size needs to be at least 1");
    std::pair<size_t, size_t> start_end;
    size_t start = 0;
    T sum = T(), highest_sum = T();
    for (size_t i = 0; i < arr.size(); ++i) {
        if (sum <= 0) {
            start = i;
            sum = T();
        } else if (sum > highest_sum) {
            highest_sum = sum;
            start_end.first = start;
            start_end.second = i - 1;
        }
        sum += arr[i];
    }
    return start_end;
}

template <typename T>
std::pair<size_t, size_t> kadane(T* arr, size_t length) {
    if (length == 0) throw std::range_error("array size needs to be at least 1");
    std::pair<size_t, size_t> start_end;
    size_t start = 0;
    T sum = T(), highest_sum = T();
    for (size_t i = 0; i < length; ++i) {
        if (sum <= 0) {
            start = i;
            sum = T();
        } else if (sum > highest_sum) {
            highest_sum = sum;
            start_end.first = start;
            start_end.second = i - 1;
        }
        sum += arr[i];
    }
    return start_end;
}

#endif // ARRAY_HPP