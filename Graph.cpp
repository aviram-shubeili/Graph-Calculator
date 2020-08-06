//
// Created by avira on 03/08/2020.
//

#include "Graph.h"
using std::string;


Graph::Graph(const std::string &data) {

    // data is not at the format of { ..  .. }
    if(not (startsWith(data, "{") and endsWith(data, "}")) ) {
        throw InvalidGraphData();
    }
    size_t end_of_vertices = data.find('|');
    string s_vertices;
    string s_edges;
    s_vertices = data.substr(1,end_of_vertices - 1);
    if( end_of_vertices != string::npos) {
        // s_edges may contain another '|'
        s_edges = data.substr(end_of_vertices + 1);
    // remove the '}' char.

    s_edges.pop_back();
    }
    else {
        // remove the '}' char.
    s_vertices.pop_back();
    }




    addAllVertices(trim(s_vertices), vertices);
    if(not s_edges.empty()){
    addAllEdges(trim(s_edges), edges);
    }
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
    Graph result = *this;
    result.vertices.insert(g2.vertices.begin(),g2.vertices.end());
    result.edges.insert(g2.edges.begin(), g2.edges.end());
    return result;
}



Graph Graph::operator^(const Graph &g2) const {
    Graph result("{ | }");

    std::set_intersection(vertices.begin(),vertices.end(),
                          g2.vertices.begin(), g2.vertices.end(),
                          std::inserter(result.vertices,result.vertices.begin()));

    std::set_intersection(edges.begin(),edges.end(),
                          g2.edges.begin(), g2.edges.end(),
                          std::inserter(result.edges,result.edges.begin()));

    return result;
}

Graph Graph::operator-(const Graph &g2) const {
    Graph result("{ | }");
    std::set_difference(vertices.begin(),vertices.end(),
                        g2.vertices.begin(),g2.vertices.end(),
                        std::inserter(result.vertices,result.vertices.begin()));

    for(pairs edge : edges) {
        try {
            result.addEdge(edge.first,edge.second);
        }
        catch (VertexNotExist& e) {
            continue;
        }
        catch(Exceptions& e) {
            // Should never Happen!
            assert(false);
        }
    }
    return result;
}

Graph Graph::operator*(const Graph &g2) const {
    Graph result("{ | }");

    // Adding the product Vertices
    for(const string& vertex_1 : vertices) {
        for(const string& vertex_2 : g2.vertices) {
            string prod_vertex = buildProductVertex(vertex_1,vertex_2);
            result.addVertex(prod_vertex);
        }
    }
    // Adding the product Edges
    for(const pairs& edge_1 : edges) {
        for(const pairs& edge_2 : g2.edges) {
            string src_1 = edge_1.first;
            string src_2 = edge_2.first;
            string dst_1 = edge_1.second;
            string dst_2 = edge_2.second;
            string prod_src = buildProductVertex(src_1,src_2);
            string prod_dst = buildProductVertex(dst_1,dst_2);
            try {
                result.addEdge(prod_src, prod_dst);
            }
            catch (GraphExceptions& e) {
                // Should never Get Here!
                assert(false);
            }
        }
    }

    return result;
}

Graph Graph::operator!() const {
    // Creating the Full simple Graph.
    Graph full_simple_graph("{ | }");
    // Vertices
    full_simple_graph.vertices = vertices;

    std::set<string>::const_iterator src_it = vertices.begin();
    std::set<string>::const_iterator dst_it = vertices.begin();
    std::set<string>::const_iterator end_it = vertices.end();
    // Edges
    for( ; src_it != end_it ; src_it++) {
        for( dst_it = vertices.begin() ; dst_it != end_it ; dst_it++) {
            if(*src_it != *dst_it) {
                string tmp_src = *src_it;
                string tmp_dst = *dst_it;
                full_simple_graph.addEdge(tmp_src, tmp_dst);
            }
        }
    }

    // Creating the Complement Graph.
    Graph result("{ | }");
    result.vertices = vertices;
    std::set_difference(full_simple_graph.edges.begin(),full_simple_graph.edges.end(),
                        edges.begin(),edges.end(),
                        std::inserter(result.edges,result.edges.begin()));

    return result;
}

string Graph::getString() const {
    string result;
    for(const string& vertex : vertices) {
        (result += vertex) += "\n";
    }
    result += "&\n";
    for(const pairs& edge : edges) {
        (((result +=edge.first) +=" ") += edge.second) += "\n";
    }
    return result;
}

void Graph::addVertex(std::string &vertex) {
    if(vertex.empty()) {
        IllegalVertexName();
    }
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
    if(s_vertices.empty()) {
        return;
    }
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
                done_with_src = false;
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
    if(inside) {
        throw InvalidGraphData();
    }
}

std::set<std::string> Graph::getVertices() {
    return vertices;
}

std::set<pairs> Graph::getEdges() {
    return edges;
}

bool isValidVertexName(const string &name) {
    if(name.empty()) {
        return false;
    }
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

string buildProductVertex(string vertex_1,string vertex_2) {
    string prod_vertex = "[";
    (prod_vertex += vertex_1 += ";") += vertex_2 += "]";

    return prod_vertex;
}