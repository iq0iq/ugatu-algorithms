#include <algorithm>
#include <iostream>
#include <vector>

struct data {
    int year = 0;
    int month = 0;
    int day = 0;
    bool alive = true;
};

bool Comparator(data data1, data data2) {
    if (data1.year == data2.year) {
        if (data1.month == data2.month) {
            return data1.day < data2.day;
        }
        return data1.month < data2.month;
    }
    return data1.year < data2.year;
}

bool change(data &birth, data &death) {  // изменение даты рождения и смерти на период, когда человек мог быть ровестником
    data eighty = birth;
    eighty.year += 80;
    eighty.alive = false;
    if (!Comparator(death, eighty)) {
        death = eighty;
    }
    birth.year += 18;
    return Comparator(birth, death);  // если birth >= death, человек не мог быть ровестником ни для кого
}

void SiftDown(std::vector<data> &array, int Size, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < Size && Comparator(array[i], array[left]))
        largest = left;
    if (right < Size && Comparator(array[largest], array[right]))
        largest = right;
    if (largest != i) {
        std::swap(array[i], array[largest]);
        SiftDown(array, Size, largest);
    }
}

void BuildHeap(std::vector<data> &array, int Size) {
    for (int i = Size / 2 - 1; i >= 0; --i) {
        SiftDown(array, Size, i);
    }
}

void HeapSort(std::vector<data> &array) {
    int heapSize = array.size();
    BuildHeap(array, heapSize);
    for (; heapSize > 1; --heapSize) {
        std::swap(array[0], array[heapSize - 1]);
        SiftDown(array, heapSize - 1, 0);
    }
}


int peers(std::vector<data> &dates) {
    HeapSort(dates);
    int count = 0;
    int Max = 0;  // будущий ответ
    for (int i = 0; i < dates.size(); ++i) {
        count += dates[i].alive ? 1 : -1;
        if (i < dates.size() && dates[i].year == dates[i + 1].year && dates[i].month == dates[i + 1].month && dates[i].day == dates[i + 1].day) {
            continue;
        }
        Max = std::max(Max, count);
    }
    return Max;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<data> dates;
    for (int i = 0; i < n; ++i) {
        data read;
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
