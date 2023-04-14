#include <iostream>
#include <limits>
#include <set>
#include <vector>

class Graph {
public:
  explicit Graph(std::size_t vertices_count);
  void AddEdge(std::size_t from, std::size_t to, std::size_t weight);
  std::size_t VerticesCount() const;
  std::vector<std::pair<std::size_t, std::size_t>>
  FindAllAdjacent(std::size_t vertex) const;

private:
  std::vector<std::vector<std::pair<std::size_t, std::size_t>>>
      edges_;  // first value in the pair is the index of the vertex, second is
               // the weight
};

Graph::Graph(std::size_t vertices_count) : edges_(vertices_count) {}

void Graph::AddEdge(std::size_t from, std::size_t to, std::size_t weight) {
  edges_[from].emplace_back(to, weight);
  edges_[to].emplace_back(from, weight);
}

std::size_t Graph::VerticesCount() const { return edges_.size(); }

std::vector<std::pair<std::size_t, std::size_t>>
Graph::FindAllAdjacent(std::size_t vertex) const {
  return edges_[vertex];
}

struct priority_queue {
public:
  void Push(std::size_t distance, std::size_t vertex);
  std::pair<std::size_t, std::size_t> Pop();
  void DecreaseKey(std::size_t distance, std::size_t old_distance,
                   std::size_t vertex);
  bool Empty();

private:
  std::set<std::pair<std::size_t, std::size_t>> set_;
};

void priority_queue::Push(std::size_t distance, std::size_t vertex) {
  set_.emplace(distance, vertex);
}

std::pair<std::size_t, std::size_t> priority_queue::Pop() {
  auto vertex = *set_.begin();
  set_.erase(set_.begin());
  return vertex;
}

void priority_queue::DecreaseKey(std::size_t distance, std::size_t old_distance,
                                 std::size_t vertex) {
  set_.erase(set_.find({old_distance, vertex}));
  set_.emplace(distance, vertex);
}

bool priority_queue::Empty() { return set_.empty(); }

std::size_t Prim(Graph &graph) {
  priority_queue queue;
  queue.Push(0, 0);
  std::vector<int64_t> distance_in_queue(graph.VerticesCount(), -1);
  distance_in_queue[0] = 0;
  std::vector<bool> is_in_tree(graph.VerticesCount());
  is_in_tree[0] = true;
  std::size_t weight = 0;
  while (!queue.Empty()) {
    auto current = queue.Pop();
    weight += current.first;
    is_in_tree[current.second] = true;
    distance_in_queue[current.second] = -1;
    for (auto i : graph.FindAllAdjacent(current.second)) {
      if (!is_in_tree[i.first]) {
        if (distance_in_queue[i.first] > static_cast<int64_t>(i.second)) {
          queue.DecreaseKey(i.second, distance_in_queue[i.first], i.first);
          distance_in_queue[i.first] = i.second;
        }
        if (distance_in_queue[i.first] == -1) {
          queue.Push(i.second, i.first);
          distance_in_queue[i.first] = i.second;
        }
      }
    }
  }
  return weight;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n);
  std::size_t from = 0;
  std::size_t to = 0;
  std::size_t weight = 0;
  for (std::size_t i = 0; i < m; ++i) {
    std::cin >> from >> to >> weight;
    graph.AddEdge(from - 1, to - 1, weight);
  }
  std::cout << Prim(graph) << std::endl;
  return 0;
}
