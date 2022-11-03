#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

void Merge(std::vector<int> &first, std::vector<int> &second, std::vector<int> &result, int k) {
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
    int len1 = len / 2;
    int len2 = len - len1;
    std::vector<int> half1(len1);
    std::vector<int> half2(len2);
    for (int i = 0; i < len1; ++i) {
        half1[i] = array[i];
    }
    for (int i = len1; i < len; ++i) {
        half2[i - len1] = array[i];
    }
    MergeSort(half1, k);
    MergeSort(half2, k);
    Merge(half1, half2, array, k);
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
