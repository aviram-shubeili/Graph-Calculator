//
// Created by avira on 05/08/2020.
//

#include "PyInterface.h"

graph_ptr create() {
    graph_ptr g;
    try {
         g = new Graph() ;
    }
    catch (std::bad_alloc& e) {

        std::cout << "Error: FATAL - allocation failed."<< std::endl;
        return nullptr;
    }
    return g;
}

void destroy(graph_ptr g) {
    if(g == nullptr) {
        std::cout << "Error: I dont know what you sent me, but its not a Graph."<< std::endl;
        return;
    }
    delete g;
}

graph_ptr addVertex(graph_ptr g, std::string v) {
    if(g == nullptr) {
        std::cout << "Error: I dont know what you sent me, but its not a Graph."<< std::endl;
        return nullptr;
    }
    try {
        g->addVertex(v);
    }
        // IllegalVertexName or VertexAlreadyExists
    catch (GraphExceptions& e) {
        std::cout << e.what();
        return nullptr;
    }
    catch (std::bad_alloc& e) {
        std::cout << "Error: FATAL - allocation failed."<< std::endl;
        return nullptr;
    }
    return g;
}


graph_ptr addEdge(graph_ptr g, std::string src, std::string dst) {
    if(g == nullptr) {
        std::cout << "Error: I dont know what you sent me, but its not a Graph." << std::endl;
        return nullptr;
    }
    try {
        g->addEdge(src,dst);
    }
        // VertexNotExist / SelfLoop / EdgeAlreadyExists
    catch (GraphExceptions& e) {
        std::cout << e.what();
        return nullptr;
    }
    catch (std::bad_alloc& e) {
        std::cout << "Error: FATAL - allocation failed." << std::endl;
        return nullptr;
    }
    return g;
}


void disp(graph_ptr g) {
    if(g == nullptr) {
        std::cout << "Error: I dont know what you sent me, but its not a Graph." << std::endl;
        return;
    }
    try {
        std::cout << g->getString();
    }
    catch (std::bad_alloc& e) {
        std::cout << "Error: FATAL - allocation failed." << std::endl;
    }
}

graph_ptr graphUnion(graph_ptr graph_in1, graph_ptr graph_in2, graph_ptr graph_out) {
    if(graph_in1 == nullptr or graph_in2 == nullptr or graph_out == nullptr) {
        std::cout << "Error: One of the parameters is not a Graph." << std::endl;
        return nullptr;
    }
    try {
        *graph_out = *graph_in1 + *graph_in2;
    }
    catch (std::bad_alloc& e) {
        std::cout << "Error: FATAL - allocation failed." << std::endl;
        return nullptr;
    }
    return graph_out;
}

graph_ptr graphIntersection(graph_ptr graph_in1, graph_ptr graph_in2, graph_ptr graph_out) {
    if(graph_in1 == nullptr or graph_in2 == nullptr or graph_out == nullptr) {
        std::cout << "Error: One of the parameters is not a Graph." << std::endl;
        return nullptr;
    }
    try {
        *graph_out = *graph_in1 ^ *graph_in2;
    }
    catch (std::bad_alloc& e) {
        std::cout << "Error: FATAL - allocation failed." << std::endl;
        return nullptr;
    }
    return graph_out;
}

graph_ptr graphDifference(graph_ptr graph_in1, graph_ptr graph_in2, graph_ptr graph_out) {
    if(graph_in1 == nullptr or graph_in2 == nullptr or graph_out == nullptr) {
        std::cout << "Error: One of the parameters is not a Graph." << std::endl;
        return nullptr;
    }
    try {
        *graph_out = *graph_in1 - *graph_in2;
    }
    catch (std::bad_alloc& e) {
        std::cout << "Error: FATAL - allocation failed." << std::endl;
        return nullptr;
    }
    return graph_out;
}

graph_ptr graphProduct(graph_ptr graph_in1, graph_ptr graph_in2, graph_ptr graph_out) {
    if(graph_in1 == nullptr or graph_in2 == nullptr or graph_out == nullptr) {
        std::cout << "Error: One of the parameters is not a Graph." << std::endl;
        return nullptr;
    }
    try {
        *graph_out = *graph_in1 * *graph_in2;
    }
    catch (std::bad_alloc& e) {
        std::cout << "Error: FATAL - allocation failed." << std::endl;
        return nullptr;
    }
    return graph_out;
}

graph_ptr graphComplement(graph_ptr graph_in, graph_ptr graph_out) {
    if(graph_in == nullptr or graph_out == nullptr) {
        std::cout << "Error: One of the parameters is not a Graph." << std::endl;
        return nullptr;
    }
    try {
        *graph_out = !(*graph_in);
    }
    catch (std::bad_alloc& e) {
        std::cout << "Error: FATAL - allocation failed." << std::endl;
        return nullptr;
    }
    return graph_out;
}
