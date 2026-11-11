#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {
void Generate(std::uint8_t height, std::uint8_t row, std::uint64_t curMask, std::uint64_t nextMask,
              std::vector<std::uint64_t>& res) {
    if (row == height) {
        res.push_back(nextMask);
        return;
    }

    if (curMask & (1ull << row)) {
        Generate(height, row + 1, curMask, nextMask, res);
    } else {
        if (row + 1 < height && !(curMask & (0b1ull << (row + 1u)))) {
            Generate(height, row + 2, curMask, nextMask, res);
        }

        Generate(height, row + 1, curMask, nextMask | (1ull << row), res);
    }
}

std::vector<std::uint64_t> FindAllMasks(std::uint8_t height, std::uint64_t state) {
    std::vector<std::uint64_t> res;
    Generate(height, 0, state, 0, res);
    return res;
}

std::uint64_t SolveDominoes(std::uint8_t height, std::uint8_t width) {
    if ((height * width) % 2 != 0) {
        return 0;
    }

    if (height > width) {
        std::swap(height, width);
    }

    std::vector<std::vector<std::uint64_t>> trans(1ull <<  height);
    for (std::uint64_t mask = 0; mask < (1ull << height); mask++) {
        trans[mask] = FindAllMasks(height, mask);
    }

    std::vector<std::uint64_t> lastCou(1ull << height, 0);
    std::vector<std::uint64_t> newCou(1ull << height, 0);

    std::vector<std::uint64_t> activeMasks = { 0 };
    std::vector<std::uint64_t> futureMasks;

    std::vector<char> used(1ull << height, false);

    lastCou[0] = 1;

    for (std::uint8_t i = 0; i < width; i++) {
        std::ranges::fill(newCou, 0);
        std::ranges::fill(used, false);
        futureMasks.clear();

        for (std::uint64_t mask : activeMasks) {
            for (std::uint64_t newMask : trans[mask]) {
                newCou[newMask] += lastCou[mask];

                if (!used[newMask]) {
                    used[newMask] = true;
                    futureMasks.push_back(newMask);
                }
            }
        }

        std::swap(lastCou, newCou);
        std::swap(activeMasks, futureMasks);
    }

    return lastCou[0];
}
}

void Task5s() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int h = 0, w = 0;
    std::cin >> h >> w;
    std::cout << SolveDominoes(h, w);
}
