#pragma once
#include <vector>

struct IGraph {
  virtual ~IGraph() = default;

  virtual void AddEdge(std::size_t from, std::size_t to) = 0;

  virtual std::size_t VerticesCount() const = 0;

  virtual std::vector<int> FindAllAdjacentIn(std::size_t vertex) const = 0;
  virtual std::vector<int> FindAllAdjacentOut(std::size_t vertex) const = 0;
};
