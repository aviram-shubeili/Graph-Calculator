//
// Created by avira on 03/08/2020.
//

#include "Graph.h"
using std::string;

bool isValidName(const std::string name);
/*
 *      *  Exceptions:
     *      InvalidGraphData() - if data is not at the format.
     *      IllegalEdgeData() - if one of the edges data is invalid - uses a vertex that doesnt exists / illegal name.
     *      IllegalVertexName() - if one of the vertices`s name is invalid.
     *      std::bad_alloc() - if allocation problem
 */
Graph::Graph(const std::string &data) {
    // data is not at the format of { .. | .. }
    if(not (startsWith(data, "{") and (data.find('|') == string::npos) and endsWith(data, "}")) ) {
        throw InvalidGraphData();
    }



}

Graph::Graph(const Graph &other) {

}

Graph &Graph::operator=(const Graph &other) {
    // if this = other
}

Graph Graph::operator+(const Graph &g2) const {
    return Graph(__cxx11::basic_string());
}

Graph Graph::operator^(const Graph &g2) const {
    return Graph(__cxx11::basic_string());
}

Graph Graph::operator-(const Graph &g2) const {
    return Graph(__cxx11::basic_string());
}

Graph Graph::operator*(const Graph &g2) const {
    return Graph(__cxx11::basic_string());
}

Graph Graph::operator!() const {
    return Graph(__cxx11::basic_string());
}

void Graph::print() const {

}

void Graph::addVertex(std::string &vertex) {

}

void Graph::addEdge(std::string &src, std::string &dest) {

}
