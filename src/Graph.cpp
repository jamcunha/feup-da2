#include "Graph.h"

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

bool Graph::addEdge(int source, int dest, int weight) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    v1->addEdge(v2, weight);
    return true;
}

bool Graph::addBidirectionalEdge(int source, int dest, int weight) {
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

int Graph::edmondsKarp(int source, int dest) const {
    auto s = findVertex(source);
    auto t = findVertex(dest);

    // Check if source and destination are valid
    if (s == nullptr || t == nullptr || s == t) {
        return -1;
    }

    // Reset the flow in the edges
    for (auto v: vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    int max_flow = 0;

    while (findAugmentingPath(s, t)) {
        int pathFlow = std::numeric_limits<int>::max();

        // Find the minimum flow in the path
        for (auto v = t; v != s;) {
            auto e = v->getPath();
            if (e->getDest() == v) {
                pathFlow = std::min(pathFlow, e->getWeight() - e->getFlow());
                v = e->getOrigin();
            } else {
                pathFlow = std::min(pathFlow, e->getFlow());
                v = e->getDest();
            }
        }

        // Update the flow in the path
        for (auto v = t; v != s;) {
            auto e = v->getPath();
            if (e->getDest() == v) {
                e->setFlow(e->getFlow() + pathFlow);
                v = e->getOrigin();
            } else {
                e->setFlow(e->getFlow() - pathFlow);
                v = e->getDest();
            }
        }

        max_flow += pathFlow;
    }

    return (max_flow ? max_flow : -1);
}

//! not sure if this is correct (changed from first project to avoid compilation errors)
void Graph::dijkstra (Vertex *source) {
    auto cmp = [](Vertex *a, Vertex *b) {
        return a->getDistance() > b->getDistance();
    };
    std::priority_queue<Vertex *, std::vector<Vertex *>, decltype(cmp)> pq(cmp);

    for (auto v : vertexSet) {
        v->setVisited(false);
        v->setDistance(std::numeric_limits<int>::max());
    }

    source->setDistance(0);
    pq.push(source);
    while (!pq.empty()) {
        Vertex * u = pq.top(); pq.pop();
        u->setVisited(true);

        for (auto e : u->getAdj()) {
            Vertex* v = e->getDest();
            int w = e->getWeight();
            if (!v->isVisited() && u->getDistance() != std::numeric_limits<int>::max() && (u->getDistance() + w < v->getDistance())) {
                v->setDistance(u->getDistance() + w);
                v->setPath(e);
                pq.push(v);
            }
        }
    }
}

int Graph::getNumVertex() const {
    return this->vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}

/* Utils */

bool Graph::findAugmentingPath(Vertex *source, Vertex *dest) const {
    for (auto v: vertexSet) {
        v->setVisited(false);
    }
    source->setVisited(true);
    std::queue<Vertex *> q;
    q.push(source);

    while (!q.empty() && !dest->isVisited()) {
        auto v = q.front(); q.pop();

        for (auto e: v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited() && e->getWeight() - e->getFlow() > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }

        for (auto e: v->getIncomming()) {
            auto w = e->getOrigin();
            if (!w->isVisited() && e->getFlow() > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }

    return dest->isVisited();
}
