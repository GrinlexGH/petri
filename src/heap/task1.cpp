#include <iostream>
#include <vector>

#include "tasks.hpp"

void Task1() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;

    std::vector<std::int64_t> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }

    // (i + 1) / 2 - 1
    // 2*i + 1
    // 2*i + 2
    bool isValid = true;
    for (int i = 2; i <= n; ++i) {
        if (a[i / 2] > a[i]) {
            isValid = false;
            break;
        }
    }

    if (isValid) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}
