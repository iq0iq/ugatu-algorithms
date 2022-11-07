#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int Partition(std::vector<int> &numbers, int left, int right) {
    int n = right - left + 1;
    if (n <= 1) return left;
    if (numbers[left] < numbers[(left + right) / 2]) {
        std::swap(numbers[left], numbers[(left + right) / 2]);
    }
    if (numbers[right] < numbers[(left + right) / 2]) {
        std::swap(numbers[right], numbers[(left + right) / 2]);
    }
    if (numbers[right] < numbers[left]) {
        std::swap(numbers[right], numbers[left]);
    }  // средний по величине элемент в left
    int pivot = numbers[left];
    int i = right;
    int j = right;
    while (j >= left) {
        for (; numbers[j] < pivot; --j) {}
        std::swap(numbers[i--], numbers[j--]);
    }
    return i + 1;
}

int QuickSelect(std::vector<int> &numbers, int k) {
    int left = 0, right = numbers.size() - 1;
    while (true) {
        int pivot = Partition(numbers, left, right);
        if (pivot == k) {
            return numbers[pivot];
        }
        if (pivot < k) {
            left = pivot + 1;
        } else {
            right = pivot;
        }
    }
}

int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    assert(k < n);
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }
    std::cout << QuickSelect(numbers, k) << std::endl;
    return 0;
}
