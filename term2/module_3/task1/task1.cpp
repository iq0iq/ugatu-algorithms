#include <iostream>
#include <string>
#include <vector>

std::vector<uint32_t> z_function(const std::string &pattern,
                                 const std::string &text) {

  std::vector<uint32_t> z(pattern.size());
  z[0] = pattern.size();
  uint32_t left = 0;
  uint32_t right = 0;
  for (uint32_t i = 1; i < pattern.size(); ++i) {
    if (i < right)
      z[i] = std::min(z[i - left], right - i);
    while (i + z[i] < pattern.size() && pattern[z[i]] == pattern[i + z[i]])
      ++z[i];
    if (i + z[i] >= right) {
      left = i;
      right = i + z[i];
    }
  }

  left = 0;
  right = 0;
  std::vector<uint32_t> answer;
  for (uint32_t i = 0; i < text.size(); ++i) {
    uint32_t this_z = 0;
    if (i < right)
      this_z = std::min(z[i - left], right - i);
    while (i + this_z < text.size() && pattern[this_z] == text[i + this_z])
      ++this_z;
    if (i + this_z >= right) {
      left = i;
      right = i + this_z;
    }
    if (this_z == pattern.size()) {
      answer.emplace_back(i);
    }
  }
  return answer;
}

int main() {
  std::string pattern;
  std::cin >> pattern;
  std::string text;
  std::cin >> text;
  auto answer = z_function(pattern, text);
  for (uint32_t i : answer)
    std::cout << i << ' ';
  std::cout << std::endl;
  return 0;
}
