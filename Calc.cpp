//
// Created by avira on 04/08/2020.
//

#include "Calc.h"



void Calc::addGraph(std::string &g_name, Graph g) {
    g_name = trim(g_name);
    if(not isValidGraphName(g_name)) {
        throw InvalidGraphName();
    }
    saved_graphs.insert({g_name, g});
}

Graph Calc::getGraph(std::string g_name) const {
    return saved_graphs.at(trim(g_name));
}

void Calc::reset() {
    saved_graphs.clear();
}

Graph Calc::applyOper(const std::string &g1_name, const char oper, const std::string &g2_name) const {
    // Exceptions may be thrown here
    Graph g1 = getGraph(g1_name);
    Graph g2 = getGraph(g2_name);

    switch (oper) {
        case '+':
            return g1 + g2;
        case '^':
            return g1 ^ g2;
        case '-':
            return g1 - g2;
        case '*':
            return g1 * g2;

        default:
            // Should never get here.
            assert(false);
            return Graph("");
    }

}

std::ostream &operator<<(std::ostream &os, const Calc &to_print) {
    for(const std::pair<std::string, class Graph> element : to_print.saved_graphs) {
        os << element.first << std::endl;
    }
    return os;
}
bool Calc::isValidGraphName(const std::string &g_name) {
    if(not isalpha(g_name[0])) {
        return false;
    }
    for(char c : g_name) {
        if(not isalnum(c)) {
            return false;
        }
    }
    if(SAVED_WORDS.find(g_name) != SAVED_WORDS.end()) {
        return false;
    }
    return true;

}

void Calc::erase(std::string to_delete) {
    if(saved_graphs.erase(to_delete) == 0) {
        throw GraphNotFound();
    }
}

void Calc::save(std::string g_name, std::string file_name) {
    if(not isValidGraphName(g_name)) {
        throw InvalidGraphName();
    }
    if(not isValidFileName(file_name)) {
        throw InvalidFileName();
    }
    Graph g = saved_graphs.at(g_name);
    std::set<std::string> vertices = g.getVertices();
    std::set<pairs> edges = g.getEdges();
    unsigned int num_vertices = vertices.size();
    unsigned int num_edges = edges.size();
    std::ofstream outfile(file_name, std::ios_base::binary);
    if(!outfile) {
        throw OpenFileError();
    }
    outfile.write((const char*)&num_vertices, sizeof(unsigned int));
    outfile.write((const char*)&num_edges, sizeof(unsigned int));
    for(const std::string& vertex : vertices) {
        unsigned int v_name_len = vertex.length()-1;
        outfile.write((const char*)&v_name_len, sizeof(unsigned int));
        outfile.write((const char*)&vertex, v_name_len);
    }
    for(const pairs& edge : edges) {
        std::string v1 = edge.first;
        std::string v2 = edge.second;
        unsigned int v1_name_len = v1.length()-1;
        unsigned int v2_name_len = v2.length()-1;
        // saving src vertex
        outfile.write((const char*)&v1_name_len, sizeof(unsigned int));
        outfile.write((const char*)&v1, v1_name_len);
        // saving dst vertex
        outfile.write((const char*)&v2_name_len, sizeof(unsigned int));
        outfile.write((const char*)&v2, v2_name_len);
    }



}

bool Calc::isValidFileName(const std::string &file_name) {
    return true;
}
