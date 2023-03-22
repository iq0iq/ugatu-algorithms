#include <iostream>
#include <vector>

bool DFS(std::vector<std::vector<int>> &graph, std::vector<bool> &used,
         std::vector<bool> &color, int current) {
  used[current] = true;
  for (int i : graph[current]) {
    if (!used[i]) {
      color[i] = !color[current];
      if (!DFS(graph, used, color, i))
        return false;
    }
    if (used[i] && color[current] == color[i])
      return false;
  }
  return true;
}

bool MainDFS(std::vector<std::vector<int>>
                 &graph) {  // returns true if the graph is bipartite
  std::vector<bool> used(graph.size());
  std::vector<bool> color(
      graph.size());  // false - first part of vertexes, true - second
  for (int i = 0; i < graph.size(); ++i)
    if (!used[i] && !DFS(graph, used, color, i))
      return false;
  return true;
}

int main() {
  int Size = 0;
  int n = 0;
  std::cin >> Size >> n;
  int from = 0;
  int to = 0;
  std::vector<std::vector<int>> graph(Size);
  for (int i = 0; i < n; ++i) {
    std::cin >> from >> to;
    graph[from].emplace_back(to);
    graph[to].emplace_back(from);
  }
  if (MainDFS(graph)) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}
