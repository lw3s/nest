#ifndef UTIL_HPP
#define UTIL_HPP

#include <utility>
#include <cstdlib>
#include <exception>
#include <vector>
#include <cmath>


int gcf(int a, int b) {
    /**
     * int gcf(int, int)
     * 
     * use Euclidean algorithm to return the greatest common factor of 2 integers
     */
    a = std::abs(a); b = std::abs(b);
    int remainder;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int lcm(int a, int b) {
    /**
     * int lcm(int, int)
     * 
     * use gcf function above to return least common multiple of 2 integers
     */
    return a * b / gcf(a, b);
}

template <typename T>
std::pair<int, int> kadane(std::vector<T> arr) {
    /**
     * std::pair<int, int> kadane(std::vector)
     * 
     * implements kadane's algorithm on a vector
     */
    if (arr.size() == 0) throw std::range_error("array size needs to be at least 1");
    std::pair<int, int> start_end;
    int start = 0;
    T sum = T(), highest_sum = T();
    for (int i = 0; i < arr.size(); ++i) {
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
std::pair<int, int> kadane(T* arr, int length) {
    /**
     * std::pair<int, int> kadane(T*, int)
     * 
     * implements kadane's algorithm on a C-style static array, given its length
     */
    if (length == 0) throw std::range_error("array size needs to be at least 1");
    std::pair<int, int> start_end;
    int start = 0;
    T sum = T(), highest_sum = T();
    for (int i = 0; i < length; ++i) {
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

#endif // UTIL_HPP
