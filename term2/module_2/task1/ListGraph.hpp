#include "IGraph.hpp"

class ListGraph : public IGraph {
public:
  explicit ListGraph(std::size_t vertices_count);
  explicit ListGraph(const IGraph *other);

  void AddEdge(std::size_t from, std::size_t to) override;

  std::size_t VerticesCount() const override;

  std::vector<std::size_t> FindAllAdjacentIn(std::size_t vertex) const override;
  std::vector<std::size_t> FindAllAdjacentOut(std::size_t vertex) const override;

private:
  std::vector<std::vector<std::size_t>> in_edges_;
  std::vector<std::vector<size_t>> out_edges_;
};
