#include "algorithms.hpp"
#include <iostream>
#include <stack>
#include <algorithm>

bool hamiltonDFS(int current_node, int position, std::vector<int>& path, std::vector<bool>& visited, const std::vector<std::vector<int>>& graph, int nodes) {
    if(position == nodes) {
        for(int neighbor : graph[current_node]) {
            if(neighbor == path[0]) return true;
        }
        return false;
    }
    for(int neighbor : graph[current_node]) {
        if(!visited[neighbor]) {
            visited[neighbor] = true;
            path[position] = neighbor;

            if(hamiltonDFS(neighbor, position+1, path, visited, graph, nodes)) return true;

            visited[neighbor] = false;
        }
    }
    return false;
}

void findHamiltonCycle(const std::vector<std::vector<int>>& graph, int nodes) {
    std::vector<int> path(nodes, -1);
    std::vector<bool> visited(nodes, false);

    path[0] = 0;
    visited[0] = true;

    if(hamiltonDFS(0, 1, path, visited, graph, nodes)) {
        std::cout << "Hamiltonian cycle:\n";
        for(int i=0; i<nodes; i++) {
            std::cout << path[i] + 1 << " --> ";
        }
        std::cout << path[0]+1 << std::endl;
    } else {
        std::cout << "Hamiltonian cycle not found." << std::endl;
    }
}

void findEulerCycle(const std::vector<std::vector<int>>& original_graph, int nodes) {
    for(int i = 0; i < nodes; i++) {
        if(original_graph[i].size() % 2 != 0) {
            std::cout << "Eulerian cycle not found (vertex " << i + 1 << " has an odd degree)." << std::endl;
            return;
        }
    }

    std::vector<std::vector<int>> graph = original_graph;
    std::stack<int> curr_path;
    std::vector<int> circuit;

    int curr_v = 0;
    curr_path.push(0);

    while (!curr_path.empty()) {
        if (!graph[curr_v].empty()) {
            curr_path.push(curr_v);
            int next_v = graph[curr_v].back();
            graph[curr_v].pop_back();

            auto it = std::find(graph[next_v].begin(), graph[next_v].end(), curr_v);
            if (it != graph[next_v].end()) {
                graph[next_v].erase(it);
            }

            curr_v = next_v;
        } else {
            circuit.push_back(curr_v);
            curr_v = curr_path.top();
            curr_path.pop();
        }
    }
    for (int i = 0; i < nodes; i++) {
        if (!graph[i].empty()) {
            std::cout << "Eulerian cycle not found (graph is disconnected)." << std::endl;
            return;
        }
    }
    std::cout << "Eulerian cycle:\n";
    for (int i = circuit.size() - 1; i >= 0; i--) {
        std::cout << circuit[i] + 1;
        if (i > 0) std::cout << " --> ";
    }
    std::cout << std::endl;
}
