//
// Created by avira on 04/08/2020.
//

#include "Calc.h"

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
            break;
    }

}
