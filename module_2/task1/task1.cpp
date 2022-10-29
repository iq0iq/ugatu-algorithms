#include <iostream>
#include <vector>

bool Comparator(std::pair<int, int> value1, std::pair<int, int> value2) {
    if (value1.first == value2.first) {
        return value1.second < value2.second;
    }
    return value1.first < value2.first;
}

void Insertionsort(std::vector<std::pair<int, int>> &coordinates, int n) {
    for (int i = 1; i < n; ++i) {
        std::pair<int, int> value = coordinates[i];
        int j = i - 1;
        for (; j >= 0 && Comparator(value, coordinates[j]); --j) {
            coordinates[j + 1] = coordinates[j];
        }
        coordinates[j + 1] = value;
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::pair<int, int>> coordinates(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> coordinates[i].first >> coordinates[i].second;
    }
    Insertionsort(coordinates, n);
    for (int i = 0; i < n; ++i) {
        std::cout << coordinates[i].first << ' ' << coordinates[i].second << std::endl;
    }
    return 0;
}