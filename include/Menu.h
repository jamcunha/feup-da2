#ifndef FEUP_DA2_MENU_H
#define FEUP_DA2_MENU_H

#include "Graph.h"
#include "Utils.h"
#include "VertexEdge.h"

#include <string>

/**
 * @brief User-friendly Menu
 */
class Menu {
private:
    Graph _graph;

    bool graphSelected;

    bool algorithmSelected;


    /**
     * @brief Read graph data from a file.
     *
     * @param INPUT_FILE The input file path.
     */
    void readData(const std::string& INPUT_FILE);

    /**
     * @brief Calculate the Traveling Salesman Problem (TSP) using the brute force algorithm.
     */
    void calculateBruteforceTSP();

    /**
     * @brief Calculate the Euclidean Traveling Salesman Problem (TSP) using the brute force algorithm.
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

/**
 * @brief Clear the terminal screen.
 */
void clearTerminal();

#endif // FEUP_DA2_MENU_H
