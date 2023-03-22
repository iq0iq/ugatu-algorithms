#include <iostream>
#include <vector>

void dfs(const std::vector<std::vector<unsigned int>> &tree,
         std::vector<bool> &used, std::vector<unsigned int> &depth,
         unsigned int current) {
  used[current] = true;
  for (unsigned int i : tree[current]) {
    if (!used[i]) {
      depth[i] = depth[current] + 1;
      dfs(tree, used, depth, i);
    }
  }
}

void find_depth(const std::vector<std::vector<unsigned int>> &tree,
                std::vector<unsigned int> &depth,
                std::vector<unsigned int> &depth2) {
  unsigned int n = tree.size();
  std::vector<bool> used(n, false);
  dfs(tree, used, depth, 0);
  unsigned int deepest1 = 0;
  for (unsigned int i = 0; i < n; ++i) {
    if (depth[i] > depth[deepest1])
      deepest1 = i;
    used[i] = false;
  }
  depth[deepest1] = 0;
  dfs(tree, used, depth, deepest1);

  unsigned int deepest2 = 0;
  for (unsigned int i = 0; i < n; ++i) {
    if (depth[i] > depth[deepest2])
      deepest2 = i;
    used[i] = false;
  }
  dfs(tree, used, depth2, deepest2);
}

int main() {
  unsigned int n = 0;
  std::cin >> n;
  std::vector<std::vector<unsigned int>> tree(n);
  unsigned int x = 0;
  unsigned int y = 0;
  for (unsigned int i = 1; i < n; ++i) {
    std::cin >> x >> y;
    tree[x].push_back(y);
    tree[y].push_back(x);
  }
  std::vector<unsigned int> depth(n);
  std::vector<unsigned int> depth2(n);
  find_depth(tree, depth, depth2);
  for (int i = 0; i < n; ++i) {
    std::cout << std::max(depth[i], depth2[i]) << std::endl;
  }
  return 0;
}
