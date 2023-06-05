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

    /**
     * @brief Recursive call of the tspBruteforce function
     * @details Time Complexity: O(|V|!)
     * 
     * @param current The current vertex being visited
     * @param current_cost The current cost of the path
     * @param num_visited The number of vertexes visited
     * @param min_cost The minimum cost found so far
     * @param tsp_path The vector to store the TSP path of the minimum cost (output parameter)
     */
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

    /**
     * @brief Bruteforce algorithm to calculate the TSP path using backtracking
     * @details Time Complexity: O(|V|+|V|!)
     * 
     * @param tsp_path The vector to store the TSP path (output parameter)
     * @return double The cost of the TSP path
     */
    double tspBruteforce(std::vector<Vertex *> &tsp_path);

    /**
     * @brief Minimum Spanning Tree (MST) using Prim's algorithm
     * @details Time Complexity: O(|V|+|E|log(|V|))
     * 
     * @param source Beginning vertex of the MST
     * @param result Vector to store the MST vertexes in the preorder (output parameter)
     * @param cost Cost of the MST (output parameter)
     */
    void prim(Vertex *source, std::vector<Vertex *> &result, double &cost);

    /**
     * @brief Runs a DFS to get the preorder of an MST graph
     * @details Time Complexity: O(|V|+|E|)
     * 
     * @param current Current vertex being visited
     * @param result Vector to store the MST vertexes in the preorder (output parameter)
     * @param cost Cost of the MST (output parameter)
     * @param prev Previous vertex
     */
    void preorderMST(Vertex *current, std::vector<Vertex *> &result, double &cost, Vertex* &prev);

    /**
     * @brief Find the weight of an edge
     * 
     * @param source Source vertex
     * @param dest Destination vertex
     * @return double Weight of the edge
     */
    double findWeightEdge(int source, int dest);

    /**
     * @brief Calculate the TSP path using the Triangular Approximation Heuristic
     * @details Time Complexity:  O((|V| + |E|)log(|V|) + |V|)
     * 
     * @param tsp_path The vector to store the TSP path (output parameter)
     * @return double The cost of the TSP path
     */
    double triangularApproximation(std::vector<Vertex *> &tsp_path);

    /**
    * @brief Calculate the TSP path using the Nearest Neighbor algorithm (with an optional use of 2-opt algorithm)
    * @details Time Complexity: O(|V|^2) if two_opt_iterations = 0, O(|V|^2 * K) where K is the number of iterations of the 2-opt algorithm
    * 
    * @param tsp_path The vector to store the TSP path (output parameter)
    * @param two_opt_iterations Number of iterations of the 2-opt algorithm
    * @return double The cost of the TSP path
    */
    double tspNearestNeighbor(std::vector<Vertex*>& tsp_path, unsigned int two_opt_iterations);

    /**
     * @brief Calculate the TSP path using the 2-opt heuristic
     * @details Time Complexity: O(|V|^2 * K) where K is the number of iterations
     * 
     * @param tsp_path The vector to store the TSP path (output parameter)
     * @param two_opt_iterations Number of iterations of the 2-opt algorithm
     */
    void twoOptAlgorithm(std::vector<Vertex *> &tsp_path, unsigned int two_opt_iterations);

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
};

#endif // FEUP_DA2_GRAPH_H
