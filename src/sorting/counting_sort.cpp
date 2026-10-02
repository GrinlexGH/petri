#include <vector>

#include "sort.hpp"

void CountingSort(int* l, int* r) {
    if (r - l <= 1) {
        return;
    }

    int mn = *l;
    int mx = *(r - 1);
    for (int* i = l; i < r; ++i) {
        mn = mn > *i ? *i : mn;
        mx = mx < *i ? *i : mx;
    }

    int k = mx - mn + 1;
    std::vector<int> cnt(k, 0);
    for (int* i = l; i < r; ++i) {
        ++cnt[*i - mn];
    }

    // Собираем префиксную сумму
    for (int i = 1; i < k; ++i) {
        cnt[i] += cnt[i - 1];
    }

    const std::ptrdiff_t n = r - l;
    std::vector<int> out(n, 0);
    for (std::ptrdiff_t i = n - 1; i >= 0; --i) {
        out[--cnt[l[i] - mn]] = l[i];
    }

    for (std::ptrdiff_t i = 0; i < n; ++i) {
        l[i] = out[i];
    }
}
