//
// Created by avira on 04/08/2020.
//

#include "GraphExceptions.h"

const char *GraphExceptions::what() const noexcept {
    return "Unknown Graph Error. \n";
}

const char *InvalidGraphData::what() const noexcept {
    return "Error: Invalid graph data. \n" ;
}

const char *IllegalEdgeData::what() const noexcept {
    return "Error: Illegal edge data. \n";
}

const char *IllegalVertexName::what() const noexcept {
    return "Error: Illegal vertex name. \n";
}

const char *VertexNotExist::what() const noexcept {
    return "Error: Vertex doesnt exist in graph. \n";
}

const char *EdgeAlreadyExists::what() const noexcept {
    return "Error: Edge already exists in graph. \n";
}

const char *VertexAlreadyExists::what() const noexcept {
    return "Error: Vertex already exists in graph. \n";
}

const char *SelfLoop::what() const noexcept {
    return "Error: Self loop edge. \n";
}

