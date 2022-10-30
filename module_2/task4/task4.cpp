#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

void Merge(const int *first, int len1, const int *second, int len2, int *result, int k) {
    int i = 0, j = 0;
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
void MergeSort(int *array, int len, int k) {
    if (len <= 1) {
        return;
    }
    int len1 = len / 2;
    int len2 = len - len1;
    MergeSort(array, len1, k);
    MergeSort(array + len1, len2, k);
    int *result = new int[len];
    Merge(array, len1, array + len1, len2, result, k);
    memcpy(array, result, sizeof(int) * len);
    delete[] result;
}

void Add(std::vector<int> &half1, std::vector<int> &half2, int value, int k, int i) {
    half2.push_back(value);
    if ((i + 1) % k == 0) {
        MergeSort(half2.data(), half2.size(), k);
        std::vector<int> result(k);
        Merge(half1.data(), half1.size(), half2.data(), half2.size(), result.data(), k);
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
    MergeSort(half2.data(), half2.size(), k);
    std::vector<int> result(k);
    Merge(half1.data(), half1.size(), half2.data(), half2.size(), result.data(), k);
    for (int i = 0; i < k; ++i) {
        std::cout << result[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}
