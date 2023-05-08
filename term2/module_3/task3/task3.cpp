#include <iostream>
#include <string>
#include <vector>

uint64_t Manacher(const std::string &s) {
  uint64_t sum = 0;
  std::vector<uint32_t> result(s.size(), 1);
  uint32_t left = 0;
  uint32_t right = 1;
  for (uint32_t i = 1; i < s.size(); ++i) {  // odd
    uint32_t &current_result = result[i];
    if (i < right) {
      uint32_t symbol_index = left + right - i - 1;
      current_result = std::min(result[symbol_index], right - i);
    }
    while (i + current_result < s.size() && i >= current_result &&
           s[i + current_result] == s[i - current_result])
      ++current_result;
    if (i + current_result > right) {
      right = i + current_result;
      left = i - current_result + 1;
    }
    sum += (current_result - 1);
  }

  result = std::vector<uint32_t>(s.size());
  left = 0;
  right = 1;
  for (uint32_t i = 1; i < s.size(); ++i) {  // even
    uint32_t &current_result = result[i];
    if (i < right) {
      uint32_t symbol_index = left + right - i;
      current_result = std::min(result[symbol_index], right - i);
    }
    while (i + current_result < s.size() && i - 1 >= current_result &&
           s[i + current_result] == s[i - current_result - 1])
      ++current_result;
    if (i + current_result > right) {
      right = i + current_result;
      left = i - current_result;
    }
    sum += current_result;
  }

  return sum;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << Manacher(s) << std::endl;
  return 0;
}
