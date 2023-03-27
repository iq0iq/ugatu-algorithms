#include "SetGraph.hpp"

SetGraph::SetGraph(std::size_t vertices_count)
    : in_edges_(vertices_count), out_edges_(vertices_count) {}

SetGraph::SetGraph(const IGraph *other)
    : in_edges_(other->VerticesCount()), out_edges_(other->VerticesCount()) {
  for (std::size_t i = 0; i < in_edges_.size(); ++i) {
    for (std::size_t j : other->FindAllAdjacentIn(i))
      in_edges_[i].emplace(j);
    for (std::size_t j : other->FindAllAdjacentOut(i))
      out_edges_[i].emplace(j);
  }
}

void SetGraph::AddEdge(std::size_t from, std::size_t to) {
  in_edges_[to].emplace(from);
  out_edges_[from].emplace(to);
}

std::size_t SetGraph::VerticesCount() const { return in_edges_.size(); }

std::vector<std::size_t> SetGraph::FindAllAdjacentIn(std::size_t vertex) const {
  std::vector<std::size_t> adjacent_in;
  for (std::size_t i : in_edges_[vertex])
    adjacent_in.emplace_back(i);
  return adjacent_in;
}

std::vector<std::size_t> SetGraph::FindAllAdjacentOut(std::size_t vertex) const {
  std::vector<std::size_t> adjacent_out;
  for (std::size_t i : out_edges_[vertex])
    adjacent_out.emplace_back(i);
  return adjacent_out;
}
