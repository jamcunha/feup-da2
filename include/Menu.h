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

    /**
     * @brief Path to input file (if Real World Graph the edge.csv)
     */
    static const std::string INPUT_FILE;
    
    /**
     * @brief Path to the node file with longitude and latitude info
     */
    static const std::string NODE_FILE;

    /**
     * @brief Reads data in input file and stores it in a graph
     *
     * TODO: change doc later
     */
    void readData(bool coordinateMode);

public:
    /**
     * @brief Constructs a new Menu object
     */
    Menu();

    void init();
};

#endif // FEUP_DA2_MENU_H
