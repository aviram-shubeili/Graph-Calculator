//
// Created by avira on 04/08/2020.
//

#include "Calc.h"



void Calc::addGraph(std::string &g_name, Graph g) {
    g_name = trim(g_name);
    if(!isValidGraphName(g_name)) {
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
