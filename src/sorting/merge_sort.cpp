#include <vector>

#include "sort.hpp"

void Merge(int* l, int* mid, int* r) {
    const std::ptrdiff_t n = r - l;
    std::vector tmp(n, 0);
    int* i = l;
    int* j = mid;
    int* k = tmp.data();
    while (i != mid && j != r) {
        if (*i <= *j) {  // Стабильность
            *k = *i;
            ++i;
        } else {
            *k = *j;
            ++j;
        }
        ++k;
    }

    while (i < mid) {
        *k = *i;
        ++i;
        ++k;
    }

    while (j < r) {
        *k = *j;
        ++j;
        ++k;
    }

    for (std::ptrdiff_t i = 0; i < n; ++i) {
        *l = tmp[i];
        ++l;
    }
}

void MergeSort(int* l, int* r) {
    if (r - l <= 1) {
        return;
    }

    MergeSort(l, l + (r - l) / 2);
    MergeSort(l + (r - l) / 2, r);
    Merge(l, l + (r - l) / 2, r);
}
