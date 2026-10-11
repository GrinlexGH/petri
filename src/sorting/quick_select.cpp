#include "sort.hpp"

std::int32_t* Partition(std::int32_t* l, std::int32_t* r);

std::int32_t QuickSelect(std::int32_t* l, std::int32_t* r, std::size_t nth) {
    if (r - l == 1) {
        return *l;
    }

    std::int32_t* q = Partition(l, r);
    if (nth < static_cast<std::size_t>(q - l)) {
        return QuickSelect(l, q, nth);
    }

    return QuickSelect(q, r, nth - (q - l));
}
