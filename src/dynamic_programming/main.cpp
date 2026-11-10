#include <cstdint>
#include <vector>

#include <fmt/format.h>

void Generate(std::uint8_t m, std::uint8_t row, std::uint64_t newMask, std::uint64_t curMask,
              std::vector<std::uint64_t>& res) {
    if (row == m) {
        res.push_back(newMask);
        return;
    }

    if (curMask & (1u << row)) {
        Generate(row + 1, newMask, curMask, m, res);
    } else {
        Generate(row + 1, newMask | (1u << row), curMask, m, res);
        if (row + 1 < m && !(curMask & (1u << (row + 1u)))) {
            Generate(row + 2, newMask, curMask, m, res);
        }
    }
}

std::vector<std::uint64_t> FindAllMasks(std::uint8_t m, std::uint64_t curMask) {
    std::vector<std::uint64_t> res;
    Generate(m, 0, 0, curMask, res);
    return res;
}

std::uint64_t Solve(std::uint8_t m, std::uint8_t n) {
    if ((m * n) % 2 != 0) {
        return 0;
    }

    if (m > n) {
        std::swap(m, n);
    }

    std::vector<std::vector<std::uint64_t>> trans(1u << m);
    for (std::uint64_t mask = 0; mask < (1u << m); mask++) {
        trans[mask] = FindAllMasks(m, mask);
    }

    std::vector<std::uint64_t> lastCou(1u << m, 0);
    std::vector<std::uint64_t> newCou(1u << m, 0);

    std::vector<std::uint64_t> activeMasks = { 0 };
    std::vector<std::uint64_t> futureMasks;

    std::vector<bool> used(1u << m, false);

    lastCou[0] = 1;

    for (std::uint8_t i = 0; i < n; i++) {
        fill(newCou.begin(), newCou.end(), 0);

        futureMasks.clear();
        fill(used.begin(), used.end(), false);

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

int main() { fmt::println("Hello from dynamic_programming!"); }
