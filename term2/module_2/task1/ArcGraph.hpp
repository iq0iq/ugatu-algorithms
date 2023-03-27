#include "IGraph.hpp"

class ArcGraph : public IGraph {
public:
  explicit ArcGraph(std::size_t vertices_count);
  explicit ArcGraph(const IGraph *other);

  void AddEdge(std::size_t from, std::size_t to) override;

  std::size_t VerticesCount() const override;

  std::vector<std::size_t> FindAllAdjacentIn(std::size_t vertex) const override;
  std::vector<std::size_t>
  FindAllAdjacentOut(std::size_t vertex) const override;

private:
  std::vector<std::pair<std::size_t, std::size_t>> pairs_;
  std::size_t size_;
};
