#include <iostream>
#include <vector>

#include "tasks.hpp"

namespace {
void SiftDownMin(std::vector<std::int64_t>& arr, std::size_t i) {
    while (true) {
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;
        std::size_t smallest = i;

        if (left < arr.size() && arr[left] < arr[smallest]) {
            smallest = left;
        }

        if (right < arr.size() && arr[right] < arr[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            std::swap(arr[i], arr[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

void SiftUpMin(std::vector<std::int64_t>& arr, std::size_t i) {
    while (i != 0) {
        std::size_t parent = (i + 1) / 2 - 1;

        if (arr[parent] > arr[i]) {
            std::swap(arr[parent], arr[i]);
            i = parent;
        } else {
            break;
        }
    }
}

std::int64_t PopMinHeap(std::vector<std::int64_t>& arr) {
    std::int64_t ret = arr[0];
    arr[0] = arr.back();
    arr.pop_back();
    if (!arr.empty()) {
        SiftDownMin(arr, 0);
    }
    return ret;
}

void PushMinHeap(std::vector<std::int64_t>& arr, std::int64_t x) {
    arr.push_back(x);
    SiftUpMin(arr, arr.size() - 1);
}

void MakeMinHeap(std::vector<std::int64_t>& arr) {
    for (int i = (int)arr.size() / 2 - 1; i >= 0; --i) {
        SiftDownMin(arr, i);
    }
}

struct Node {
    std::int64_t dur = 0;
    std::int64_t cost = 0;
};

void SiftUpMin(std::vector<Node>& arr, std::size_t i) {
    while (i != 0) {
        std::size_t parent = (i + 1) / 2 - 1;

        if (arr[parent].dur > arr[i].dur) {
            std::swap(arr[parent], arr[i]);
            i = parent;
        } else {
            break;
        }
    }
}

void PushMinHeap(std::vector<Node>& arr, Node x) {
    arr.push_back(x);
    SiftUpMin(arr, arr.size() - 1);
}

void SiftDownMin(std::vector<Node>& arr, std::size_t i) {
    while (true) {
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;
        std::size_t smallest = i;

        if (left < arr.size() && arr[left].dur < arr[smallest].dur) {
            smallest = left;
        }

        if (right < arr.size() && arr[right].dur < arr[smallest].dur) {
            smallest = right;
        }

        if (smallest != i) {
            std::swap(arr[i], arr[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

Node PopMinHeap(std::vector<Node>& arr) {
    Node ret = arr[0];
    arr[0] = arr.back();
    arr.pop_back();
    if (!arr.empty()) {
        SiftDownMin(arr, 0);
    }
    return ret;
}
}

void Task4() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int m = 0;
    std::cin >> n >> m;

    std::vector<std::int64_t> freeCores(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> freeCores[i];
    }

    MakeMinHeap(freeCores);

    std::vector<Node> busyCores;
    std::uint64_t totalCost = 0;
    for (int i = 0; i < m; ++i) {
        std::int64_t t = 0;
        std::int64_t f = 0;
        std::cin >> t >> f;

        while (!busyCores.empty() && busyCores[0].dur <= t) {
            Node freedCore = PopMinHeap(busyCores);
            PushMinHeap(freeCores, freedCore.cost);
        }

        if (!freeCores.empty()) {
            std::int64_t lowestRate = PopMinHeap(freeCores);
            totalCost += lowestRate * f;
            PushMinHeap(busyCores, { t + f, lowestRate });
        }
    }

    std::cout << totalCost << std::endl;
}
