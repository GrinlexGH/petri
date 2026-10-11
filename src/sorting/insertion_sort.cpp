#include "sort.hpp"

void InsertionSort(std::int32_t* l, std::int32_t* r) {
    if (r - l <= 1) {
        return;
    }

    for (std::int32_t* i = l; i < r - 1; ++i) {
        std::int32_t* j = i + 1;
        const std::int32_t tmp = *j;
        while (j > l && *(j - 1) > tmp) {
            *j = *(j - 1);
            --j;
        }
        *j = tmp;
    }
}
