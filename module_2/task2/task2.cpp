#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

struct date {
    int year = 0;
    int month = 0;
    int day = 0;
    bool alive = true;
};

bool Comparator(const date &date1, const date &date2) {
    return std::tie(date1.year, date1.month, date1.day) < std::tie(date2.year, date2.month, date2.day);
}

bool change(date &birth, date &death) {  // изменение даты рождения и смерти на период, когда человек мог быть ровестником
    date eighty = birth;
    eighty.year += 80;
    eighty.alive = false;
    if (!Comparator(death, eighty)) {
        death = eighty;
    }
    birth.year += 18;
    return Comparator(birth, death);  // если birth >= death, человек не мог быть ровестником ни для кого
}

void SiftDown(std::vector<date> &array, int Size, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < Size && Comparator(array[i], array[left])) largest = left;
    if (right < Size && Comparator(array[largest], array[right])) largest = right;
    if (largest != i) {
        std::swap(array[i], array[largest]);
        SiftDown(array, Size, largest);
    }
}

void BuildHeap(std::vector<date> &array, int Size) {
    for (int i = Size / 2 - 1; i >= 0; --i) {
        SiftDown(array, Size, i);
    }
}

void HeapSort(std::vector<date> &array) {
    int heapSize = array.size();
    BuildHeap(array, heapSize);
    for (; heapSize > 1; --heapSize) {
        std::swap(array[0], array[heapSize - 1]);
        SiftDown(array, heapSize - 1, 0);
    }
}

int peers(std::vector<date> &dates) {
    HeapSort(dates);
    int count = 0;
    int Max = 0;  // будущий ответ
    for (int i = 0; i < dates.size(); ++i) {
        count += dates[i].alive ? 1 : -1;
        if (i < dates.size() && dates[i].year == dates[i + 1].year &&
            dates[i].month == dates[i + 1].month &&
            dates[i].day == dates[i + 1].day) {
            continue;
        }
        Max = std::max(Max, count);
    }
    return Max;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<date> dates;
    for (int i = 0; i < n; ++i) {
        date read;
        std::cin >> read.day >> read.month >> read.year;
        dates.push_back(read);
        std::cin >> read.day >> read.month >> read.year;
        read.alive = false;
        dates.push_back(read);
        if (!change(dates[dates.size() - 2], dates[dates.size() - 1])) {
            dates.pop_back();
            dates.pop_back();
        }
    }
    std::cout << peers(dates) << std::endl;
    return 0;
}
