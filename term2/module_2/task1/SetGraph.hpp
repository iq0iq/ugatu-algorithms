#include "IGraph.hpp"
#include <unordered_set>

class SetGraph : public IGraph {
public:
  explicit SetGraph(int vertices_count);
  explicit SetGraph(const IGraph *other);

  void AddEdge(std::size_t from, std::size_t to) override;

  std::size_t VerticesCount() const override;

  std::vector<int> FindAllAdjacentIn(std::size_t vertex) const override;
  std::vector<int> FindAllAdjacentOut(std::size_t vertex) const override;

private:
  std::vector<std::unordered_set<int>> in_edges_;
  std::vector<std::unordered_set<int>> out_edges_;
};
