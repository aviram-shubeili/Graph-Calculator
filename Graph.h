//
// Created by avira on 03/08/2020.
//

#ifndef MTM_FINALPROJECT_GRAPH_H
#define MTM_FINALPROJECT_GRAPH_H
#include <iostream>
#include <set>
#include <utility>

class Graph {
private:
    // TODO try catch!
    std::set<std::string> Vertices;
    std::set<std::pair<std::string,std::string>> Edges; // todo: maybe map???

public:
    /**
     * Create a Graph from a string : { **Vertices** | **Edges** }
     * @param data
     *  Exceptions:
     *      InvalidGraphData() - if data is not at the format.
     *      IllegalEdgeData() - if one of the edges data is invalid - uses a vertex that doesnt exists / illegal name.
     *      IllegalVertexName() - if one of the vertices`s name is invalid.
     *      std::bad_alloc() - if allocation problem
     */
    Graph(const std::string& data);    //TODO:  should it be explicit?
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
    Graph(const Graph& other);    //TODO:  should it be explicit?

    /**
     * Assignment operator - current graph will be overridden
     *
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph& operator=(const Graph& other);

    /**
     *  union of 2 graphs
     * @param g2
     * @return the united graph
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph operator+(const Graph& g2) const;
    //TODO: bi-direction operator +

    /**
     * create an intersection of 2 graphs
     * @param g2
     * @return the intersected graph
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph operator^(const Graph& g2) const;
    // TODO: bi-direction operator ^

    /**
     * creates the difference of this graph and g2
     * @param g2
     * @return the difference graph
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph operator-(const Graph& g2) const;
    //TODO: bi-direction operator -

    /**
     *  creates the product of 2 graphs
     * @param g2
     * @return the product
     *  Exceptions:
     *       std::bad_alloc() - if allocation problem
     */
    Graph operator*(const Graph& g2) const;
    //TODO: bi-direction operator *

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
     * TODO: ?
     */
    void print() const;

    /**
     * add a vertex to the graph
     * @param vertex
     *  Exceptions:
     *       IllegalVertexName() - if vertex name is invalid.
     *       std::bad_alloc() - if allocation problem
     */
    void addVertex(std::string& vertex);
    /**
     * add an edge to the graph between existing vertices.
     * @param src
     * @param dest
     *       IllegalVertexName() - if one of the vertices`s name is invalid.
     *       std::bad_alloc() - if allocation problem
     *       VertexNotExist() - if one of the vertices doesnt exist in the graph.
     */
    void addEdge(std::string& src, std::string& dest);
};


#endif //MTM_FINALPROJECT_GRAPH_H
