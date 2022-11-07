#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void CountingSort(std::vector<std::string> &strings, int left, int right, int digit) {
    if (right == left) {
        return;
    }
    std::vector<int> symbols[257];  // symbols[i] - вектор с номерами строк, начинающихся на символ с номером i
    for (int i = left; i <= right; ++i) {
        if (strings[i].size() <= digit) {
            symbols[0].push_back(i);
        } else {
            symbols[int(strings[i][digit])].push_back(i);
        }
    }
    std::vector<std::string> interval;
    for (int i = 0; i < 257; ++i) {
        for (int j: symbols[i]) {
            interval.push_back(strings[j]);
        }
    }
    for (int i = left; i <= right; ++i) {
        strings[i] = interval[i - left];
    }
}

void MSDSort(std::vector<std::string> &strings, int left, int right, int digit, int max_digit) {
    CountingSort(strings, left, right, digit);
    if (right == left || digit == max_digit) { return; }
    int start = left;
    for (int i = left; i < right; ++i) {
        if (strings[i].size() <= digit && strings[i + 1].size() > digit || strings[i][digit] != strings[i + 1][digit]) {
            MSDSort(strings, start, i, digit + 1, max_digit);
            start = i + 1;
        }
    }
    MSDSort(strings, start, right, digit + 1, max_digit);
}

int main() {
    std::vector<std::string> strings;
    std::string element;
    int max_digit = 0;
    while (std::cin >> element) {
        strings.push_back(element);
        if (element.size() - 1 > max_digit) {
            max_digit = element.size() - 1;
        }
    }
    MSDSort(strings, 0, strings.size() - 1, 0, max_digit);
    for (std::string s: strings) {
        std::cout << s << std::endl;
    }
    return 0;
}
