#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

#include "sort.hpp"

int main() {
    std::vector<std::int32_t> arr { -3, -2, -1, 0, 0, 1, 2, 3 };
    std::mt19937 generator { std::random_device { }() };
    std::uniform_int_distribution<std::size_t> distribution(0, arr.size() - 1);

    std::ranges::shuffle(arr, generator);
    QuickSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));
    QuickSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));

    std::ranges::shuffle(arr, generator);
    std::vector tmp = arr;
    std::size_t idx = distribution(generator);
    std::ranges::nth_element(tmp, tmp.begin() + static_cast<std::ptrdiff_t>(idx));
    assert(QuickSelect(arr.data(), arr.data() + arr.size(), idx) == tmp[idx]);

    arr = { 3, 2, 1, 0, 0, -1, -2, -3 };
    assert(MergeSort(arr.data(), arr.data() + arr.size()) == 27);
    assert(std::ranges::is_sorted(arr));
    assert(MergeSort(arr.data(), arr.data() + arr.size()) == 0);
    assert(std::ranges::is_sorted(arr));

    std::ranges::shuffle(arr, generator);
    CountingSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));
    CountingSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));

    std::ranges::shuffle(arr, generator);
    LSDRadixSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));
    LSDRadixSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));

    std::ranges::shuffle(arr, generator);
    InsertionSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));
    InsertionSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));

    std::ranges::shuffle(arr, generator);
    SelectionSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));
    SelectionSort(arr.data(), arr.data() + arr.size());
    assert(std::ranges::is_sorted(arr));
}
