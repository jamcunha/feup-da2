#include "../include/Menu.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void Menu::readData(const std::string& INPUT_FILE) {
    
    _graph.clearGraph();
    
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

void Menu::calculateBruteforceTSP() {
    if (!graphSelected) {
        std::cout << "No graph selected. Please select a graph first.\n\n";
        return;
    }

    std::vector<Vertex *> tsp_path;
 
    auto start = std::chrono::high_resolution_clock::now();
    double cost = _graph.tspBruteforce(tsp_path);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Path: ";
    for (int i = 0; i < tsp_path.size(); i++) {
        std::cout << tsp_path[i]->getId() << (i == tsp_path.size() - 1 ? "\n" : " -> ");
    }

    std::cout << "Cost: " << cost << "\n";
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed Time: " << duration.count() << " ms\n\n";
}



void Menu::calculateNearestNeighborTSP() {
    if (!graphSelected) {
        std::cout << "No graph selected. Please select a graph first.\n\n";
        return;
    }

    std::vector<Vertex*> tsp_path;
    double cost = 0.0;

    auto start = std::chrono::high_resolution_clock::now();

    _graph.tspNearestNeighbor(tsp_path);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "TSP Path (Nearest Neighbor): ";
    for (int i = 0; i < tsp_path.size(); i++) {
        std::cout << tsp_path[i]->getId() << (i == tsp_path.size() - 1 ? "\n" : " -> ");
    }

    for (int i = 0; i < tsp_path.size() - 1; i++) {
        Edge* edge = tsp_path[i]->getEdge(tsp_path[i + 1]);
        cost += edge->getWeight();
    }

    std::cout << "Cost: " << cost << '\n';
    std::cout << "Elapsed Time: " << duration.count() << " ms\n\n";
}



void Menu::init() {
    bool exit = false;

    while (!exit) {
        std::cout << "Menu Options:\n";
        std::cout << "1. Select Graph\n";
        std::cout << "2. Run Algorithm\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                clearTerminal();
                graphSelectionMenu();
                break;
            case 2:
                clearTerminal();
                algorithmSelectionMenu();
                break;
            case 3:
                clearTerminal();
                exit = true;
                break;
            default:
                clearTerminal();
                std::cout << "Invalid choice. Please try again.\n\n";
                break;
        }
    }
}

void Menu::graphSelectionMenu() {
    graphSelected = false;

    while (!graphSelected) {
        std::cout << "Graph Selection:\n";
        std::cout << "1. Real-World-Graphs\n";
        std::cout << "2. Toy-Graphs\n";
        std::cout << "3. Back\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                clearTerminal();
                std::cout << "Real-World-Graphs Selection:\n";
                std::cout << "1. Graph 1\n";
                std::cout << "2. Graph 2\n";
                std::cout << "3. Graph 3\n";
                std::cout << "4. Back\n";
                std::cout << "Enter your choice: ";

                int rwgChoice;
                std::cin >> rwgChoice;

                switch (rwgChoice) {
                    case 1:
                        clearTerminal();
                        std::cout << "Selected Real-World-Graph 1.\n\n";
                        readData("../data/Real-World-Graphs/graph1/edges.csv");
                        graphSelected = true;
                        break;
                    case 2:
                        clearTerminal();
                        std::cout << "Selected Real-World-Graph 2.\n\n";
                        readData("../data/Real-World-Graphs/graph2/edges.csv");
                        graphSelected = true;
                        break;
                    case 3:
                        clearTerminal();
                        std::cout << "Selected Real-World-Graph 3.\n\n";
                        readData("../data/Real-World-Graphs/graph3/edges.csv");
                        graphSelected = true;
                        break;
                    case 4:
                        clearTerminal();
                        std::cout << "Going back to Graph Selection Menu.\n\n";
                        break;
                    default:
                        clearTerminal();
                        std::cout << "Invalid choice. Please try again.\n\n";
                        break;
                }
                break;
            case 2:
                clearTerminal();
                std::cout << "Toy-Graphs Selection:\n";
                std::cout << "1. Shipping\n";
                std::cout << "2. Stadiums\n";
                std::cout << "3. Tourism\n";
                std::cout << "4. Back\n";
                std::cout << "Enter your choice: ";

                int tgChoice;
                std::cin >> tgChoice;

                switch (tgChoice) {
                    case 1:
                        clearTerminal();
                        std::cout << "Selected Toy-Graph Shipping.\n\n";
                        readData("../data/Toy-Graphs/shipping.csv");
                        graphSelected = true;
                        break;
                    case 2:
                        clearTerminal();
                        std::cout << "Selected Toy-Graph Stadiums.\n\n";
                        readData("../data/Toy-Graphs/stadiums.csv");
                        graphSelected = true;
                        break;
                    case 3:
                        clearTerminal();
                        std::cout << "Selected Toy-Graph Tourism.\n\n";
                        readData("../data/Extra/edges_300.csv");
                        graphSelected = true;
                        break;
                    case 4:
                        clearTerminal();
                        std::cout << "Going back to Graph Selection Menu.\n\n";
                        break;
                    default:
                        clearTerminal();
                        std::cout << "Invalid choice. Please try again.\n\n";
                        break;
                }
                break;
            case 3:
                clearTerminal();
                return;
            default:
                clearTerminal();
                std::cout << "Invalid choice. Please try again.\n\n";
                break;
        }
    }
}

void Menu::algorithmSelectionMenu() {
    algorithmSelected = false;

    while (!algorithmSelected) {
        std::cout << "Algorithm Selection:\n";
        std::cout << "1. Calculate TSP (Brute Force)\n";
        std::cout << "2. Calculate TSP (Triangular Approximation Heuristic) \n";
        std::cout << "3. Calculate TSP (Nearest Neighbor)\n";
        std::cout << "4. Back\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                clearTerminal();
                std::cout << "Selected TSP (Brute Force) Algorithm.\n\n";
                calculateBruteforceTSP();
                algorithmSelected = true;
                break;
            case 2:
                clearTerminal();
                std::cout << "Selected TSP (Triangular Approximation Heuristic).\n\n";
                calculateTriangularApproximation();
                algorithmSelected = true;
                break;
            case 3:
                clearTerminal();
                std::cout << "Selected TSP (Nearest Neighbor) Algorithm.\n\n";
                calculateNearestNeighborTSP();
                algorithmSelected = true;
                break;
            case 4:
                clearTerminal();
                return;
            default:
                clearTerminal();
                std::cout << "Invalid choice. Please try again.\n\n";
                break;
        }
    }
}

Menu::Menu() {
    graphSelected = false;
    algorithmSelected = false;
    
    std::cout << "Elapsed Time: " << duration.count() << " s\n";
}

