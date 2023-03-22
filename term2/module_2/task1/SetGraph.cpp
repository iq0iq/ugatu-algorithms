#include "SetGraph.hpp"

SetGraph::SetGraph(int vertices_count)
    : in_edges_(vertices_count), out_edges_(vertices_count) {}

SetGraph::SetGraph(const IGraph *other)
    : in_edges_(other->VerticesCount()), out_edges_(other->VerticesCount()) {
  for (std::size_t i = 0; i < in_edges_.size(); ++i) {
    for (int j : other->FindAllAdjacentIn(i))
      in_edges_[i].emplace(j);
    for (int j : other->FindAllAdjacentOut(i))
      out_edges_[i].emplace(j);
  }
}

void SetGraph::AddEdge(std::size_t from, std::size_t to) {
  in_edges_[to].emplace(from);
  out_edges_[from].emplace(to);
}

std::size_t SetGraph::VerticesCount() const { return in_edges_.size(); }

std::vector<int> SetGraph::FindAllAdjacentIn(std::size_t vertex) const {
  std::vector<int> adjacent_in;
  for (int i : in_edges_[vertex])
    adjacent_in.emplace_back(i);
  return adjacent_in;
}

std::vector<int> SetGraph::FindAllAdjacentOut(std::size_t vertex) const {
  std::vector<int> adjacent_out;
  for (int i : out_edges_[vertex])
    adjacent_out.emplace_back(i);
  return adjacent_out;
}
