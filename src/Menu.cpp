#include "Menu.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// To work with `Real-World-Graphs` import '../data/Real-World-Graphs/graph{x}/edges.csv'
// To work with `Real-World-Graphs` import '../data/Extra_Fully_Connected_Graphs/edges_{x}.csv'
// To work with `Toy-Graphs` import '../data/Toy-Graphs/{file}.csv'
const std::string Menu::INPUT_FILE = "../data/Real-World-Graphs/graph3/edges.csv";

// To work with `Real-World-Graphs` import '../data/Real-World-Graphs/graph{x}/nodes.csv'
const std::string Menu::NODE_FILE = "../data/Real-World-Graphs/graph3/nodes.csv";

void Menu::readData(bool coordinateMode) {
    if (!coordinateMode) {
        std::ifstream input(INPUT_FILE);

        if (!input.is_open()) {
            std::cout << "Error opening the file\n";
            exit(1);
        }

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

        input.close();
    } else { // TODO: to be tested
        std::ifstream node(NODE_FILE);
        std::ifstream edge(INPUT_FILE);

        if (!node.is_open() || !edge.is_open()) {
            std::cout << "Error opening a file\n";
            exit(1);
        }

        std::string line;

        // discard first line
        getline(node, line);
        getline(edge, line);

        while (getline(node, line)) {
            std::stringstream ss(line);
            std::string id_str, long_str, lat_str;

            getline(ss, id_str, ',');
            getline(ss, long_str, ',');
            getline(ss, lat_str);

            if (line.back() == '\r' || line.back() == '\n') {
                line.pop_back(); // remove '\n' or '\r'
            }

            _graph.addVertex(std::stoi(id_str), std::stod(long_str), std::stod(lat_str));
        }

        while (getline(edge, line)) {
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

            _graph.addBidirectionalEdge(origin, dest, std::stod(distance));
        }

        node.close();
        edge.close();
    }
}

Menu::Menu() {
    //! refactor later (when implementing the menu)
    bool coordinateMode = true;

    this->_graph = new Graph(coordinateMode);
    readData(coordinateMode);
}

void Menu::init() {
    std::vector<Vertex *> tsp_path;

    auto start = std::chrono::high_resolution_clock::now();

    double cost = _graph.triangularApproximation(tsp_path);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Path: ";
    for (int i = 0; i < tsp_path.size(); i++) {
        std::cout << tsp_path[i]->getId() << (i == tsp_path.size() - 1 ? "\n" : " -> ");
    }
    std::cout << "Cost: " << cost << "\n";
    std::cout << "Elapsed time: " << duration.count() << " s\n";
}
