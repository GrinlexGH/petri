#include <vector>

#include "sort.hpp"

void CountingSort(std::int32_t* l, std::int32_t* r) {
    if (r - l <= 1) {
        return;
    }

    std::int32_t mn = *l;
    std::int32_t mx = *(r - 1);
    for (const std::int32_t* i = l; i < r; ++i) {
        mn = mn > *i ? *i : mn;
        mx = mx < *i ? *i : mx;
    }

    const std::size_t k = mx - mn + 1;
    std::vector cnt(k, 0);
    for (const std::int32_t* i = l; i < r; ++i) {
        ++cnt[*i - mn];
    }

    for (std::size_t i = 1; i < k; ++i) {
        cnt[i] += cnt[i - 1];
    }

    const std::size_t n = r - l;
    std::vector out(n, 0);
    for (std::size_t i = n; i > 0; --i) {
        out[--cnt[l[i - 1] - mn]] = l[i - 1];
    }

    for (std::size_t i = 0; i < n; ++i) {
        l[i] = out[i];
    }
}
