#include "IGraph.hpp"

class ListGraph : public IGraph {
public:
  explicit ListGraph(int vertices_count);
  explicit ListGraph(const IGraph *other);

  void AddEdge(std::size_t from, std::size_t to) override;

  std::size_t VerticesCount() const override;

  std::vector<int> FindAllAdjacentIn(std::size_t vertex) const override;
  std::vector<int> FindAllAdjacentOut(std::size_t vertex) const override;

private:
  std::vector<std::vector<int>> in_edges_;
  std::vector<std::vector<int>> out_edges_;
};
