#include <iostream>
#include <vector>

void Insertion_sort(std::vector<std::pair<int, int>> &coordinates) {
  for (int i = 1; i < coordinates.size(); ++i) {
    std::pair<int, int> value = coordinates[i];
    int j = i - 1;
    for (; j >= 0 && value < coordinates[j]; --j) {
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
  Insertion_sort(coordinates);
  for (int i = 0; i < n; ++i) {
    std::cout << coordinates[i].first << ' ' << coordinates[i].second
              << std::endl;
  }
  return 0;
}
