#include "Menu.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// To work with `Real-World-Graphs` import '../data/Real-World-Graphs/graph{x}/edges.csv'
// To work with `Toy-Graphs` import '../data/Toy-Graphs/{file}.csv'
const std::string Menu::INPUT_FILE = "../data/Toy-Graphs/stadiums.csv";

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

    auto start = std::chrono::high_resolution_clock::now();
    double cost = _graph.tspBruteforce(tsp_path);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Path: ";
    for (int i = 0; i < tsp_path.size(); i++) {
        std::cout << tsp_path[i]->getId() << (i == tsp_path.size() - 1 ? "\n" : " -> ");
    }

    std::cout << "Cost: " << cost << '\n';
    std::cout << "Elapsed Time: " << duration.count() << " s\n";
}
