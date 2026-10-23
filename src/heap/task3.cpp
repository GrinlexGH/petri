#include <iostream>
#include <vector>

#include "tasks.hpp"

namespace {
struct Node {
    std::int64_t val = 0;
    int id = 0;
};

void SiftUpMax(std::vector<Node>& arr, std::size_t i) {
    while (i != 0) {
        std::size_t parent = (i + 1) / 2 - 1;

        if (arr[parent].val < arr[i].val) {
            std::swap(arr[parent], arr[i]);
            i = parent;
        } else {
            break;
        }
    }
}

void SiftUpMin(std::vector<Node>& arr, std::size_t i) {
    while (i != 0) {
        std::size_t parent = (i + 1) / 2 - 1;

        if (arr[parent].val > arr[i].val) {
            std::swap(arr[parent], arr[i]);
            i = parent;
        } else {
            break;
        }
    }
}

void SiftDownMax(std::vector<Node>& arr, std::size_t i) {
    while (true) {
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;
        std::size_t largest = i;

        if (left < arr.size() && arr[left].val > arr[largest].val) {
            largest = left;
        }

        if (right < arr.size() && arr[right].val > arr[largest].val) {
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

void SiftDownMin(std::vector<Node>& arr, std::size_t i) {
    while (true) {
        std::size_t left = 2 * i + 1;
        std::size_t right = 2 * i + 2;
        std::size_t smallest = i;

        if (left < arr.size() && arr[left].val < arr[smallest].val) {
            smallest = left;
        }

        if (right < arr.size() && arr[right].val < arr[smallest].val) {
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
}

void Task3() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;

    std::vector<Node> minHeap;
    std::vector<Node> maxHeap;
    std::vector<bool> isDeleted(n, false);

    int curId = 0;

    for (int i = 0; i < n; ++i) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "GetMin") {
            while (!minHeap.empty() && isDeleted[minHeap[0].id]) {
                minHeap[0] = minHeap.back();
                minHeap.pop_back();
                if (!minHeap.empty()) {
                    SiftDownMin(minHeap, 0);
                }
            }

            std::cout << minHeap[0].val << std::endl;
            isDeleted[minHeap[0].id] = true;

            minHeap[0] = minHeap.back();
            minHeap.pop_back();
            if (!minHeap.empty()) {
                SiftDownMin(minHeap, 0);
            }
        } else if (cmd == "GetMax") {
            while (!maxHeap.empty() && isDeleted[maxHeap[0].id]) {
                maxHeap[0] = maxHeap.back();
                maxHeap.pop_back();
                if (!maxHeap.empty()) {
                    SiftDownMax(maxHeap, 0);
                }
            }

            std::cout << maxHeap[0].val << std::endl;
            isDeleted[maxHeap[0].id] = true;

            maxHeap[0] = maxHeap.back();
            maxHeap.pop_back();
            if (!maxHeap.empty()) {
                SiftDownMax(maxHeap, 0);
            }
        } else {
            std::int64_t x = 0;
            bool negative = false;
            int pos = 7;

            if (cmd[pos] == '-') {
                negative = true;
                ++pos;
            }

            cmd.pop_back();

            char* end;
            x = std::strtoll(cmd.c_str() + pos, &end, 10);
            x = negative ? -x : x;

            Node newNode { x, curId++ };

            maxHeap.push_back(newNode);
            SiftUpMax(maxHeap, maxHeap.size() - 1);

            minHeap.push_back(newNode);
            SiftUpMin(minHeap, minHeap.size() - 1);
        }
    }
}
