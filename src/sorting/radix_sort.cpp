#include <vector>

#include "sort.hpp"

void ByteCountingSort(std::uint32_t* l, std::uint32_t* r, std::uint32_t exp) {
    const std::size_t k = 256;
    std::vector cnt(k, 0);
    for (std::uint32_t* i = l; i < r; ++i) {
        ++cnt[(*i / exp) % k];
    }

    for (std::size_t i = 1; i < k; ++i) {
        cnt[i] += cnt[i - 1];
    }

    const std::size_t n = r - l;
    std::vector<std::uint32_t> out(n, 0);
    for (std::size_t i = n; i > 0; --i) {
        out[--cnt[(l[i - 1] / exp) % k]] = l[i - 1];
    }

    for (std::size_t i = 0; i < n; ++i) {
        l[i] = out[i];
    }
}

void LSDRadixSort(std::uint32_t* l, std::uint32_t* r) {
    if (r - l <= 1) {
        return;
    }

    std::uint32_t mx = *l;
    for (std::uint32_t* i = l; i < r; ++i) {
        mx = mx < *i ? *i : mx;
    }

    // Если exp == 0, то мы вышли за пределы любого доступного числа,
    // то есть отсортировали последний байт
    for (std::uint32_t exp = 1; (exp != 0) && (mx / exp > 0); exp *= 256) {
        ByteCountingSort(l, r, exp);
    }
}

void LSDRadixSort(std::int32_t* l, std::int32_t* r) {
    if (r - l <= 1) {
        return;
    }

    std::vector<std::uint32_t> negative;
    std::vector<std::uint32_t> positive;

    for (std::int32_t* i = l; i < r; ++i) {
        if (*i < 0) {
            // -*i для INT32_MIN переполняет int, поэтому считаем модуль в unsigned,
            // где арифметика определена по модулю
            negative.push_back(0u - static_cast<std::uint32_t>(*i));
        } else {
            positive.push_back(*i);
        }
    }

    LSDRadixSort(positive.data(), positive.data() + positive.size());
    LSDRadixSort(negative.data(), negative.data() + negative.size());

    std::size_t pos = 0;
    for (std::size_t i = negative.size(); i > 0; --i) {
        // Ебля с преобразованием. Если в negative лежит abs(INT32_MIN),
        // то берём abs(INT32_MIN) - 1, это уже влезет в положительный int,
        // дальше кастуем, делаем унарный минус и возвращаем -1 обратно
        l[pos++] = -static_cast<std::int32_t>(negative[i - 1] - 1u) - 1;
    }

    for (std::uint32_t x : positive) {
        l[pos++] = static_cast<std::int32_t>(x);
    }
}
