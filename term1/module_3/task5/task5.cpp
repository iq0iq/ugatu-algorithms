#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

size_t Hash1(const std::string &key, size_t size) {
    size_t hash = 0;
    for (char i: key)
        hash = (hash * 27 + i - 'a') % size;
    return hash;
}

size_t Hash2(const std::string &key, size_t size) {
    if (key.empty()) return 0;
    size_t hash = 0;
    int i = static_cast<int>(key.size()) - 1;
    for (; i >= 0; --i)
        hash = (hash * 27 + key[i] - 'a') % size;
    return (2 * hash + 1) % size;
}

class HashTable {
public:
    explicit HashTable(int size = 8) : table(size) {}
    bool Has(const std::string &key) const;
    bool Add(const std::string &key);
    bool Remove(const std::string &key);

private:
    std::vector<std::string> table;
    int count = 0;  // количество занятых ячеек
    void Growth();
};

void HashTable::Growth() {
    std::vector<std::string> new_table(table.size() * 2);
    for (std::string i: table) {
        if (!i.empty() && i != "DELETED") {
            for (int j = 0; j < new_table.size(); ++j) {
                size_t hash = (Hash1(i, new_table.size()) + j * Hash2(i, new_table.size())) % new_table.size();
                if (new_table[hash].empty()) {
                    new_table[hash] = i;
                    break;
                }
            }
        }
    }
    table = new_table;
}

bool HashTable::Has(const std::string &key) const {
    for (int i = 0; i < table.size(); ++i) {
        size_t hash = (Hash1(key, table.size()) + i * Hash2(key, table.size())) % table.size();
        if (table[hash].empty()) return false;
        if (table[hash] == key) return true;
    }
    return false;
}

bool HashTable::Add(const std::string &key) {
    if (count >= 0.75 * table.size()) Growth();
    for (int i = 0; i < table.size(); ++i) {
        size_t hash = (Hash1(key, table.size()) + i * Hash2(key, table.size())) % table.size();
        if (table[hash].empty() || table[hash] == "DELETED") {
            table[hash] = key;
            ++count;
            return true;
        }
        if (table[hash] == key) return false;
    }
    return false;
}

bool HashTable::Remove(const std::string &key) {
    for (int i = 0; i < table.size(); ++i) {
        size_t hash = (Hash1(key, table.size()) + i * Hash2(key, table.size())) % table.size();
        if (table[hash].empty()) return false;
        if (table[hash] == key) {
            table[hash] = "DELETED";
            --count;
            return true;
        }
    }
    return false;
}

int main() {
    char type;
    std::string str;
    HashTable table;
    std::vector<bool> answers;
    while (std::cin >> type >> str) {
        switch (type) {
            case '+':
                answers.emplace_back(table.Add(str));
                break;
            case '-':
                answers.emplace_back(table.Remove(str));
                break;
            case '?':
                answers.emplace_back(table.Has(str));
        }
    }
    for (bool i: answers)
        std::cout << (i ? "OK" : "FAIL") << std::endl;
    return 0;
}
