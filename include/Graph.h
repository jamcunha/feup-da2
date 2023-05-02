#ifndef FEUP_DA1_GRAPH_H
#define FEUP_DA1_GRAPH_H

#include "VertexEdge.h"

#include <vector>

// TODO: change documentation

/**
 * @brief Railway network
 */
class Graph {
private:
    /**
     * @brief Vector of graph vertexes
     */
    std::vector<Vertex *> vertexSet;

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
    bool addEdge(int source, int dest, int weight);

    /**
     * @brief Add a edge from source to destination vertex and another edge the other way
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @param weight Edge weight
     * @return true Edge was added
     * @return false Source or destination vertex does not exist
     */
    bool addBidirectionalEdge(int source, int dest, int weight);

    /**
     * @brief Find an augmenting path in the graph using BFS
     * 
     * @details Time Complexity: O(|V|+|E|)
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @return true Found augmenting path
     * @return false No augmenting path
     */
    bool findAugmentingPath(Vertex *source, Vertex *dest) const;

    /**
     * @brief Find the maximum flow between source and destination vertex using Edmonds-Karp algorithm
     * Used to calculate the maximum number of trains that can simultaneously travel between two stations
     * 
     * @details Time Complexity: O(|V||E|²)
     * 
     * @param source Source vertex
     * @param dest Destination Vertex
     * @return int max_flow or -1 if error (input or flow network is not valid)
     */
    int edmondsKarp(int source, const int dest) const;

    /**
     * @brief Find the minimum cost path from source to all other vertexes using Dijkstra algorithm.
     * 
     * @details Time Complexity: O(|V|+|E|log(|V|))
     * 
     * @param source Source vertex
     */
    void dijkstra(Vertex *source);

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
};

#endif // FEUP_DA1_GRAPH_H
