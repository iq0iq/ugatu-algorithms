#include <iostream>
#include <string>
#include <vector>

std::string min_string(const std::vector<uint32_t> &prefix) {
  const uint8_t alphabet_size = 26;
  std::string result = "a";
  for (uint32_t i = 1; i < prefix.size(); ++i) {
    if (prefix[i] != 0) {
      result.push_back(result[prefix[i] - 1]);
    } else {
      uint32_t k = i - 1;
      std::vector<bool> allowed_letters(alphabet_size - 1, true);
      while (prefix[k] != 0) {
        allowed_letters[result[prefix[k]] - 'a'] = false;
        k = prefix[k] - 1;
        if (prefix[k] == k)
          break;
      }
      for (char j = 1; j < alphabet_size; ++j) {
        if (allowed_letters[j]) {
          result.push_back('a' + j);
          break;
        }
      }
    }
  }
  return result;
}

int main() {
  std::vector<uint32_t> prefix;
  uint32_t x = 0;
  while (std::cin >> x)
    prefix.emplace_back(x);
  std::cout << min_string(prefix) << std::endl;
  return 0;
}
