#include "Menu.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// To work with `Real-World-Graphs` import '../data/Real-World-Graphs/graph{x}/edges.csv'
// To work with `Toy-Graphs` import '../data/Toy-Graphs/{file}.csv'
const std::string Menu::INPUT_FILE = "../data/Toy-Graphs/shipping.csv";

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
    // TODO: change later
    for (Vertex* v: _graph.getVertexSet()) {
        std::cout << "\nVertex: " << v->getId() << "\n\n";
        for (Edge* e: v->getAdj()) {
            std::cout << "------------ Edge: " << e->getDest()->getId() << " -------------\n";
        }
    }
}
