#include "Menu.h"
#include "Utils.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// To work with `Real-World-Graphs` import '../data/Real-World-Graphs/graph{x}/edges.csv'
// To work with `Real-World-Graphs` import '../data/Extra_Fully_Connected_Graphs/edges_{x}.csv'
// To work with `Toy-Graphs` import '../data/Toy-Graphs/{file}.csv'
// std::string Menu::INPUT_FILE;

// To work with `Real-World-Graphs` import '../data/Real-World-Graphs/graph{x}/nodes.csv'
// std::string Menu::NODE_FILE;

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
    } else {
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

void Menu::calculateBruteforceTSP() {
    if (!_graph_selected) {
        std::cout << "No graph selected. Please select a graph first.\n\n";
        return;
    }

    std::vector<Vertex *> tsp_path;

    auto start = std::chrono::high_resolution_clock::now();
    double cost = _graph.tspBruteforce(tsp_path);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "TSP Path (Brute Force Algorithm):";
    for (int i = 0; i < tsp_path.size(); i++) {
        std::cout << tsp_path[i]->getId() << (i == tsp_path.size() - 1 ? "\n" : " -> ");
    }

    std::cout << "Cost: " << cost << '\n';
    std::cout << "Elapsed Time: " << duration.count() << " s\n\n";   
}

void Menu::calculateTriangularApproximation() {
    if (!_graph_selected) {
        std::cout << "No graph selected. Please select a graph first.\n\n";
        return;
    }

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
    std::cout << "Elapsed Time: " << duration.count() << " s\n\n";
}



void Menu::calculateNearestNeighborTSP() {
    if (!_graph_selected) {
        std::cout << "No graph selected. Please select a graph first.\n\n";
        return;
    }

    std::vector<Vertex*> tsp_path;

    auto start = std::chrono::high_resolution_clock::now();

    double cost = _graph.tspNearestNeighbor(tsp_path);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "TSP Path (Nearest Neighbor): ";
    for (int i = 0; i < tsp_path.size(); i++) {
        std::cout << tsp_path[i]->getId() << (i == tsp_path.size() - 1 ? "\n" : " -> ");
    }

    std::cout << "Cost: " << cost << '\n';
    std::cout << "Elapsed Time: " << duration.count() << " s\n\n";
}



void Menu::init() {
    while (true) {
        utils::clearScreen();
        std::cout << "Menu Options:\n";
        std::cout << "1. Select Graph\n";
        std::cout << "2. Run Algorithm\n";
        std::cout << "3. Exit\n\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                utils::clearScreen();
                graphSelectionMenu();
                break;
            case 2:
                utils::clearScreen();
                algorithmSelectionMenu();
                break;
            case 3:
                utils::clearScreen();
                return;
            default:
                utils::clearScreen();
                std::cout << "Invalid choice. Please try again.\n\n";
                break;
        }
    }
}

void Menu::graphSelectionMenu() {
    _graph_selected = false;

    while (!_graph_selected) {
        std::cout << "Graph Selection:\n";
        std::cout << "1. Real-World-Graphs\n";
        std::cout << "2. Toy-Graphs\n";
        std::cout << "3. Extra-Graphs\n";
        std::cout << "4. Back\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                utils::clearScreen();
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
                        utils::clearScreen();
                        std::cout << "Selected Real-World-Graph 1.\n\n";

                        _graph = Graph(true);

                        this->INPUT_FILE = "../data/Real-World-Graphs/graph1/edges.csv";
                        this->NODE_FILE = "../data/Real-World-Graphs/graph1/nodes.csv";
                        readData(true);
                        _graph_selected = true;
                        break;
                    case 2:
                        utils::clearScreen();
                        std::cout << "Selected Real-World-Graph 2.\n\n";

                        _graph = Graph(true);

                        this->INPUT_FILE = "../data/Real-World-Graphs/graph2/edges.csv";
                        this->NODE_FILE = "../data/Real-World-Graphs/graph2/nodes.csv";
                        readData(true);
                        _graph_selected = true;
                        break;
                    case 3:
                        utils::clearScreen();
                        std::cout << "Selected Real-World-Graph 3.\n\n";

                        _graph = Graph(true);

                        this->INPUT_FILE = "../data/Real-World-Graphs/graph3/edges.csv";
                        this->NODE_FILE = "../data/Real-World-Graphs/graph3/nodes.csv";
                        readData(true);
                        _graph_selected = true;
                        break;
                    case 4:
                        utils::clearScreen();
                        std::cout << "Going back to Graph Selection Menu.\n\n";
                        break;
                    default:
                        utils::clearScreen();
                        std::cout << "Invalid choice. Please try again.\n\n";
                        break;
                }
                break;
            case 2:
                utils::clearScreen();
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
                        utils::clearScreen();
                        std::cout << "Selected Toy-Graph Shipping.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Toy-Graphs/shipping.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 2:
                        utils::clearScreen();
                        std::cout << "Selected Toy-Graph Stadiums.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Toy-Graphs/stadiums.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 3:
                        utils::clearScreen();
                        std::cout << "Selected Toy-Graph Tourism.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Toy-Graphs/tourism.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 4:
                        utils::clearScreen();
                        std::cout << "Going back to Graph Selection Menu.\n\n";
                        break;
                    default:
                        utils::clearScreen();
                        std::cout << "Invalid choice. Please try again.\n\n";
                        break;
                }
                break;
            case 3:
            utils::clearScreen();
                std::cout << "Toy-Graphs Selection:\n";
                std::cout << "1. 25 Edges\n";
                std::cout << "2. 50 Edges\n";
                std::cout << "3. 75 Edges\n";
                std::cout << "4. 100 Edges\n";
                std::cout << "5. 200 Edges\n";
                std::cout << "6. 300 Edges\n";
                std::cout << "7. 400 Edges\n";
                std::cout << "8. 500 Edges\n";
                std::cout << "9. 600 Edges\n";
                std::cout << "10. 700 Edges\n";
                std::cout << "11. 800 Edges\n";
                std::cout << "12. 900 Edges\n";
                std::cout << "13. Back\n";
                std::cout << "Enter your choice: ";

                int egChoice;
                std::cin >> egChoice;

                switch (egChoice) {
                    case 1:
                        utils::clearScreen();
                        std::cout << "Selected 25 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_25.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 2:
                        utils::clearScreen();
                        std::cout << "Selected 50 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_50.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 3:
                        utils::clearScreen();
                        std::cout << "Selected 75 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_75.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 4:
                        utils::clearScreen();
                        std::cout << "Selected 100 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_100.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 5:
                        utils::clearScreen();
                        std::cout << "Selected 200 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_200.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 6:
                        utils::clearScreen();
                        std::cout << "Selected 300 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_300.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 7:
                        utils::clearScreen();
                        std::cout << "Selected 400 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_400.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 8:
                        utils::clearScreen();
                        std::cout << "Selected 500 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_500.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 9:
                        utils::clearScreen();
                        std::cout << "Selected 600 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_600.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 10:
                        utils::clearScreen();
                        std::cout << "Selected 700 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_700.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 11:
                        utils::clearScreen();
                        std::cout << "Selected 800 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_800.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 12:
                        utils::clearScreen();
                        std::cout << "Selected 900 Edges Extra Graph.\n\n";

                        _graph = Graph(false);

                        this->INPUT_FILE = "../data/Extra_Fully_Connected_Graphs/edges_900.csv";
                        readData(false);
                        _graph_selected = true;
                        break;
                    case 13:
                        utils::clearScreen();
                        std::cout << "Going back to Graph Selection Menu.\n\n";
                        break;
                    default:
                        utils::clearScreen();
                        std::cout << "Invalid choice. Please try again.\n\n";
                        break;
                }
                break;
            case 4:
                utils::clearScreen();
                return;
            default:
                utils::clearScreen();
                std::cout << "Invalid choice. Please try again.\n\n";
                break;
        }
    }
}

void Menu::algorithmSelectionMenu() {
    _algorithm_selected = false;

    while (!_algorithm_selected) {
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
                utils::clearScreen();
                std::cout << "Selected TSP (Brute Force) Algorithm.\n\n";
                calculateBruteforceTSP();
                _algorithm_selected = true;
                utils::waitEnter();
                break;
            case 2:
                utils::clearScreen();
                std::cout << "Selected TSP (Triangular Approximation Heuristic).\n\n";
                calculateTriangularApproximation();
                _algorithm_selected = true;
                utils::waitEnter();
                break;
            case 3:
                utils::clearScreen();
                std::cout << "Selected TSP (Nearest Neighbor) Algorithm.\n\n";
                calculateNearestNeighborTSP();
                _algorithm_selected = true;
                utils::waitEnter();
                break;
            case 4:
                return;
            default:
                utils::clearScreen();
                std::cout << "Invalid choice. Please try again.\n\n";
                break;
        }
    }
}

Menu::Menu() {
    _graph_selected = false;
    _algorithm_selected = false;
}
