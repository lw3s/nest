#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <vector>
#include <cstdlib>
#include <stdexcept>

namespace search {

int linear(std::vector<int> arr, int val) {
    /**
     * int search::linear(std::vector<int>, int)
     * 
     * return the index at which val occurs or throw an error
     */
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == val) return i;
    }
    throw std::range_error("arr does not contain val");
}

int binary(std::vector<int> arr, int val) {
    /**
     * int search::binary(std::vector<int>, int)
     * 
     * search more efficiently, assuming vector is sorted; if not, behavior is undefined
     */
    int l = 0, r = arr.size() - 1, m;
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

int tree(std::vector<int> arr, int val) {
    /**
     * int tree(std::vector<int>, int)
     * 
     * works like others, but assumes that if we have vector { a, b, c, d, e, f, g }, it represent the binary search tree:
     *      a
     *    /   \
     *   b     c
     *  / \   / \
     * d   e f   g
     */
    int pos = 0;
    while (pos < arr.size()) {
        if (val == arr[pos]) return pos;
        
        if (val < arr[pos]) pos = pos * 2 + 1;
        else if (val > arr[pos]) pos = pos * 2 + 2;
    }
    throw std::range_error("arr is invalid binary search tree or does not contain val");
}

int interpolation(std::vector<int> arr, int val) {
    /**
     * int search::interpolation(std::vector<int>, int)
     * 
     * like binary search, except more efficient if evenly distributed
     */
    int l = 0, r = arr.size() - 1, m;
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
    /**
     * bool is_sorted(std::vector<int>)
     * 
     * checks if we can use binary/interpolation
     */
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i-1] > arr[i]) return false;
    }
    return true;
}

bool is_bintree(std::vector<int> arr, int root = 0) {
    /**
     * bool is_bintree(std::vector)
     * 
     * checks if we can use the search::tree on the vector
     */
    int left = root * 2 + 1, right = root * 2 + 2;
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
