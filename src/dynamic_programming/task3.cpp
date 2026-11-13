#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Item {
    int weight = 0;
    double value = 0;
};

void Task3() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0, wBig = 0;
    std::cin >> n >> wBig;
    std::vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        std::cin >> items[i].weight >> items[i].value;
    }

    std::vector<std::vector<double>> pref(n + 1, std::vector<double>(wBig + 1, 0.0f));
    for (int i = 1; i <= n; i++) {
        int wt = items[i - 1].weight;
        double val = items[i - 1].value;
        for (int w = 0; w <= wBig; w++) {
            pref[i][w] = pref[i - 1][w];
            if (w >= wt) {
                pref[i][w] = std::max(pref[i][w], pref[i - 1][w - wt] + val);
            }
        }
    }

    std::vector<std::vector<double>> suff(n + 2, std::vector<double>(wBig + 1, 0.0f));
    for (int i = n; i >= 1; i--) {
        int wt = items[i - 1].weight;
        double val = items[i - 1].value;
        for (int w = 0; w <= wBig; w++) {
            suff[i][w] = suff[i + 1][w];
            if (w >= wt) {
                suff[i][w] = std::max(suff[i][w], suff[i + 1][w - wt] + val);
            }
        }
    }

    std::cout << std::fixed << std::setprecision(9);
    for (int j = 1; j <= n; j++) {
        double maxVal = 0.0f;
        for (int w = 0; w <= wBig; w++) {
            double current = pref[j - 1][w] + suff[j + 1][wBig - w];
            maxVal = std::max(current, maxVal);
        }
        std::cout << maxVal << '\n';
    }
}
