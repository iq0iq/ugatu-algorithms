#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<int, int>> segments;
    int x = 0;
    int y = 0;
    while (std::cin >> x >> y)
        segments.emplace_back(y, x);
    sort(segments.begin(), segments.end());
    int sum = 0;
    int last = 0;
    for (std::pair<int, int> i: segments) {
        if (i.second >= last) {
            ++sum;
            last = i.first;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
