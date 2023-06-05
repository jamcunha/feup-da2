#ifndef FEUP_DA2_MENU_H
#define FEUP_DA2_MENU_H

#include "Graph.h"

#include <string>

/**
 * @brief User-friendly Menu
 */
class Menu {
private:
    Graph _graph;

    bool _graph_selected;

    bool _algorithm_selected;

    /**
     * @brief Path to input file (if Real World Graph the edge.csv)
     */
    std::string INPUT_FILE;
    
    /**
     * @brief Path to the node file with longitude and latitude info
     */
    std::string NODE_FILE;

    /**
     * @brief Reads data in input file and stores it in a graph
     *
     * TODO: change doc later
     */
    void readData(bool coordinateMode);

    /**
     * @brief Calculate the Traveling Salesman Problem (TSP) using the brute force algorithm.
     */
    void calculateBruteforceTSP();

    /**
     * @brief Calculate the Euclidean Traveling Salesman Problem (TSP) using the Triangular Approximation algorithm.
     */
    void calculateTriangularApproximation();

    /**
     * @brief Calculate the Euclidean Traveling Salesman Problem (TSP) using the Nearest Neighbor algorithm.
     */
    void calculateNearestNeighborTSP();

    /**
     * @brief Display the graph selection menu.
     */
    void graphSelectionMenu();

    /**
     * @brief Display the algorithm selection menu.
     */
    void algorithmSelectionMenu();

public:
    /**
     * @brief Constructs a new Menu object
     */
    Menu();

    /**
     * @brief Initialize the menu.
     */
    void init();
};

#endif // FEUP_DA2_MENU_H
