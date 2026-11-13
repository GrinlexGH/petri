#include <iostream>
#include <vector>

int* LowerBound(int* l, int* r, int x) {
    if (r == l) {
        return r;
    }

    std::size_t mid = (r - l) / 2;

    if (l[mid] >= x) {
        return LowerBound(l, l + mid, x);
    } else {
        return LowerBound(l + mid + 1, r, x);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;
    std::vector<int> seq(n);
    for (int i = 0; i < n; i++) {
        std::cin >> seq[i];
    }

    std::vector<int> dp(n, std::numeric_limits<int>::max());

    for (int i = 0; i < n; i++) {
        int* lb = LowerBound(dp.data(), dp.data() + dp.size(), seq[i]);
        *lb = seq[i];
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i] == std::numeric_limits<int>::max()) {
            break;
        }
        cnt++;
    }

    std::cout << cnt;
}
