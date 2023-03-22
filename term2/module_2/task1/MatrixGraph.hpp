#include "IGraph.hpp"

class MatrixGraph : public IGraph {
public:
  explicit MatrixGraph(int vertices_count);
  explicit MatrixGraph(const IGraph *other);

  void AddEdge(std::size_t from, std::size_t to) override;

  std::size_t VerticesCount() const override;

  std::vector<int> FindAllAdjacentIn(std::size_t vertex) const override;
  std::vector<int> FindAllAdjacentOut(std::size_t vertex) const override;

private:
  std::vector<std::vector<bool>> matrix;
};
