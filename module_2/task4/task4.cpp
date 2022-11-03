#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

void Merge(const std::vector<int> &first, const std::vector<int> &second, std::vector<int> &result, int k) {
    int i = 0;
    int j = 0;
    int len1 = first.size();
    int len2 = second.size();
    while (i < len1 && j < len2 && i + j < k) {
        if (second[j] >= first[i]) {
            result[i + j] = first[i];
            ++i;
        } else {
            result[i + j] = second[j];
            ++j;
        }
    }
    while (i < len1 && i + j < k) {
        result[i + j] = first[i];
        ++i;
    }
    while (j < len2 && i + j < k) {
        result[i + j] = second[j];
        ++j;
    }
}
void MergeSort(std::vector<int> &array, int k) {
    int len = array.size();
    if (len <= 1) {
        return;
    }
    int left_half_len = len / 2;
    int right_half_len = len - left_half_len;
    std::vector<int> left_half(left_half_len);
    std::vector<int> right_half(right_half_len);
    for (int i = 0; i < left_half_len; ++i) {
        left_half[i] = array[i];
    }
    for (int i = left_half_len; i < len; ++i) {
        right_half[i - left_half_len] = array[i];
    }
    MergeSort(left_half, k);
    MergeSort(right_half, k);
    Merge(left_half, right_half, array, k);
}

void Add(std::vector<int> &half1, std::vector<int> &half2, int value, int k, int i) {
    half2.push_back(value);
    if ((i + 1) % k == 0) {
        MergeSort(half2, k);
        std::vector<int> result(k);
        Merge(half1, half2, result, k);
        half1 = result;  // merged both vectors reducing the total number of arguments to k, the result in half1
        half2.clear();
    }
}
int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    assert(k <= n);
    std::vector<int> half1;
    std::vector<int> half2;
    int value = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        Add(half1, half2, value, k, i);
    }
    MergeSort(half2, k);
    std::vector<int> result(k);
    Merge(half1, half2, result, k);
    for (int i = 0; i < k; ++i) {
        std::cout << result[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}
