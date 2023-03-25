#include <iostream>
#include <vector>

class Graph {
public:
  explicit Graph(std::size_t vertices_count);

  void AddEdge(std::size_t from, std::size_t to);

  std::size_t VerticesCount() const;

  std::vector<std::size_t> FindAllAdjacent(std::size_t vertex) const;

private:
  std::vector<std::vector<std::size_t>> edges;
};

Graph::Graph(std::size_t vertices_count) : edges(vertices_count) {}

void Graph::AddEdge(std::size_t from, std::size_t to) {
  edges[to].emplace_back(from);
  edges[from].emplace_back(to);
}

std::size_t Graph::VerticesCount() const { return edges.size(); }

std::vector<std::size_t> Graph::FindAllAdjacent(std::size_t vertex) const {
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
    } else if (color[current] == color[i])
      return false;
  }
  return true;
}

bool MainDFS(Graph &graph) {  // returns true if the graph is bipartite
  std::size_t size = graph.VerticesCount();
  std::vector<bool> used(size);
  std::vector<bool> color(
      size);  // false - first part of vertexes, true - second
  for (int i = 0; i < size; ++i)
    if (!used[i] && !DFS(graph, used, color, i))
      return false;
  return true;
}

int main() {
  int size = 0;
  int n = 0;
  std::cin >> size >> n;
  std::size_t from = 0;
  std::size_t to = 0;
  Graph graph(size);
  for (int i = 0; i < n; ++i) {
    std::cin >> from >> to;
    graph.AddEdge(from, to);
  }
  std::cout << (MainDFS(graph) ? "YES" : "NO") << std::endl;
  return 0;
}
