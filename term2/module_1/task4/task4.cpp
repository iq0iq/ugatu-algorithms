#include <iostream>
#include <string>
#include <vector>

void print(std::vector<unsigned int> &bigint_x) {
  if (bigint_x.size() == 1 && bigint_x[0] == 0) {
    std::cout << 0 << std::endl;
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
  std::cout << std::endl;
}

void sum(const std::string &x, const std::string &y) {
  std::vector<unsigned int> bigint_x;
  std::vector<unsigned int> bigint_y;
  for (int i = x.size() - 1; i >= 0; i -= 9) {
    bigint_x.push_back(i < 8 ? std::stoi(x.substr(0, i + 1))
                             : std::stoi(x.substr(i - 8, 9)));
  }
  for (int i = y.size() - 1; i >= 0; i -= 9) {
    bigint_y.push_back(i < 8 ? std::stoi(y.substr(0, i + 1))
                             : std::stoi(y.substr(i - 8, 9)));
  }
  int in_mind = 0;
  for (unsigned int i = 0;
       i < std::max(bigint_x.size(), bigint_y.size()) || in_mind != 0; ++i) {
    if (i >= bigint_x.size())
      bigint_x.push_back(0);
    bigint_x[i] += ((i < bigint_y.size() ? bigint_y[i] : 0) + in_mind);
    in_mind = bigint_x[i] / 1'000'000'000;
    bigint_x[i] %= 1'000'000'000;
  }
  print(bigint_x);
}

int main() {
  std::string x, y;
  std::cin >> x >> y;
  sum(x, y);
  return 0;
}
