#include <vector>

#include "sort.hpp"

namespace {
void Merge(int* l, const int* mid, const int* r) {
    const std::ptrdiff_t n = r - l;
    std::vector tmp(n, 0);
    const int* i = l;
    const int* j = mid;
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

    for (std::ptrdiff_t q = 0; q < n; ++q) {
        *l = tmp[q];
        ++l;
    }
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
