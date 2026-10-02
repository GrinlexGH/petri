#include <random>

#include "sort.hpp"

// Разбиение Хоара
int* Partition(int* l, int* r) {
    static thread_local std::mt19937 randomGenerator { std::random_device { }() };
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0, (r - l) - 1);

    int pivot = *(l + distribution(randomGenerator));
    int* i = l;
    int* j = r - 1;

    while (i <= j) {
        while (*i < pivot) {
            ++i;
        }

        while (*j > pivot) {
            --j;
        }

        if (i <= j) {
            int tmp = *i;
            *i = *j;
            *j = tmp;

            ++i;
            --j;
        }
    }

    return i;
}

void QuickSort(int* l, int* r) {
    if (r - l <= 1) {
        return;
    }

    int* q = Partition(l, r);
    QuickSort(l, q);
    QuickSort(q, r);
}
