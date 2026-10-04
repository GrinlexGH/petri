#include <vector>

#include "sort.hpp"

void DigitCountingSort(unsigned int* l, unsigned int* r, unsigned int exp) {
    int k = 256;
    std::vector<int> cnt(k, 0);
    for (unsigned int* i = l; i < r; ++i) {
        ++cnt[(*i / exp) % k];
    }

    for (int i = 1; i < k; ++i) {
        cnt[i] += cnt[i - 1];
    }

    std::vector<unsigned int> out(r - l, 0);
    for (unsigned int i = r - l; i > 0; --i) {
        out[--cnt[(l[i - 1] / exp) % k]] = l[i - 1];
    }

    for (int i = 0; i < r - l; ++i) {
        l[i] = out[i];
    }
}

void LSDRadixSortPositive(unsigned int* l, unsigned int* r) {
    if (r - l <= 1) {
        return;
    }

    unsigned int mx = *l;
    for (unsigned int* i = l; i < r; ++i) {
        mx = mx < *i ? *i : mx;
    }

    // Если exp == 0, то мы вышли за пределы любого доступного числа,
    // то есть отсортировали последний байт.
    for (unsigned int exp = 1; (exp != 0) && (mx / exp > 0); exp *= 256) {
        DigitCountingSort(l, r, exp);
    }
}

void LSDRadixSort(int* l, int* r) {
    if (r - l <= 1) {
        return;
    }

    std::vector<unsigned int> negative;
    std::vector<unsigned int> positive;

    for (int* i = l; i < r; ++i) {
        if (*i < 0) {
            // -*i для INT_MIN переполняет int (UB), поэтому считаем модуль в unsigned,
            // где арифметика определена по модулю
            negative.push_back(0u - static_cast<unsigned int>(*i));
        } else {
            positive.push_back(*i);
        }
    }

    LSDRadixSortPositive(positive.data(), positive.data() + positive.size());
    LSDRadixSortPositive(negative.data(), negative.data() + negative.size());

    int pos = 0;
    for (unsigned int i = negative.size(); i > 0; --i) {
        // Ебля с преобразованием. Если в negative лежит |INT_MIN|,
        // то берём |INT_MIN| - 1, это уже влезет в положительный int,
        // дальше кастуем, делаем унарный минус и возвращаем -1 обратно
        l[pos++] = -static_cast<int>(negative[i - 1] - 1u) - 1;
    }

    for (unsigned int x : positive) {
        l[pos++] = static_cast<int>(x);
    }
}
