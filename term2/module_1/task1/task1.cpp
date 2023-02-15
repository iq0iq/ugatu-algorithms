#include <iostream>
#include <limits>
#include <vector>

int counting(const std::vector<int> &denominations,
             std::vector<unsigned int> &dp,
             std::vector<unsigned int> &last_in) {
  dp[0] = 0;
  for (unsigned int i = 1; i < dp.size(); ++i) {
    for (int j = 0; j < denominations.size(); ++j) {
      if (i >= denominations[j]) {
        if (dp[i - denominations[j]] < dp[i] - 1) {
          last_in[i] = denominations[j];
          dp[i] = dp[i - denominations[j]] + 1;
        }
      }
    }
  }
  return dp.back() == std::numeric_limits<unsigned int>::max() ? -1 : dp.back();
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> denominations(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> denominations[i];
  }
  int s = 0;
  std::cin >> s;
  std::vector<unsigned int> dp(s + 1, std::numeric_limits<unsigned int>::max());
  std::vector<unsigned int> last_in(s + 1);
  std::cout << counting(denominations, dp, last_in) << std::endl;
  if (last_in[s] != 0) {
    while (last_in[s] != 0) {
      std::cout << last_in[s] << ' ';
      s -= last_in[s];
    }
    std::cout << std::endl;
  }
  return 0;
}
