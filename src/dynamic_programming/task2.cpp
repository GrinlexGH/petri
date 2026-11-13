#include <iostream>
#include <vector>

int main() {
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
}
