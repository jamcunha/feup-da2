#ifndef FEUP_DA2_GRAPH_H
#define FEUP_DA2_GRAPH_H

#include "VertexEdge.h"

#include <vector>

/**
 * @brief Graph to structure the data
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

    void prim(Vertex *source, std::vector<Vertex *> &result, Graph &mst, Graph &original);

    void preorderMST(Vertex *current, std::vector<Vertex *> &result, Graph &original);
};

#endif // FEUP_DA2_GRAPH_H
