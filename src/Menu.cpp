#include "Menu.h"

#include <fstream>
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

        // TODO: origin and dest is int and distance double
        std::string origin, dest, distance;

        getline(ss, origin, ',');
        getline(ss, dest, ',');
        getline(ss, distance);

        if (line.back() == '\r' || line.back() == '\n') {
            line.pop_back(); // remove '\n' or '\r'
        }
    }
}

Menu::Menu(): _graph(Graph()) {
    readData();
}
