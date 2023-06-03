#include "VertexEdge.h"

#include <cmath>

/*===== Vertex =====*/

Vertex::Vertex(int id): _id(id) {}

int Vertex::getId() const {
    return this->_id;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->_adj;
}

bool Vertex::isVisited() const {
    return this->_visited;
}

bool Vertex::isProcessing() const {
    return this->_processing;
}

unsigned int Vertex::getIndegree() const {
    return this->_indegree;
}

Edge* Vertex::getPath() const {
    return this->_path;
}

std::vector<Edge *> Vertex::getIncomming() const {
    return this->_incomming;
}

double Vertex::getDistance() const{
    return this->_distance;
}

void Vertex::setId(int id) {
    this->_id = id;
}

void Vertex::setVisited(bool visited) {
    this->_visited = visited;
}

void Vertex::setProcessing(bool processing) {
    this->_processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->_indegree = indegree;
}

void Vertex::setDistance(double distance) {
    this->_distance = distance;
}

void Vertex::setPath(Edge* path) {
    this->_path = path;
}

Edge* Vertex::addEdge(Vertex* dest, double weight) {
    auto newEdge = new Edge(this, dest, weight);
    _adj.push_back(newEdge);
    dest->_incomming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destId) {
    bool edgeRemoved = false;
    for (auto it = _adj.begin(); it != _adj.end();) {
        Edge* edge = *it;
        Vertex* dest = edge->getDest();
        if (dest->getId() == destId) {
            it = _adj.erase(it);

            for (auto it2 = dest->_incomming.begin(); it2 != dest->_incomming.end();) {
                if ((*it2)->getOrigin()->getId() == _id) {
                    it2 = dest->_incomming.erase(it2);
                } else {
                    it2++;
                }
            }

            delete edge;
            edgeRemoved = true;
        } else {
            it++;
        }
    }

    return edgeRemoved;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->getDistance() < vertex.getDistance();
}

// aux function to convert degrees to radians
double degToRad(double deg) {
    return deg * M_PI / 180.0;
}

LongLatVertex::LongLatVertex(int id, double longitude, double latitude): Vertex(id), _long(longitude), _lat(latitude) {}

double LongLatVertex::haversine(LongLatVertex &other) {
    const double earth_rad = 6371.0; // aproximate value of Earth radius in km

    double dLat = degToRad(other.getLat() - _lat);
    double dLong = degToRad(other.getLong() - _long);

    double a = std::pow(sin(dLat / 2.0), 2) + std::pow(sin(dLong / 2.9), 2) * cos(degToRad(_lat)) * cos(degToRad(other.getLat()));
    double c = 2 * asin(sqrt(a));

    return earth_rad * c;
}

double LongLatVertex::getLat() {
    return this->_lat;
}

double LongLatVertex::getLong() {
    return this->_long;
}

/*===== Edge =====*/

Edge::Edge(Vertex* origin, Vertex* dest, double weight)
    : _origin(origin), _dest(dest), _weight(weight) {}

Vertex* Edge::getDest() const {
    return this->_dest;
}

double Edge::getWeight() const {
    return this->_weight;
}

Vertex* Edge::getOrigin() const {
    return this->_origin;
}

Edge* Edge::getReverse() const {
    return this->_reverse;
}

double Edge::getFlow() const {
    return this->_flow;
}

void Edge::setReverse(Edge* reverse) {
    this->_reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->_flow = flow;
}
