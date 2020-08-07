//
// Created by avira on 03/08/2020.
//

#ifndef SWIG
#ifndef MTM_FINALPROJECT_GRAPH_H
#define MTM_FINALPROJECT_GRAPH_H
#include <iostream>
#include <set>
#include <utility>
#include "Auxiliaries.h"

typedef  std::pair<std::string, std::string>  pairs;
class Graph {
private:
    std::set<std::string> vertices;
    std::set<pairs> edges;

public:
    /**
     * Default constructor to an Empty Graph (used by python)
     */
    Graph() = default;
    /**
     * Create a Graph from a string : { **Vertices** | **Edges** }
     * @param data
     *  Exceptions:
     *      InvalidGraphData() - if data is not at the format.
     *      IllegalEdgeData() - if one of the edges data is invalid - uses a vertex that doesnt exists / illegal name.
     *      IllegalVertexName() - if one of the vertices`s name is invalid.
     *      std::bad_alloc() - if allocation problem
     */
    Graph(const std::string& data);    //TODO :  should it be explicit?
    /**
     *
     * @param other
     */
    /**
     * copy other to current graph - current graph will be overridden
     * @param other
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph(const Graph& other);    //TODO :  should it be explicit?

    /**
     * Assignment operator - current graph will be overridden
     *
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph& operator=(const Graph& other);

    /**
     * Default D'or.
     */
    ~Graph() = default;

    /**
     *  union of 2 graphs
     * @param g2
     * @return the united graph
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph operator+(const Graph& g2) const;
    //TODO : bi-direction operator +

    /**
     * create an intersection of 2 graphs
     * @param g2
     * @return the intersected graph
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph operator^(const Graph& g2) const;
    // TODO : bi-direction operator ^

    /**
     * creates the difference of this graph and g2
     * @param g2
     * @return the difference graph
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph operator-(const Graph& g2) const;
    //TODO : bi-direction operator -

    /**
     *  creates the product of 2 graphs
     * @param g2
     * @return the product
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph operator*(const Graph& g2) const;
    //TODO : bi-direction operator *

    /**
     * complement of graph
     * @return the complement
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph operator!() const;

    /**
     * prints to stdout the Graph according to demands.
     * Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    std::string getString() const;

    /**
     * add a vertex to the graph
     * @param vertex
     *  Exceptions:
     *       IllegalVertexName() - if vertex name is invalid.
     *       VertexAlreadyExists() - if vertex already exists in the graph.
     *       std::bad_alloc() - if allocation problem
     */
    void addVertex(std::string& vertex);
    /**
     * add an edge to the graph between existing vertices.
     * @param src
     * @param dest
     * Exceptions:
     *       VertexNotExist() - if one of the vertices doesnt exist in the graph.
     *       SelfLoop() - if user tries to add a self loop.
     *       EdgeAlreadyExists() - if user tries to add parallel Edges
     *       std::bad_alloc() - if allocation problem
     */
    void addEdge(std::string& src, std::string& dest);

    /**
     * given a string of all the vertices, this function will add all vertices to the dst set
     * @param s_vertices
     *  Exceptions:
     *       IllegalVertexName() - if vertex name is invalid.
     *       VertexAlreadyExists() - if vertex already exists in the graph.
     *       std::bad_alloc() - if allocation problem
     */
    void addAllVertices(const std::string &s_vertices, std::set<std::string> &dst_set);

    /**
     * given a string of all the Edges, this function will add all edges to the dst map
     * @param s_edges
     * Exceptions:
     *       IllegalVertexName() - if one of the vertices`s name is invalid.
     *       std::bad_alloc() - if allocation problem
     *       VertexNotExist() - if one of the vertices doesnt exist in the graph.
     *       EdgeAlreadyExists() - if user tries to add parallel Edges
     *       SelfLoop() - if user tries to add a self loop.
     */
    void addAllEdges(const std::string &s_edges, std::set<pairs> &dst_set);
    /**
     * return a copy of vertices set
     * @return
     */
    std::set<std::string> getVertices();

    /**
     * return a copy of edges set
     * @return
     */
    std::set<pairs> getEdges();
};

/**
 * Check if name is a valid Vertex name
 * @param name
 * @return
 */
bool isValidVertexName(const std::string &name);
/**
 *      create the product vertex string.
 * @param vertex_1
 * @param vertex_2
 * @return
 * Exceptions:
 *      std::bad_alloc if allocation problem.
 */
std::string buildProductVertex(std::string vertex_1,std::string vertex_2);

#endif //MTM_FINALPROJECT_GRAPH_H
#endif //SWIG
