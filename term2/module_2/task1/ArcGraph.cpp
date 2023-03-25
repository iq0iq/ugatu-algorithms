#include "ArcGraph.hpp"

ArcGraph::ArcGraph(int vertices_count) : size_(vertices_count) {}

ArcGraph::ArcGraph(const IGraph *other) {
  size_ = other->VerticesCount();
  for (std::size_t i = 0; i < size_; ++i) {
    for (std::size_t j : other->FindAllAdjacentOut(i))
      pairs_.emplace_back(i, j);
  }
}

void ArcGraph::AddEdge(std::size_t from, std::size_t to) {
  pairs_.emplace_back(from, to);
  if (from >= size_)
    size_ = from + 1;
  if (to >= size_)
    size_ = to + 1;
}

std::size_t ArcGraph::VerticesCount() const { return size_; }

std::vector<std::size_t> ArcGraph::FindAllAdjacentIn(std::size_t vertex) const {
  std::vector<std::size_t> adjacent_in;
  for (std::pair<std::size_t, std::size_t> i : pairs_)
    if (i.second == vertex)
      adjacent_in.emplace_back(i.first);
  return adjacent_in;
}

std::vector<std::size_t>
ArcGraph::FindAllAdjacentOut(std::size_t vertex) const {
  std::vector<std::size_t> adjacent_out;
  for (std::pair<std::size_t, std::size_t> i : pairs_)
    if (i.first == vertex)
      adjacent_out.emplace_back(i.second);
  return adjacent_out;
}
