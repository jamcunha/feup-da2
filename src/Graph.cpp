#include "Graph.h"

#include <algorithm>
#include <limits>
#include <queue>

Vertex* Graph::findVertex(int id) const {
    for (auto v: vertexSet) {
        if (v->getId() == id) {
            return v;
        }
    }

    return nullptr;
}

bool Graph::addVertex(int id) {
    if (findVertex(id) != nullptr) {
        return false;
    }

    vertexSet.push_back(new Vertex(id));
    return true;
}

bool Graph::removeVertex(int id) {
    Vertex* v = findVertex(id);
    if (v == nullptr) {
        return false;
    }
    
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        w->removeEdge(v->getId());
        v->removeEdge(w->getId());
    }
    
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getId() == id){
            vertexSet.erase(it);
            break;
        }
    }

    delete v;
    return true;
}

bool Graph::addEdge(int source, int dest, double weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, weight);
    return true;
}

bool Graph::addBidirectionalEdge(int source, int dest, double weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    auto e1 = v1->addEdge(v2, weight);
    auto e2 = v2->addEdge(v1, weight);

    e1->setReverse(e2);
    e2->setReverse(e1);

    return true;
}

void Graph::dijkstra(Vertex* source) {
    auto cmp = [](Vertex* a, Vertex* b) {
        return a->getDistance() < b->getDistance();
    };
    std::priority_queue<Vertex *, std::vector<Vertex *>, decltype(cmp)> pq(cmp);

    for (Vertex* v: vertexSet) {
        v->setVisited(false);
        v->setDistance(std::numeric_limits<double>::max());
    }

    source->setDistance(0);
    pq.push(source);
    while (!pq.empty()) {
        Vertex* u = pq.top(); pq.pop();
        u->setVisited(true);

        for (Edge* e: u->getAdj()) {
            Vertex* v = e->getDest();
            double w = e->getWeight();
            if (!v->isVisited() && u->getDistance() != std::numeric_limits<double>::max() && u->getDistance() + w < v->getDistance()) {
                v->setDistance(u->getDistance() + w);
                pq.push(v);
            }
        }
    }
}

//! recursive function for tsp bruteforce (refactor later)
void Graph::tspBacktrackBruteforce(Vertex* current, double current_cost, int num_visited, double& min_cost, std::vector<Vertex *> &tsp_path) {
    if (num_visited == getNumVertex()) {
        double cost = current_cost;
        bool hasEdge = false;
        for (Edge* e: current->getAdj()) {
            if (e->getDest()->getId() == 0) {
                hasEdge = true;
                cost += e->getWeight();
                break;
            }
        }

        if (!hasEdge) {
            dijkstra(current);
            cost += findVertex(0)->getDistance(); // use dijkstra to get the distance between current and 0
            // for real world graph use latitude and longitude (maybe haversine algorithm)
        }

        if (cost < min_cost) {
            min_cost = cost;

            Vertex* init = findVertex(0);

            tsp_path.clear();
            tsp_path.push_back(init); tsp_path.push_back(current);
            //? id may not be needed
            for (Edge* e = current->getPath(); e->getOrigin()->getId() != findVertex(0)->getId(); e = e->getOrigin()->getPath()) {
                tsp_path.push_back(e->getOrigin());
            }
            tsp_path.push_back(init);

            std::reverse(tsp_path.begin(), tsp_path.end());
        }
        return;
    }

    for (Edge* e: current->getAdj()) { // may need refactor
        Vertex* w = e->getDest();
        if (!w->isVisited()) {
            w->setVisited(true);
            w->setPath(e);
            tspBacktrackBruteforce(w, current_cost + e->getWeight(), num_visited + 1, min_cost, tsp_path);
            w->setVisited(false);
            w->setPath(nullptr);
        }
    }
}

double Graph::tspBruteforce(std::vector<Vertex *> &tsp_path) {
    for (auto& v: vertexSet) {
        v->setVisited(false);
        v->setPath(nullptr);
    }

    double min_cost = std::numeric_limits<double>::max();

    auto init = findVertex(0);
    init->setVisited(true);
    tspBacktrackBruteforce(init, 0, 1, min_cost, tsp_path);

    return min_cost;
}

int Graph::getNumVertex() const {
    return this->vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}
