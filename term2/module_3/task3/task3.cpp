#include <iostream>
#include <string>
#include <vector>

uint64_t Manacher(const std::string &s, bool odd) {
  uint64_t sum = 0;
  std::vector<uint32_t> result(s.size(), odd);
  uint32_t left = 0;
  uint32_t right = 1;
  for (uint32_t i = 1; i < s.size(); ++i) {
    uint32_t &current_result = result[i];
    if (i < right) {
      uint32_t symbol_index = left + right - i - odd;
      current_result = std::min(result[symbol_index], right - i);
    }
    while (i + current_result < s.size() && i - !odd >= current_result &&
           s[i + current_result] == s[i - current_result - !odd])
      ++current_result;
    if (i + current_result > right) {
      right = i + current_result;
      left = i - current_result + odd;
    }
    sum += (current_result - odd);
  }
  return sum;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << Manacher(s, true) + Manacher(s, false) << std::endl;
  return 0;
}
