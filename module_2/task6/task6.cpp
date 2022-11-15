#include "sort.h"
#include <iostream>
#include <stack>

void SortSmall(unsigned int *arr, unsigned int size) {
    if (size <= 1) return;
    if (size == 2) {
        if (arr[0] > arr[1]) std::swap(arr[0], arr[1]);
        return;
    }
    for (int i = 1; i < size; ++i) {
        int tmp = arr[i];
        int j = i - 1;
        for (; j >= 0 && tmp < arr[j]; --j) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = tmp;
    }

}

void Median(unsigned int *arr, unsigned int size) {
    if (arr[0] < arr[(size - 1) / 2]) {
        std::swap(arr[0], arr[(size - 1) / 2]);
    }
    if (arr[size - 1] < arr[(size - 1) / 2]) {
        std::swap(arr[size - 1], arr[(size - 1) / 2]);
    }
    if (arr[size - 1] < arr[0]) {
        std::swap(arr[size - 1], arr[0]);
    }
}

void Sort(unsigned int *arr, unsigned int size) {
    using ll = unsigned int;
    std::stack<std::pair<ll, ll>> indexes;
    indexes.emplace(0, size);
    while (!indexes.empty()) {
        auto [start, length] = indexes.top();
        if (length <= 18) {
            SortSmall(arr + start, length);
            indexes.pop();
            continue;
        }
        auto *array = arr + start;
        Median(array, length);
        int i = length - 1, j = length - 1;
        while (j >= 0) {
            for (; array[j] < array[0]; --j) {}
            std::swap(array[i--], array[j--]);
        }
        indexes.pop();
        if (length > i + 3) indexes.emplace(start + i + 2, length - i - 2);
        if (i > 0) indexes.emplace(start, i + 1);
    }
}
