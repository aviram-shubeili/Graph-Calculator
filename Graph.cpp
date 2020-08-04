//
// Created by avira on 03/08/2020.
//

#include "Graph.h"
using std::string;


Graph::Graph(const std::string &data) {

    // TODO fix so | is optional in a graph with no edges

    // data is not at the format of { .. | .. }
    if(not (startsWith(data, "{") and (data.find('|') != string::npos) and endsWith(data, "}")) ) {
        throw InvalidGraphData();
    }
    string s_vertices = data.substr(1,data.find('|') - 1);

    // s_edges may contain another '|'
    string s_edges = data.substr(data.find('|') + 1);

    // remove the '}' char.
    s_edges.pop_back();

    addAllVertices(trim(s_vertices), vertices);
    addAllEdges(trim(s_edges), edges);
}

Graph::Graph(const Graph &other) : vertices(other.vertices), edges(other.edges) {}

Graph& Graph::operator=(const Graph &other) {
    if(this == &other) {
        return *this;
    }
    vertices = other.vertices;
    edges = other.edges;
    return *this;

}


Graph Graph::operator+(const Graph &g2) const {
    return Graph("");
}



Graph Graph::operator^(const Graph &g2) const {
    return Graph("");
}

Graph Graph::operator-(const Graph &g2) const {
    return Graph("");
}

Graph Graph::operator*(const Graph &g2) const {
    return Graph("");
}

Graph Graph::operator!() const {
    return Graph("");
}

void Graph::print(std::ostream &output) const {
    for(const string& vertex : vertices) {
        output << vertex << std::endl;
    }
    output << "&" << std::endl;
    for(const pairs& edge : edges) {
        output << edge.first << " " << edge.second << std::endl;
    }
}

void Graph::addVertex(std::string &vertex) {
    vertex = trim(vertex);
    if(!isValidVertexName(vertex)) {
        throw IllegalVertexName();
    }
    // vertex already exists
    if(vertices.find(vertex) != vertices.end()) {
        throw VertexAlreadyExists();
    }
    vertices.insert(vertex);
}

void Graph::addEdge(std::string &src, std::string &dest) {
    src = trim(src);
    dest = trim(dest);
    // one of the vertex's doesnt exist.
    if(vertices.find(src) == vertices.end() or vertices.find(dest) == vertices.end()) {
        throw VertexNotExist();
    }
    if(src == dest) {
        throw SelfLoop();
    }
    pairs edge = make_pair(src,dest);
    // edge already exist
    if(edges.find(edge) != edges.end()) {
        throw EdgeAlreadyExists();
    }
    edges.insert(edge);
}

void Graph::addAllVertices(const string &s_vertices, std::set<std::string> &dst_set) {
    string cur_vertex;
    bool ended_prop = true;
    for(char c : s_vertices) {
        if(c == ',') {
            cur_vertex = trim(cur_vertex);
            addVertex(cur_vertex);
            cur_vertex = "";
            ended_prop = false;
        }
        else {
            cur_vertex += c;
            ended_prop = true;
        }
    }
    // add the last vertex.
    if(not ended_prop) {
        throw InvalidGraphData();
    }
    cur_vertex = trim(cur_vertex);
    addVertex(cur_vertex);


}

void Graph::addAllEdges(const string &s_edges, std::set<pairs> &dst_set) {

    bool inside = false;
    bool sep_ok = true;
    bool done_with_src = false;
    string src, dst;
    for(char c : s_edges) {

        // we are outside of an Edge data (<v1,v2>)
        if(!inside) {
            if(c == '<' and sep_ok) {
                inside = true;
            }
            else if(c == ',') {
                // <edge> , , <edge>
                if(sep_ok) {
                    throw InvalidGraphData();
                }
                else {
                    sep_ok = true;
                }
            }
                // some character outside of < > or < without , to seperate
            else if(c != ' ') {
                throw InvalidGraphData();
            }
        }

        else {  // inside = true
            if(c == '>') {
                inside = false;
                addEdge(src,dst);
                src = "";
                dst = "";
                sep_ok = false;
            }
            else if(c == ',' ) {
                done_with_src = true;
            }
            else if(!done_with_src) {
                src += c;
            }
            else {
                dst += c;
            }
        }
    }
}

// TODO
bool isValidVertexName(const string &name) {
    int num_open = 0;
    for(char c : name) {
        if(c == '[') {
            num_open++;
        }
        else if(c== ']'){
            if(--num_open < 0) {
                return false;
            }
        }
        else if(c == ';') {
            if(num_open == 0) {
                return false;
            }
        }
        else if(not isalnum(c)){
            return false;
        }
    }
    return num_open == 0;
}
