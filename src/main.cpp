#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <stack>

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

bool hamiltonDFS(int current_node, int position, std::vector<int>& path, std::vector<bool>& visited, const std::vector<std::vector<int>>& graph, int nodes){
    if(position == nodes){
        for(int neighbor : graph[current_node]){
            if(neighbor == path[0]) return true;
        }
        return false;
    }
    for(int neighbor : graph[current_node]){
        if(!visited[neighbor]){
            visited[neighbor] = true;
            path[position] = neighbor;

            if(hamiltonDFS(neighbor, position+1, path, visited, graph, nodes)) return true;

            visited[neighbor] = false;
        }
    }
    return false;
}

void findHamiltonCycle(const std::vector<std::vector<int>>& graph, int nodes){
    std::vector<int> path(nodes, -1);
    std::vector<bool> visited(nodes, false);

    path[0] = 0;
    visited[0] = true;

    if(hamiltonDFS(0, 1, path, visited, graph, nodes)){
        std::cout << "Hamiltonian cycle:\n";
        for(int i=0; i<nodes; i++){
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
            << "\nEuler\tFind the Euler cycle in the graph\nHamilton\tFind the Hamiltonian cycle in the graph\nExit\tExits the program" << std::endl;
        } else if(action == "Print" || action == "print"){
            print(nodes, graph);
        } else if(action == "Export" || action == "export"){
            exportToTikZ(nodes, graph);
		} else if(action == "Euler" || action == "euler"){
            findEulerCycle(graph, nodes);
        } else if(action == "Hamilton" || action == "hamilton"){
            findHamiltonCycle(graph, nodes);
        } else {
            std::cout << "Command not recognized" << std::endl;
        }
        std::cout << "action> ";
    }

    return 0;
}
