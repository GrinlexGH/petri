#include "sort.hpp"

void SelectionSort(int* l, int* r) {
    if (r - l <= 1) {
        return;
    }

    for (int* i = l; i < r - 1; ++i) {
        int* mn = i;
        for (int* j = i + 1; j < r; ++j) {
            mn = *mn > *j ? j : mn;
        }

        int tmp = *mn;
        while (mn > i) {
            *mn = *(mn - 1);
            --mn;
        }

        *i = tmp;
    }
}
