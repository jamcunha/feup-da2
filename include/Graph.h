#ifndef FEUP_DA2_GRAPH_H
#define FEUP_DA2_GRAPH_H

#include "VertexEdge.h"

#include <string>
#include <vector>
#include <limits>


const double INF = std::numeric_limits<double>::infinity();

/**
 * @brief Graph to structure the data
 */
class Graph {
private:
    /**
     * @brief Vector of graph vertexes
     */
    std::vector<Vertex *> vertexSet;

    void tspBacktrackBruteforce(Vertex* current, double current_cost, int num_visited, double& min_cost, std::vector<Vertex *> &tsp_path);

    /**
     * @brief 
     * 
     * @details 
     * 
     * @param int 
     * @return 
     */
    Edge* getNearestVertex(Vertex* v);

    double distance;

    std::string order;

public:
    /**
     * @brief Find a vertex in the graph with the given id, if it does not exists return nullptr
     * 
     * @details Time Complexity: O(|V|)
     * 
     * @param int Vertex id
     * @return Vertex* vertex
     */
    Vertex* findVertex(int id) const;

    /**
     * @brief Add a vertex to the graph
     * 
     * @param int Vertex id
     * @return true Vertex was added
     * @return false Vertex with that id already exists
     */
    bool addVertex(int id);

    /**
     * @brief Remove a vertex from the graph
     * 
     * @param int Id of the vertex to remove
     * @return true Vertex was removed
     * @return false Vertex was not found
     */
    bool removeVertex(int id);

    /**
     * @brief Add a edge to a vertex of the graph
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @return true Edge was added
     * @return false Source or destination vertex does not exist
     */
    bool addEdge(int source, int dest, double weight);

    /**
     * @brief Add a edge from source to destination vertex and another edge the other way
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @return true Edge was added
     * @return false Source or destination vertex does not exist
     */
    bool addBidirectionalEdge(int source, int dest, double weight);

    /**
     * @brief Find the minimum cost path from source to all other vertexes using Dijkstra algorithm.
     * @details Time Complexity: O(|V|+|E|log(|V|))
     * 
     * @param source Source vertex
     */
    void dijkstra(Vertex* source);

    double tspBruteforce(std::vector<Vertex *> &tsp_path);

    /**
     * @brief Get graph's number of vertexes
     * 
     * @return int Number of vertexes
     */
    int getNumVertex() const;

    /**
     * @brief Get graph's vertexes
     * 
     * @return std::vector<Vertex *> vertexSet
     */
    std::vector<Vertex *> getVertexSet() const;

    /**
     * @brief Mark all vertices as unvisited
     * 
     */
    void markAllUnvisited();

    /**
     * @brief Calculate the tour distance
     * 
     * @param start 
     * @return double 
     */
    double calculateTourDistance(Vertex* start) const;

    /**
     * @brief Get the Nearest Neighbor object
     * 
     * @param idx 
     * @return bool 
     */
    double calculateTour(std::vector<Vertex*>& tsp_path) const;

    /**
     * @brief Clears the graph by removing all vertices and edges.
     */
    void clearGraph();

    void tspNearestNeighbor(std::vector<Vertex*>& tsp_path);


};

#endif // FEUP_DA2_GRAPH_H
