#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include <fmt/format.h>

void Generate(std::uint8_t height, std::uint8_t row, std::uint64_t newMask, std::uint64_t curMask,
              std::vector<std::uint64_t>& res) {
    if (row == height) {
        res.push_back(newMask);
        return;
    }

    if (curMask & (1u << row)) {
        Generate(row + 1, newMask, curMask, height, res);
    } else {
        Generate(row + 1, newMask | (1u << row), curMask, height, res);
        if (row + 1 < height && !(curMask & (1u << (row + 1u)))) {
            Generate(row + 2, newMask, curMask, height, res);
        }
    }
}

std::vector<std::uint64_t> FindAllMasks(std::uint8_t height, std::uint64_t curMask) {
    std::vector<std::uint64_t> res;
    Generate(height, 0, 0, curMask, res);
    return res;
}

std::uint64_t SolveDominoes(std::uint8_t height, std::uint8_t width) {
    if ((height * width) % 2 != 0) {
        return 0;
    }

    if (height > width) {
        std::swap(height, width);
    }

    std::vector<std::vector<std::uint64_t>> trans(1u << height);
    for (std::uint64_t mask = 0; mask < (1u << height); mask++) {
        trans[mask] = FindAllMasks(height, mask);
    }

    std::vector<std::uint32_t> lastCou(1u << height, 0);
    std::vector<std::uint32_t> newCou(1u << height, 0);

    std::vector<std::uint64_t> activeMasks = { 0 };
    std::vector<std::uint64_t> futureMasks;

    std::vector<bool> used(1u << height, false);

    lastCou[0] = 1;

    for (std::uint8_t i = 0; i < width; i++) {
        std::ranges::fill(newCou, 0);
        std::ranges::fill(futureMasks, 0);
        std::ranges::fill(used, false);

        for (std::uint64_t mask : activeMasks) {
            for (std::uint64_t newMask : trans[mask]) {
                newCou[newMask] += lastCou[mask];

                if (!used[newMask]) {
                    used[newMask] = true;
                    futureMasks.push_back(newMask);
                }
            }
        }

        swap(lastCou, newCou);
        swap(activeMasks, futureMasks);
    }

    return lastCou[0];
}

int main() {
    std::uint8_t w = 0, h = 0;
    fmt::println("Enter height and width of the desk: ");
    std::cin >> h >> w;
    fmt::println("{}", SolveDominoes(h, w));
}
