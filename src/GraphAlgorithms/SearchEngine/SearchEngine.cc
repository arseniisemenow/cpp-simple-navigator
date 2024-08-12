#include "SearchEngine.h"

#include <unordered_set>

#include "containers/adaptors/Stack/Stack.h"
#include "containers/adaptors/Queue/Queue.h"

namespace s21 {

std::vector<int> SearchEngine::DepthFirstSearch(const Graph &graph,
                                                const int start_index) {
  if (graph.IsEmpty()) {
    return {};
  }
  if (start_index >= graph.GetGraph().size()) {
    return {};
  }

  std::vector<int> result;
  std::unordered_set<int> visited;
  Stack<int> stack;
  stack.push(start_index - 1);

  while (!stack.empty()) {
    int vertex = stack.top();
    stack.pop();

    if (visited.find(vertex) == visited.end()) {
      visited.insert(vertex);
      result.push_back(vertex + 1);

      for (int i = graph.GetGraph().size() - 1; i >= 0; --i) {
        if (graph.GetGraph()[vertex][i] != 0 &&
            visited.find(i) == visited.end()) {
          stack.push(i);
        }
      }
    }
  }

  return result;
}

std::vector<int> SearchEngine::BreadthFirstSearch(const Graph &graph,
                                                  const int start_index) {
  if (graph.IsEmpty()) {
    return {};
  }
  if (start_index >= graph.GetGraph().size()) {
    return {};
  }
  std::vector<int> result;
  std::unordered_set<int> visited;
  Queue<int> queue;
  queue.push(start_index - 1);
  visited.insert(start_index - 1);

  while (!queue.empty()) {
    const int current = queue.front();
    queue.pop();
    result.push_back(current + 1);

    for (size_t i = 0; i < graph.GetGraph().size(); ++i) {
      if (graph.GetGraph()[current][i] != 0 &&
          visited.find(i) == visited.end()) {
        queue.push(i);
        visited.insert(i);
      }
    }
  }

  return result;
}

}  // namespace s21
