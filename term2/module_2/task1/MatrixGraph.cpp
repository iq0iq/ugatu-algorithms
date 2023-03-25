#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(int vertices_count)
    : matrix_(std::vector<std::vector<bool>>(
          vertices_count, std::vector<bool>(vertices_count))) {}

MatrixGraph::MatrixGraph(const IGraph *other)
    : matrix_(std::vector<std::vector<bool>>(
          other->VerticesCount(), std::vector<bool>(other->VerticesCount()))) {
  for (std::size_t i = 0; i < matrix_.size(); ++i) {
    for (std::size_t j : other->FindAllAdjacentIn(i))
      matrix_[j][i] = true;
    for (std::size_t j : other->FindAllAdjacentOut(i))
      matrix_[i][j] = true;
  }
}

void MatrixGraph::AddEdge(std::size_t from, std::size_t to) {
  matrix_[from][to] = true;
}

std::size_t MatrixGraph::VerticesCount() const { return matrix_.size(); }

std::vector<std::size_t>
MatrixGraph::FindAllAdjacentIn(std::size_t vertex) const {
  std::vector<std::size_t> adjacent_in;
  for (std::size_t i = 0; i < matrix_.size(); ++i)
    if (matrix_[i][vertex])
      adjacent_in.emplace_back(i);
  return adjacent_in;
}

std::vector<std::size_t>
MatrixGraph::FindAllAdjacentOut(std::size_t vertex) const {
  std::vector<std::size_t> adjacent_out;
  for (std::size_t i = 0; i < matrix_.size(); ++i)
    if (matrix_[vertex][i])
      adjacent_out.emplace_back(i);
  return adjacent_out;
}
