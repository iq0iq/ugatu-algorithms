#include <iostream>
#include <vector>

unsigned long long DP(const unsigned int n) {
  std::vector<std::vector<unsigned long long>> dp(
      n + 1, std::vector<unsigned long long>(n + 1));
  for (unsigned int j = 0; j <= n; ++j)
    dp[0][j] = 1;
  for (unsigned int i = 1; i <= n; ++i) {
    for (unsigned int j = 1; j <= n; ++j) {
      dp[i][j] = dp[i][j - 1];
      if (i >= j) {
        dp[i][j] += dp[i - j][j - 1];
      }
    }
  }
  return dp.back().back();
}

int main() {
  unsigned int n = 0;
  std::cin >> n;
  std::cout << DP(n) << std::endl;
  return 0;
}
