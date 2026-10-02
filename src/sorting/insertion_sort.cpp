#include "sort.hpp"

void InsertionSort(int* l, int* r) {
    if (r - l <= 1) {
        return;
    }

    for (int* i = l; i < r - 1; ++i) {
        int* j = i + 1;
        int tmp = *j;
        while (j > l && *(j - 1) > tmp) {  // Стабильность
            *j = *(j - 1);
            --j;
        }
        *j = tmp;
    }
}
