#include <iostream>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> x(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> x[i];
  }
  int s = 0;
  std::cin >> s;
  std::vector<unsigned int> dp(s + 1, 4'294'967'294);
  std::vector<unsigned int> last_in(s + 1, 0);
  dp[0] = 0;
  for (unsigned int i = 1; i < s + 1; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i >= x[j]) {
        if (dp[i - x[j]] + 1 < dp[i]) {
          last_in[i] = x[j];
          dp[i] = dp[i - x[j]] + 1;
        }
      }
    }
  }
  if (dp[s] == 4'294'967'294) {
    std::cout << -1 << std::endl;
  } else {
    std::cout << dp[s] << std::endl;
  }
  if (last_in[s] != 0) {
    while (last_in[s] != 0) {
      std::cout << last_in[s] << ' ';
      s = s - last_in[s];
    }
    std::cout << std::endl;
  }
  return 0;
}
