#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

void Task1() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;
    std::vector<char> clearing(n);
    for (int i = 0; i < n; i++) {
        std::cin >> clearing[i];
    }

    std::vector<int> dp(n, -1);
    dp[0] = 0;
    for (int i = 1; i < n; ++i) {
        if (clearing[i] == 'w') {
            continue;
        }

        int bonus = clearing[i] == '"' ? 1 : 0;
        std::array<int, 3> variants;
        variants[0] = (i >= 1 && dp[i - 1] != -1) ? (dp[i - 1] + bonus) : (-1);
        variants[1] = (i >= 3 && dp[i - 3] != -1) ? (dp[i-3] + bonus) : (-1);
        variants[2] = (i >= 5 && dp[i - 5] != -1) ? (dp[i-5] + bonus) : (-1);

        int maxPrev = *std::ranges::max_element(variants);
        dp[i] = (maxPrev != -1) ? maxPrev : dp[i];
    }

    std::cout << dp[n - 1];
}
