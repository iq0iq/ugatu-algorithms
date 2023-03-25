#include "IGraph.hpp"
#include <unordered_set>

class SetGraph : public IGraph {
public:
  explicit SetGraph(int vertices_count);
  explicit SetGraph(const IGraph *other);

  void AddEdge(std::size_t from, std::size_t to) override;

  std::size_t VerticesCount() const override;

  std::vector<std::size_t> FindAllAdjacentIn(std::size_t vertex) const override;
  std::vector<std::size_t> FindAllAdjacentOut(std::size_t vertex) const override;

private:
  std::vector<std::unordered_set<std::size_t>> in_edges_;
  std::vector<std::unordered_set<std::size_t>> out_edges_;
};
