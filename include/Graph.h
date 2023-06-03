#ifndef FEUP_DA2_GRAPH_H
#define FEUP_DA2_GRAPH_H

#include "VertexEdge.h"

#include <vector>
#include <unordered_map>

/**
 * @brief Graph to structure the data
 */
class Graph {
private:
    /**
     * @brief Unordered map of graph vertexes
     */
    std::unordered_map<int, Vertex *> vertexSet;

    void tspBacktrackBruteforce(Vertex* current, double current_cost, int num_visited, double& min_cost, std::vector<Vertex *> &tsp_path);

    /**
     * @brief Check if the vertexes have coordinates or not
     * (Used for Real World Graphs)
     */
    bool _coordinate_mode;

public:

    Graph() = default;
    Graph(bool coordinateMode);

    /**
     * @brief Find a vertex in the graph with the given id, if it does not exists return nullptr
     * 
     * @details Time Complexity: O(1)
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
     * @brief Add a vertex to the graph, with latitude and longitude if _coordinate_mode is true
     * 
     * @param int Vertex id
     * @param double Vertex longitude
     * @param double Vertex latitude
     * @return true Vertex was added
     * @return false Vertex with that id already exists
     */
    bool addVertex(int id, double longitude, double latitude);

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
     * @return std::unordered_map<int, Vertex *> vertexSet
     */
    std::unordered_map<int, Vertex *> getVertexSet() const;

    void prim(Vertex *source, std::vector<Vertex *> &result, Graph &mst, Graph &original, double &cost);

    void preorderMST(Vertex *current, std::vector<Vertex *> &result, Graph &original, double &cost, Vertex* &prev);

    double findWeightEdge(int source, int dest);
};

#endif // FEUP_DA2_GRAPH_H
