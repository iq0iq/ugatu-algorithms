#include <iostream>
#include <vector>

class Graph {
public:
  explicit Graph(int vertices_count);

  void AddEdge(std::size_t from, std::size_t to);

  std::size_t VerticesCount() const;

  std::vector<int> FindAllAdjacent(std::size_t vertex) const;

private:
  std::vector<std::vector<int>> edges;
};

Graph::Graph(int vertices_count) : edges(vertices_count) {}

void Graph::AddEdge(std::size_t from, std::size_t to) {
  edges[to].emplace_back(from);
  edges[from].emplace_back(to);
}

std::size_t Graph::VerticesCount() const { return edges.size(); }

std::vector<int> Graph::FindAllAdjacent(std::size_t vertex) const {
  return edges[vertex];
}

bool DFS(Graph &graph, std::vector<bool> &used, std::vector<bool> &color,
         int current) {
  used[current] = true;
  for (int i : graph.FindAllAdjacent(current)) {
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

bool MainDFS(Graph &graph) {  // returns true if the graph is bipartite
  std::size_t Size = graph.VerticesCount();
  std::vector<bool> used(Size);
  std::vector<bool> color(Size);  // false - first part of vertexes, true - second
  for (int i = 0; i < Size; ++i)
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
  Graph graph(Size);
  for (int i = 0; i < n; ++i) {
    std::cin >> from >> to;
    graph.AddEdge(from, to);
  }
  if (MainDFS(graph)) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}
