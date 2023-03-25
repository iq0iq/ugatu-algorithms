#include "IGraph.hpp"

class ArcGraph : public IGraph {
public:
  explicit ArcGraph(int vertices_count);
  explicit ArcGraph(const IGraph *other);

  void AddEdge(std::size_t from, std::size_t to) override;

  std::size_t VerticesCount() const override;

  std::vector<int> FindAllAdjacentIn(std::size_t vertex) const override;
  std::vector<int> FindAllAdjacentOut(std::size_t vertex) const override;

private:
  std::vector<std::pair<int, int>> pairs;
  std::size_t Size;
};
