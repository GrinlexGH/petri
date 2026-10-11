#include "sort.hpp"

void SelectionSort(std::int32_t* l, std::int32_t* r) {
    if (r - l <= 1) {
        return;
    }

    for (std::int32_t* i = l; i < r - 1; ++i) {
        std::int32_t* mn = i;
        for (std::int32_t* j = i + 1; j < r; ++j) {
            mn = *mn > *j ? j : mn;
        }

        std::int32_t tmp = *mn;
        while (mn > i) {
            *mn = *(mn - 1);
            --mn;
        }

        *i = tmp;
    }
}
