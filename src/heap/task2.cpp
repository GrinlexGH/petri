#include <iostream>
#include <vector>

#include "tasks.hpp"

namespace {
void SiftDownMax(std::vector<std::int32_t>& arr, std::size_t size, std::size_t i) {
    while (true) {
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;
        std::size_t largest = i;

        if (left < size && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < size && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            i = largest;
        } else {
            break;
        }
    }
}

void MakeMaxHeap(std::vector<std::int32_t>& arr) {
    for (int i = (int)arr.size() / 2 - 1; i >= 0; --i) {
        SiftDownMax(arr, arr.size(), i);
    }
}
}

void Task2() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;

    std::vector<std::int32_t> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    MakeMaxHeap(a);

    for (int i = n - 1; i > 0; --i) {
        std::swap(a[0], a[i]);
        SiftDownMax(a, i, 0);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << " ";
    }

    std::cout << std::endl;
}
