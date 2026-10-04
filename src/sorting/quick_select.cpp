#include <random>

#include "sort.hpp"

// Разбиение Хоара
int* Partition(int* l, int* r) {
    thread_local std::mt19937 randomGenerator { std::random_device { }() };
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0, (r - l) - 1);

    const int pivot = l[distribution(randomGenerator)];
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
            const int tmp = *i;
            *i = *j;
            *j = tmp;

            ++i;
            --j;
        }
    }

    return i;
}

int QuickSelect(int* l, int* r, unsigned int nth) {
    if (r - l == 1) {
        return *l;
    }

    int* q = Partition(l, r);
    // Элемент слева
    if (nth < q - l) {
        return QuickSelect(l, q, nth);
    }

    // Элемент справа
    return QuickSelect(q, r, nth - (q - l));
}
