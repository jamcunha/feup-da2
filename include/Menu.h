
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
     * @brief Path to input file
     */
    static const std::string INPUT_FILE; //! check later if the other info is needed

    /**
     * @brief Reads data in input file and stores it in a graph
     */
    void readData();

public:
    /**
     * @brief Constructs a new Menu object
     */
    Menu();
};

#endif // FEUP_DA2_MENU_H
