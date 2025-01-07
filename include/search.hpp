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
        m = size_t((l + r) / 2);
        if (val == arr[m]) return m;
        if (val < arr[m]) r = m;
        if (val > arr[m]) l = m;
    }
    throw std::range_error("arr is unsorted or does not countain val");
}

size_t bintree(std::vector<int> arr, int val) { // see docs
    return 0;
}

size_t interpolation(std::vector<int> arr, int val) {
    return 0;
}

}

bool is_sorted(std::vector<int> arr) {
    return true;
}

bool is_bintree(std::vector<int> arr) {
    return true;
}