#include <random>

#include "sort.hpp"

std::int32_t* Partition(std::int32_t* l, std::int32_t* r) {
    static std::mt19937 generator { std::random_device { }() };
    std::uniform_int_distribution<std::size_t> distribution(0, (r - l) - 1);

    const std::int32_t pivot = l[distribution(generator)];
    std::int32_t* i = l;
    std::int32_t* j = r - 1;

    while (i <= j) {
        while (*i < pivot) {
            ++i;
        }

        while (*j > pivot) {
            --j;
        }

        if (i <= j) {
            const std::int32_t tmp = *i;
            *i = *j;
            *j = tmp;

            ++i;
            --j;
        }
    }

    return i;
}

void QuickSort(std::int32_t* l, std::int32_t* r) {
    if (r - l <= 1) {
        return;
    }

    std::int32_t* q = Partition(l, r);
    QuickSort(l, q);
    QuickSort(q, r);
}
