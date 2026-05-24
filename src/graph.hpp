#pragma once
#include <vector>

void addEdge(int node_1, int node_2, std::vector<std::vector<int>>& graph);
void removeEdge(int a, int b, std::vector<std::vector<int>>& graph);
bool edgeExists(int node_1, int node_2, const std::vector<std::vector<int>>& graph);
void generateGraph(int nodes, int saturation, std::vector<std::vector<int>>& graph);
void exportToTikZ(int nodes, const std::vector<std::vector<int>>& graph);
void print(int nodes, std::vector<std::vector<int>>& graph);
