#include <iostream>
#include <unordered_set>
#include <vector>

class MatrixGraph {
public:
  explicit MatrixGraph(std::size_t vertices_count);
  void AddEdge(std::size_t from, std::size_t to, double weight);
  std::size_t VerticesCount() const;
  std::vector<std::size_t> FindAllAdjacentOut(std::size_t vertex) const;
  double FindWeight(std::size_t from, std::size_t to) const;

private:
  std::vector<std::vector<double>> matrix_;
};

MatrixGraph::MatrixGraph(std::size_t vertices_count)
    : matrix_(vertices_count, std::vector<double>(vertices_count, -1)) {}

void MatrixGraph::AddEdge(std::size_t from, std::size_t to, double weight) {
  matrix_[from][to] = weight;
}

std::size_t MatrixGraph::VerticesCount() const { return matrix_.size(); }

std::vector<std::size_t>
MatrixGraph::FindAllAdjacentOut(std::size_t vertex) const {
  std::vector<std::size_t> adjacent_out;
  for (std::size_t i = 0; i < matrix_.size(); ++i)
    if (matrix_[vertex][i] != -1)
      adjacent_out.emplace_back(i);
  return adjacent_out;
}

double MatrixGraph::FindWeight(std::size_t from, std::size_t to) const {
  return matrix_[from][to];
}

bool Relax(MatrixGraph &graph, std::vector<double> &prices, std::size_t from,
           std::size_t to) {
  if (prices[to] < prices[from] * graph.FindWeight(from, to)) {
    prices[to] = prices[from] * graph.FindWeight(from, to);
    return true;
  }
  return false;
}

bool BellmanFord(MatrixGraph &graph) {
  std::vector<double> prices(graph.VerticesCount());
  for (std::size_t i : graph.FindAllAdjacentOut(0))
    prices[i] = graph.FindWeight(0, i);
  std::unordered_set<std::size_t> relaxed;
  for (std::size_t i = 0; i < graph.VerticesCount(); ++i)
    relaxed.emplace(i);
  std::unordered_set<std::size_t> being_relaxed;

  for (std::size_t i = 0; i < graph.VerticesCount() - 1; ++i) {
    for (std::size_t from : relaxed) {
      for (std::size_t to : graph.FindAllAdjacentOut(from)) {
        if (Relax(graph, prices, from, to))
          being_relaxed.emplace(to);
      }
    }
    if (being_relaxed.empty())
      return true;
    relaxed = std::move(being_relaxed);
  }

  for (std::size_t from : relaxed) {
    for (std::size_t to : graph.FindAllAdjacentOut(from)) {
      if (Relax(graph, prices, from, to))
        return false;
    }
  }
  return true;
}

int main() {
  std::size_t n = 0;
  std::cin >> n;
  MatrixGraph graph(n);
  double weight = 0;
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = 0; j < n; ++j) {
      if (i == j)
        continue;
      std::cin >> weight;
      graph.AddEdge(i, j, weight);
    }
  }
  std::cout << ((BellmanFord(graph)) ? "NO" : "YES");
  std::cout << std::endl;
  return 0;
}
