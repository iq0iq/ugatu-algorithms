#include <iostream>
#include <vector>

class ListGraph {
public:
  explicit ListGraph(int vertices_count);

  void AddEdge(int from, int to);
  std::size_t VerticesCount() const;
  std::vector<int> FindAllAdjacentIn(int vertex) const;
  std::vector<int> FindAllAdjacentOut(int vertex) const;

private:
  std::vector<std::vector<int>> in_edges_;
  std::vector<std::vector<int>> out_edges_;
};

ListGraph::ListGraph(int vertices_count)
    : in_edges_(vertices_count), out_edges_(vertices_count) {}

void ListGraph::AddEdge(int from, int to) {
  in_edges_[to].emplace_back(from);
  out_edges_[from].emplace_back(to);
}

std::size_t ListGraph::VerticesCount() const { return in_edges_.size(); }

std::vector<int> ListGraph::FindAllAdjacentIn(int vertex) const {
  return in_edges_[vertex];
}
std::vector<int> ListGraph::FindAllAdjacentOut(int vertex) const {
  return out_edges_[vertex];
}

void DFS_for_inverted(const ListGraph &graph, std::vector<int> &leave,
                      std::vector<bool> &used, int current, int &time) {
  used[current] = true;
  for (int i : graph.FindAllAdjacentIn(current)) {
    if (!used[i])
      DFS_for_inverted(graph, leave, used, i, time);
  }
  leave[current] = time++;
}

void DFS(const ListGraph &graph, std::vector<int> &components,
         std::vector<std::pair<bool, bool>> &in_out, int current,
         int current_component) {
  components[current] = current_component;
  for (int i : graph.FindAllAdjacentOut(current)) {
    if (components[i] == -1)
      DFS(graph, components, in_out, i, current_component);
    if (components[i] != current_component) {
      in_out[current_component].second = true;
      in_out[components[i]].first = true;
    }
  }
}

void Kosaraju(const ListGraph &graph,
              std::vector<std::pair<bool, bool>> &in_out) {
  std::vector<int> leave(graph.VerticesCount());
  std::vector<bool> used(graph.VerticesCount());
  int time = 0;
  for (int i = 0; i < graph.VerticesCount(); ++i) {
    if (!used[i])
      DFS_for_inverted(graph, leave, used, i, time);
  }
  std::vector<int> components(graph.VerticesCount(), -1);
  int components_number = 0;
  for (int i = leave.size() - 1; i >= 0; --i) {
    if (components[leave[i]] == -1) {
      in_out.emplace_back(false, false);
      DFS(graph, components, in_out, i, components_number++);
    }
  }
}

std::size_t number_of_edges_to_be_added(const ListGraph &graph) {
  std::vector<std::pair<bool, bool>>
      in_out;  // first - true if there are incoming edges in the component,
               // second - outcoming
  Kosaraju(graph, in_out);
  int incoming_sum = 0;
  int outcoming_sum = 0;
  int isolated_sum = 0;
  for (auto i : in_out) {
    if (i.first)
      ++incoming_sum;
    if (i.second)
      ++outcoming_sum;
    if (!i.first && !i.second)
      ++isolated_sum;
  }
  return (in_out.size() == 1
              ? 0
              : std::max(incoming_sum, outcoming_sum) + isolated_sum);
}

int main() {
  int v = 0;
  int e = 0;
  std::cin >> v >> e;
  int from = 0;
  int to = 0;
  ListGraph graph(v);
  for (int i = 0; i < e; ++i) {
    std::cin >> from >> to;
    graph.AddEdge(from - 1, to - 1);
  }
  std::cout << number_of_edges_to_be_added(graph) << std::endl;
  return 0;
}
