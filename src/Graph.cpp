#include "Graph.h"
#include "MutablePriorityQueue.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>

Graph::Graph(bool coordinateMode): _coordinate_mode(coordinateMode) {}

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

bool Graph::addVertex(int id, double longitude, double latitude) {
    if (!this->_coordinate_mode) {
        return false;
    }

    if (findVertex(id) != nullptr) {
        return false;
    }

    vertexSet.push_back(new LongLatVertex(id, longitude, latitude));
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

double Graph::findWeightEdge(int source, int dest){
    auto v1 = findVertex(source);
    if (v1 == nullptr) {
        return 0;
    }
    for (auto adj : v1->getAdj()){
        if (adj->getDest()->getId() == dest){
            return adj->getWeight();
        }
    }
    return 0;
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

int Graph::getNumVertex() const {
    return this->vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}

void Graph::prim(Vertex* source, std::vector<Vertex*> &result, Graph &mst, Graph &original, double &cost){
    /*auto cmp = [](Vertex* a, Vertex* b) {
        return a->getDistance() > b->getDistance();
    };*/
    //std::priority_queue<Vertex *, std::vector<Vertex *>, decltype(cmp)> pq(cmp);
    MutablePriorityQueue<Vertex> pq;
    for (Vertex* v: vertexSet) {
        mst.addVertex(v->getId());
        v->setVisited(false);
        v->setDistance(std::numeric_limits<double>::max());
        v->setPath(nullptr);
    }

    source->setDistance(0);
    pq.insert(source);
    while (!pq.empty()) {
        Vertex* u = pq.extractMin();
        if (u->isVisited())
            continue;
        u->setVisited(true);
        if (u->getId()!=source->getId())
            mst.addBidirectionalEdge(u->getPath()->getOrigin()->getId(), u->getId(), u->getPath()->getWeight());
        for (Edge* e: u->getAdj()) {
            Vertex* v = e->getDest();
            double w = e->getWeight();
            if (!v->isVisited() && w < v->getDistance()) {
                double previous = v->getDistance();
                v->setDistance(w);
                v->setPath(e);
                if (previous == std::numeric_limits<double>::max())
                    pq.insert(v);
                else
                    pq.decreaseKey(v);
            }
        }
    }
    for (Vertex* v: vertexSet) {
        v->setVisited(false);
    }
    Vertex* v = mst.findVertex(0);
    int prev;
    preorderMST(v, result, original, cost, prev);
}

void Graph::preorderMST(Vertex* current, std::vector<Vertex*> &result, Graph &original, double &cost, int &prev){
    Vertex* v = original.findVertex(current->getId());
    result.push_back(v);
    current->setVisited(true);
    bool flag = true;
    for (Edge* e: current->getAdj()) {
        if (flag && !e->getDest()->isVisited()){
            cost += e->getWeight();
            prev = e->getDest()->getId();

        }
        else if (!e->getDest()->isVisited()){
            cost += original.findWeightEdge(prev, e->getDest()->getId());
            prev = e->getDest()->getId();
        }
        flag = false;
        Vertex* w = e->getDest();
        if (!w->isVisited()) {
            preorderMST(w, result, original, cost, prev);
        }
    }
}

