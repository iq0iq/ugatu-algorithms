#include "ArcGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include <iostream>
#include <random>

inline void create_edges(IGraph *graph) {
  std::mt19937 Random(clock());
  std::size_t size = graph->VerticesCount();
  for (std::size_t i = 0; i < size; ++i)
    for (std::size_t j = 0; j < size; ++j)
      if (Random() % 4 == 0)
        graph->AddEdge(i, j);
}

void cout_degree(const IGraph *graph) {
  std::size_t vertex_degree = 0;
  std::size_t max_degree = 0;
  std::size_t min_degree = graph->VerticesCount();
  std::size_t sum = 0;
  for (std::size_t i = 0; i < graph->VerticesCount(); ++i) {
    vertex_degree = graph->FindAllAdjacentIn(i).size() +
                    graph->FindAllAdjacentOut(i).size();
    max_degree = std::max(max_degree, vertex_degree);
    min_degree = std::min(min_degree, vertex_degree);
    sum += vertex_degree;
  }
  std::cout << min_degree << ' ' << sum / 1000. << ' ' << max_degree << '\n';
}

int main() {
  ListGraph LG(1000);
  MatrixGraph MG(1000);
  SetGraph SG(1000);
  ArcGraph AG(1000);

  create_edges(&LG);
  create_edges(&MG);
  create_edges(&SG);
  create_edges(&AG);

  ListGraph LG_from_MG(&MG);
  ListGraph LG_from_SG(&SG);
  ListGraph LG_from_AG(&AG);
  MatrixGraph MG_from_LG(&LG);
  MatrixGraph MG_from_SG(&SG);
  MatrixGraph MG_from_AG(&AG);
  SetGraph SG_from_LG(&LG);
  SetGraph SG_from_MG(&MG);
  SetGraph SG_from_AG(&AG);
  ArcGraph AG_from_LG(&LG);
  ArcGraph AG_from_MG(&MG);
  ArcGraph AG_from_SG(&SG);

  cout_degree(&LG);
  cout_degree(&MG_from_LG);
  cout_degree(&SG_from_LG);
  cout_degree(&AG_from_LG);
  std::cout << std::endl;
  cout_degree(&MG);
  cout_degree(&LG_from_MG);
  cout_degree(&SG_from_MG);
  cout_degree(&AG_from_MG);
  std::cout << std::endl;
  cout_degree(&SG);
  cout_degree(&LG_from_SG);
  cout_degree(&MG_from_SG);
  cout_degree(&AG_from_SG);
  std::cout << std::endl;
  cout_degree(&AG);
  cout_degree(&LG_from_AG);
  cout_degree(&MG_from_AG);
  cout_degree(&SG_from_AG);

  return 0;
}
