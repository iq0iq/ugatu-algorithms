#include <iostream>
#include <string>
#include <vector>

std::vector<unsigned int> Stoi(std::string &x) {
  std::vector<unsigned int> bigint_x;
  for (int i = x.size() - 1; i >= 0; i -= 9) {
    bigint_x.push_back(i < 8 ? std::stoi(x.substr(0, i + 1))
                             : std::stoi(x.substr(i - 8, 9)));
  }
  return bigint_x;
}

std::vector<unsigned int> sum(const std::vector<unsigned int> &bigint_x,
                              const std::vector<unsigned int> &bigint_y) {
  std::vector<unsigned int> result = bigint_x;
  int in_mind = 0;
  for (unsigned int i = 0;
       i < std::max(result.size(), bigint_y.size()) || in_mind != 0; ++i) {
    if (i >= result.size())
      result.push_back(0);
    result[i] += ((i < bigint_y.size() ? bigint_y[i] : 0) + in_mind);
    in_mind = result[i] / 1'000'000'000;
    result[i] %= 1'000'000'000;
  }
  return result;
}

void print(std::vector<unsigned int> &bigint_x) {
  if (bigint_x.size() == 1 && bigint_x[0] == 0) {
    std::cout << 0;
    return;
  }
  std::cout << bigint_x.back();
  for (int i = bigint_x.size() - 2; i >= 0; --i) {
    unsigned int copy = bigint_x[i];
    while (copy != 0 && copy < 100'000'000) {
      std::cout << 0;
      copy *= 10;
    }
    if (copy == 0)
      std::cout << "00000000";
    std::cout << bigint_x[i];
  }
}

int main() {
  std::string x;
  std::string y;
  std::cin >> x >> y;
  auto bigint_x = Stoi(x);
  auto bigint_y = Stoi(y);
  auto result = sum(bigint_x, bigint_y);
  print(result);
  std::cout << std::endl;
  return 0;
}
