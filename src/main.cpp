#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "graph.hpp"
#include "algorithms.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "1 Argument expected. Possible arguments: \n --hamilton \n --non-hamilton\n";
        return 1;
    }
    if (std::string(argv[1]) != "--hamilton" && std::string(argv[1]) != "--non-hamilton") {
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

    if (std::string(argv[1]) == "--hamilton") {
        std::cout << "saturation> ";
        std::cin >> saturation;
    } else {
        saturation = 50;
    }

    generateGraph(nodes, saturation, graph);
    
    if (std::string(argv[1]) == "--non-hamilton") {
        int isolated = std::rand() % nodes;   
        std::vector<int> neighbors = graph[isolated];

        for (int i : neighbors) {
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
