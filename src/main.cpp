#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void addEdge(int node_1, int node_2, std::vector<std::vector<int>>& graph)
{
    graph[node_1].push_back(node_2);
    graph[node_2].push_back(node_1);
}
void removeEdge(int a, int b, std::vector<std::vector<int>>& graph)
{
    graph[a].erase(
        std::remove(graph[a].begin(), graph[a].end(), b),
        graph[a].end());

    graph[b].erase(
        std::remove(graph[b].begin(), graph[b].end(), a),
        graph[b].end());
}

bool edgeExists(int node_1, int node_2, const std::vector<std::vector<int>>& graph)
{
    for (int v : graph[node_1])
    {
        if (v == node_2)
            return true;
    }
    return false;
}

void generateGraph(int nodes, int saturation, std::vector<std::vector<int>>& graph)
{
    int currentEdges = 0, targetEdges = (nodes * (nodes - 1) / 2 * saturation) / 100;

    std::vector<int> nodes_visited(nodes, 0);

    // Create Hamiltonian cycle
    int lastVisited, firstVisited = std::rand() % nodes;
    nodes_visited[firstVisited] = 1;
    lastVisited = firstVisited;

    for (int i = 1; i < nodes; ++i)
    {
        int visiting = std::rand() % nodes;
        while (nodes_visited[visiting])
        {
            visiting = std::rand() % nodes;
        }
        
        addEdge(lastVisited, visiting, graph);
        nodes_visited[visiting] = 1;
        lastVisited = visiting;
        currentEdges++;
    }

    addEdge(lastVisited, firstVisited, graph);
    currentEdges++;

    // Add random edges until saturation is reached
    while (currentEdges < targetEdges)
    {

        int a = std::rand() % nodes;
        int b = std::rand() % nodes;
        int c = std::rand() % nodes;

        if (a == b || b == c || a == c)
            continue;
        if (edgeExists(a, b, graph) || edgeExists(b, c, graph) || edgeExists(c, a, graph))
            continue;

        addEdge(a, b, graph);
        addEdge(b, c, graph);
        addEdge(c, a, graph);
        currentEdges += 3;
    }
}

void print(int nodes, std::vector<std::vector<int>>& graph)
{
    for (int i = 0; i < nodes; i++)
    {
        std::cout << i + 1 << ": ";
        for (int neighbor : graph[i])
        {
            std::cout << neighbor + 1 << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) 
    {
        std::cout << "1 Argument expected. Possible arguments: \n --hamilton \n --non-hamilton\n";
        return 1;
    }
	if (std::string(argv[1]) != "--hamilton" && std::string(argv[1]) != "--non-hamilton")
	{
		std::cout << "Incorrect argument. Possible arguments: \n --hamilton \n --non-hamilton\n";
		return 1;
	}

    int nodes;
    std::cout << "nodes> ";
    std::cin >> nodes;

    std::vector<std::vector<int>> graph;
    graph.resize(nodes);

    std::srand(std::time(0));
    int saturation;

    if (std::string(argv[1]) == "--hamilton")
    {
        std::cout << "saturation> ";
        std::cin >> saturation;
    }
    else
    {
        saturation = 50;
    }

    generateGraph(nodes, saturation, graph);
    
    if (std::string(argv[1]) == "--non-hamilton")
    {
        int isolated = std::rand() % nodes;   
        std::vector<int> neighbors = graph[isolated];

        for (int i : neighbors)
        {
            removeEdge(isolated, i, graph);
        }
    }
     
    print(nodes, graph);
    return 0;
}
