#include "ListGraph.hpp"
#include <iostream>

ListGraph::ListGraph(std::size_t vertices_count)
    : in_edges_(vertices_count), out_edges_(vertices_count) {}

ListGraph::ListGraph(const IGraph *other)
    : in_edges_(other->VerticesCount()), out_edges_(other->VerticesCount()) {
  for (std::size_t i = 0; i < in_edges_.size(); ++i) {
    in_edges_[i] = other->FindAllAdjacentIn(i);
    out_edges_[i] = other->FindAllAdjacentOut(i);
  }
}

void ListGraph::AddEdge(std::size_t from, std::size_t to) {
  in_edges_[to].emplace_back(from);
  out_edges_[from].emplace_back(to);
}

std::size_t ListGraph::VerticesCount() const { return in_edges_.size(); }

std::vector<std::size_t>
ListGraph::FindAllAdjacentIn(std::size_t vertex) const {
  return in_edges_[vertex];
}
std::vector<std::size_t>
ListGraph::FindAllAdjacentOut(std::size_t vertex) const {
  return out_edges_[vertex];
}
