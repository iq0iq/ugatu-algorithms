#include "ArcGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include <iostream>
#include <random>

inline void create_edges(IGraph *graph) {
  std::mt19937 Random(clock());
  size_t Size = graph->VerticesCount();
  for (size_t i = 0; i < Size; ++i)
    for (size_t j = 0; j < Size; ++j)
      if (Random() % 4 == 0)
        graph->AddEdge(i, j);
}

void cout_degree(const IGraph *graph) {
  int vertex_degree = 0;
  int Max = 0;
  int Min = graph->VerticesCount();
  int Sum = 0;
  for (unsigned int i = 0; i < graph->VerticesCount(); ++i) {
    vertex_degree = graph->FindAllAdjacentIn(i).size() +
                    graph->FindAllAdjacentOut(i).size();
    Max = std::max(Max, vertex_degree);
    Min = std::min(Min, vertex_degree);
    Sum += vertex_degree;
  }
  std::cout << Min << ' ' << Sum / 1000. << ' ' << Max << '\n';
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
