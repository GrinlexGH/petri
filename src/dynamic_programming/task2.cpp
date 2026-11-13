#include <iostream>
#include <vector>

void Task2() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;
    std::vector<int> first(n);
    for (int i = 0; i < n; i++) {
        std::cin >> first[i];
    }

    int m = 0;
    std::cin >> m;
    std::vector<int> second(m);
    for (int i = 0; i < m; i++) {
        std::cin >> second[i];
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = (first[i - 1] == second[j - 1]) ? (dp[i - 1][j - 1] + 1)
                                                       : std::max(dp[i][j - 1], dp[i - 1][j]);
        }
    }

    std::cout << dp[n][m];
}
