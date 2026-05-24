#pragma once
#include <vector>

bool hamiltonDFS(int current_node, int position, std::vector<int>& path, std::vector<bool>& visited, const std::vector<std::vector<int>>& graph, int nodes);
void findHamiltonCycle(const std::vector<std::vector<int>>& graph, int nodes);
void findEulerCycle(const std::vector<std::vector<int>>& original_graph, int nodes);
