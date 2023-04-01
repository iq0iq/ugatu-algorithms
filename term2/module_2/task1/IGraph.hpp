#pragma once
#include <vector>

struct IGraph {
  virtual ~IGraph() = default;

  virtual void AddEdge(std::size_t from, std::size_t to) = 0;

  virtual std::size_t VerticesCount() const = 0;

  virtual std::vector<std::size_t>
  FindAllAdjacentIn(std::size_t vertex) const = 0;
  virtual std::vector<std::size_t>
  FindAllAdjacentOut(std::size_t vertex) const = 0;
};
