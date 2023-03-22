#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(int vertices_count)
    : matrix(std::vector<std::vector<bool>>(
          vertices_count, std::vector<bool>(vertices_count))) {}

MatrixGraph::MatrixGraph(const IGraph *other)
    : matrix(std::vector<std::vector<bool>>(
          other->VerticesCount(), std::vector<bool>(other->VerticesCount()))) {
  for (std::size_t i = 0; i < matrix.size(); ++i) {
    for (int j : other->FindAllAdjacentIn(i))
      matrix[j][i] = true;
    for (int j : other->FindAllAdjacentOut(i))
      matrix[i][j] = true;
  }
}

void MatrixGraph::AddEdge(std::size_t from, std::size_t to) {
  matrix[from][to] = true;
}

std::size_t MatrixGraph::VerticesCount() const { return matrix.size(); }

std::vector<int> MatrixGraph::FindAllAdjacentIn(std::size_t vertex) const {
  std::vector<int> adjacent_in;
  for (int i = 0; i < matrix.size(); ++i)
    if (matrix[i][vertex])
      adjacent_in.emplace_back(i);
  return adjacent_in;
}

std::vector<int> MatrixGraph::FindAllAdjacentOut(std::size_t vertex) const {
  std::vector<int> adjacent_out;
  for (int i = 0; i < matrix.size(); ++i)
    if (matrix[vertex][i])
      adjacent_out.emplace_back(i);
  return adjacent_out;
}
