#include "ArcGraph.hpp"

ArcGraph::ArcGraph(int vertices_count) : Size(vertices_count) {}

ArcGraph::ArcGraph(const IGraph *other) {
  Size = other->VerticesCount();
  for (std::size_t i = 0; i < Size; ++i) {
    for (int j : other->FindAllAdjacentOut(i))
      pairs.emplace_back(i, j);
  }
}

void ArcGraph::AddEdge(std::size_t from, std::size_t to) {
  pairs.emplace_back(from, to);
  if (from >= Size)
    Size = from + 1;
  if (to >= Size)
    Size = to + 1;
}

std::size_t ArcGraph::VerticesCount() const { return Size; }

std::vector<int> ArcGraph::FindAllAdjacentIn(std::size_t vertex) const {
  std::vector<int> adjacent_in;
  for (std::pair<int, int> i : pairs)
    if (i.second == vertex)
      adjacent_in.emplace_back(i.first);
  return adjacent_in;
}

std::vector<int> ArcGraph::FindAllAdjacentOut(std::size_t vertex) const {
  std::vector<int> adjacent_out;
  for (std::pair<int, int> i : pairs)
    if (i.first == vertex)
      adjacent_out.emplace_back(i.second);
  return adjacent_out;
}
