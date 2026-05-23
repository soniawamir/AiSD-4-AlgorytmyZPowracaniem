#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

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

void exportToTikZ(int nodes, const std::vector<std::vector<int>>& graph)
{
    const double PI = 3.1415;
    const double node_spacing = 1.5; 
    double radius = (nodes * node_spacing) / (2.0 * PI);
    
    if (radius < 2.0) {
        radius = 2.0; 
    }

    std::cout << "\\begin{tikzpicture}[scale=0.8, transform shape, every node/.style={circle, draw, minimum size=0.6cm, inner sep=1pt}]" << std::endl;
    
    for (int i = 0; i < nodes; i++)
    {
        double angle = i * (2.0 * PI / nodes);
        double x = radius * std::cos(angle);
        double y = radius * std::sin(angle);

        std::cout << "  \\node (n" << i + 1 << ") at (" << x << ", " << y << ") {" << i + 1 << "};" << std::endl;
    }

    for (int i = 0; i < nodes; i++)
    {
        for (int neighbor : graph[i])
        {
            if (neighbor > i)
            {
                std::cout << "  \\draw (n" << i + 1 << ") -- (n" << neighbor + 1 << ");" << std::endl;
            }
        }
    }

    std::cout << "\\end{tikzpicture}" << std::endl;
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

    std::string action;
    std::cout << "action> ";
    while(std::cin >> action){
        if(action == "exit" || action == "Exit"){
            break;
        } else if(action == "Help" || action == "help"){
            std::cout << "Help\tShow this message\nPrint\tPrint the graph as an adjacency list\nExport\tExport graph to tickzpicture"
            << "\nEuler\tFind the Euler cycle in the graph\nHamilton\tFind the Hamilton cycle in the graph\nExit\tExits the program" << std::endl;
        } else if(action == "Print" || action == "print"){
            print(nodes, graph);
        } else if(action == "Export" || action == "export"){
            exportToTikZ(nodes, graph);
        } else if(action == "Euler" || action == "euler"){

        } else if(action == "Hamilton" || action == "hamilton"){

        } else {
            std::cout << "Command not recognized" << std::endl;
        }
        std::cout << "action> ";
    }
    return 0;
}
