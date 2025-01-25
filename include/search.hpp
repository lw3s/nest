#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <vector>
#include <cstdlib>
#include <stdexcept>

namespace search {

size_t linear(std::vector<int> arr, int val) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == val) return i;
    }
    throw std::range_error("arr does not contain val");
}

size_t binary(std::vector<int> arr, int val) {
    size_t l = 0, r = arr.size() - 1, m;
    if (arr[l] == val) return l;
    if (arr[r] == val) return r;
    while (r - l >= 2) {
        m = (l + r) / 2;
        if (val == arr[m]) return m;

        if (val < arr[m]) r = m;
        else if (val > arr[m]) l = m;
    }
    throw std::range_error("arr is unsorted or does not contain val");
}

size_t tree(std::vector<int> arr, int val) { // see docs
    size_t pos = 0;
    while (pos < arr.size()) {
        if (val == arr[pos]) return pos;
        
        if (val < arr[pos]) pos = pos * 2 + 1;
        else if (val > arr[pos]) pos = pos * 2 + 2;
    }
    throw std::range_error("arr is invalid binary search tree or does not contain val");
}

size_t interpolation(std::vector<int> arr, int val) {
    size_t l = 0, r = arr.size() - 1, m;
    if (arr[l] == val) return l;
    if (arr[r] == val) return r;
    while (r - l >= 2) {
        m = ((val - arr[l]) * (r - l) / (arr[r] - arr[l])) + l;
        if (!(l < m < r)) break;
        if (val == arr[m]) return m;

        if (val < arr[m]) r = m;
        else if (val > arr[m]) l = m;
    }
    while (r - l >= 2) {
        m = (l + r) / 2;
        if (val == arr[m]) return m;

        if (val < arr[m]) r = m;
        else if (val > arr[m]) l = m;
    }
    throw std::range_error("arr is unsorted or does not contain val");
}

}

bool is_sorted(std::vector<int> arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i-1] > arr[i]) return false;
    }
    return true;
}

bool is_bintree(std::vector<int> arr, size_t root = 0) {
    size_t left = root * 2 + 1, right = root * 2 + 2;
    if (right < arr.size()) {
        if (arr[right] <= arr[root]) return false;
        if (!is_bintree(arr, right)) return false;
    }
    if (left < arr.size()) {
        if (arr[left] >= arr[root]) return false;
        if (!is_bintree(arr, left)) return false;
    }
    return true;
}

#endif // SEARCH_HPP
