//
// Created by avira on 05/08/2020.
//

#ifndef MTM_FINALPROJECT_PYINTERFACE_H
#define MTM_FINALPROJECT_PYINTERFACE_H
#include "Auxiliaries.h"
#include "Graph.h"

typedef Graph* graph_ptr;

graph_ptr create();

void destroy(graph_ptr g);

graph_ptr addVertex(graph_ptr g, std::string v);

graph_ptr addEdge(graph_ptr g, std::string src, std::string dst);

void disp(graph_ptr g);

graph_ptr graphUnion(graph_ptr graph_in1, graph_ptr graph_in2, graph_ptr graph_out);

graph_ptr graphIntersection(graph_ptr graph_in1, graph_ptr graph_in2, graph_ptr graph_out);

graph_ptr graphDifference(graph_ptr graph_in1, graph_ptr graph_in2, graph_ptr graph_out);

graph_ptr graphProduct(graph_ptr graph_in1, graph_ptr graph_in2, graph_ptr graph_out);

graph_ptr graphComplement(graph_ptr graph_in, graph_ptr graph_out);

#endif //MTM_FINALPROJECT_PYINTERFACE_H
