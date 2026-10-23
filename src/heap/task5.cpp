#include <iostream>
#include <vector>

#include "tasks.hpp"

namespace {
constexpr int kMaxTime = 100000;
constexpr int kMaxBlocks = 30000;
constexpr int kL = 600;

void SiftDownMin(std::vector<int>& arr, std::size_t i) {
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

int PopMinHeap(std::vector<int>& arr) {
    int ret = arr[0];
    arr[0] = arr.back();
    arr.pop_back();
    if (!arr.empty()) {
        SiftDownMin(arr, 0);
    }
    return ret;
}

void SiftUpMin(std::vector<int>& arr, std::size_t i) {
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

void PushMinHeap(std::vector<int>& arr, int x) {
    arr.push_back(x);
    SiftUpMin(arr, arr.size() - 1);
}
}

void Task5() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> mem(kMaxBlocks);
    for (int i = 0; i < kMaxBlocks; ++i) {
        mem[i] = i + 1;
    }

    std::vector<int> expiryTime(kMaxBlocks + 1, 0);
    std::vector<std::vector<int>> wantBeFree(kMaxTime);

    int curT = 0;
    int t = 0;
    std::string cmd;
    while (std::cin >> t >> cmd) {
        while (curT <= t) {
            for (int block : wantBeFree[curT]) {
                if (expiryTime[block] == curT) {
                    PushMinHeap(mem, block);
                    expiryTime[block] = 0;
                }
            }
            ++curT;
        }

        if (cmd == "+") {
            int block = PopMinHeap(mem);
            expiryTime[block] = t + kL;
            wantBeFree[t + kL].push_back(block);
            std::cout << block << std::endl;
        } else if (cmd == ".") {
            int block;
            std::cin >> block;

            if (expiryTime[block] > t) {
                expiryTime[block] = t + kL;
                wantBeFree[t + kL].push_back(block);
                std::cout << "+" << std::endl;
            } else {
                std::cout << "-" << std::endl;
            }
        }
    }
}
