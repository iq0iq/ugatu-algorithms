#include <climits>
#include <iostream>
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
      edges_; // first value in the pair is the index of the vertex, second is
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
  std::size_t Pop();
  void DecreaseKey(std::size_t distance, std::size_t old_distance,
                   std::size_t vertex);
  bool Empty();

private:
  std::set<std::pair<std::size_t, std::size_t>> set_;
};

void priority_queue::Push(std::size_t distance, std::size_t vertex) {
  set_.emplace(distance, vertex);
}

std::size_t priority_queue::Pop() {
  std::size_t vertex = set_.begin()->second;
  set_.erase(set_.begin());
  return vertex;
}

void priority_queue::DecreaseKey(std::size_t distance, std::size_t old_distance,
                                 std::size_t vertex) {
  set_.erase(set_.find({old_distance, vertex}));
  set_.emplace(distance, vertex);
}

bool priority_queue::Empty() { return set_.empty(); }

std::size_t Dijkstra(Graph &graph, std::size_t from, std::size_t to) {
  std::vector<std::size_t> distance(graph.VerticesCount(), ULLONG_MAX);
  distance[from] = 0;
  priority_queue queue;
  queue.Push(0, from);
  while (!queue.Empty()) {
    std::size_t current = queue.Pop();
    for (std::pair<std::size_t, std::size_t> i :
         graph.FindAllAdjacent(current)) {
      std::size_t index = i.first;
      std::size_t weight = i.second;
      if (distance[index] > distance[current] + weight) {
        if (distance[index] == ULLONG_MAX) {
          queue.Push(distance[current] + weight, index);
        } else {
          queue.DecreaseKey(distance[current] + weight, distance[index], index);
        }
        distance[index] = distance[current] + weight;
      }
    }
  }
  return distance[to];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n);
  std::size_t from = 0;
  std::size_t to = 0;
  std::size_t weight = 0;
  for (std::size_t i = 0; i < m; ++i) {
    std::cin >> from >> to >> weight;
    graph.AddEdge(from, to, weight);
  }
  std::cin >> from >> to;
  std::cout << Dijkstra(graph, from, to) << std::endl;
  return 0;
}
