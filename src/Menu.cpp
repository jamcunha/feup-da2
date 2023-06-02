#include "Menu.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// To work with `Real-World-Graphs` import '../data/Real-World-Graphs/graph{x}/edges.csv'
// To work with `Toy-Graphs` import '../data/Toy-Graphs/{file}.csv'
const std::string Menu::INPUT_FILE = "../data/Real-World-Graphs/graph2/edges.csv";

void Menu::readData() {
    std::ifstream input(INPUT_FILE);

    std::string line;

    //discard first line
    getline(input, line);

    while (getline(input, line)) {
        std::stringstream ss(line);
        std::string origin_str, dest_str, distance;

        getline(ss, origin_str, ',');
        getline(ss, dest_str, ',');
        getline(ss, distance);

        if (line.back() == '\r' || line.back() == '\n') {
            line.pop_back(); // remove '\n' or '\r'
        }

        int origin = std::stoi(origin_str);
        int dest = std::stoi(dest_str);

        // if they already exist it just exits
        _graph.addVertex(origin);
        _graph.addVertex(dest);

        _graph.addBidirectionalEdge(origin, dest, std::stod(distance));
    }
}

Menu::Menu(): _graph(Graph()) {
    readData();
}

void Menu::init() {
    std::vector<Vertex *> tsp_path;
    double cost = 0;

    auto start = std::chrono::high_resolution_clock::now();

    Graph mst = Graph();
    Vertex* source = _graph.findVertex(0);
    _graph.prim(source,tsp_path, mst, _graph, cost);
    cost+=_graph.findWeightEdge((*(tsp_path.rbegin()))->getId(), source->getId());
    tsp_path.push_back(source);
    /*for (std::vector<Vertex *>::iterator it = tsp_path.begin(); it != tsp_path.end()-1; it++){
        std::vector<Vertex *>::iterator it2 = next(it, 1);
        for(auto e : (*it)->getAdj()){
            if (e->getDest()->getId() == (*it2)->getId()){
                cost += e->getWeight();
            }
        }
    }*/

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Path: ";
    for (int i = 0; i < tsp_path.size(); i++) {
        std::cout << tsp_path[i]->getId() << (i == tsp_path.size() - 1 ? "\n" : " -> ");
    }
    std::cout << "Cost: " << cost << "\n";
    std::cout << "Elapsed time: " << duration.count() << " ms\n";
}
