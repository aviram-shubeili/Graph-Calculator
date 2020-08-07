//
// Created by avira on 04/08/2020.
//

#ifndef MTM_FINALPROJECT_CALC_H
#define MTM_FINALPROJECT_CALC_H
#include "Auxiliaries.h"
#include "Graph.h"

class Calc {
    std::map<std::string,class Graph> saved_graphs;

    friend Graph makeGraph(std::string data, Calc &calc);
public:
    /**
     * Create a New Calc with empty map of saved_graphs
     * Exceptions:
     *      std::bad_alloc() - if allocation problem.
     */
    Calc() = default;
    /**
     * no need to copy calculator.
     */
    Calc(const Calc&) = delete;
    /**
     * no need to reassign a calculator
     */
    Calc& operator=(const Calc&) = delete;
    /**
     * Default D'or.
     */
    ~Calc() = default;

    /**
     * Checks if g_name is valid and adds the graph to the memory
     * @param g
     * Exceptions:
     *      InvalidGraphName()
     */
    void addGraph(std::string &g_name, Graph g);
    /**
     * if graph Exists in memory return a copy of it, if not - exception will be thrown
     *
     * @param g_name
     * @return
     * Exceptions
     *      out_of_range() if not exists
     */
    Graph getGraph(std::string g_name) const;
    /**
     * reset the graph map
     */
    void reset();

    /**
     * This deletes a graph from the saved graphs
     * Exceptions:
     *      GraphNotFound() - if graph is not in saved in calc.
     */
    void erase(std::string to_delete);

    /**
     * getString to os the names of all saved_graphs known to Calc.
     * @param os
     * @param to_print
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const Calc &to_print);

    /**
     *  * Check if name is a valid Graph name
     * @param g_name
     * @return
     * Exceptions:
     *      none
     */
    static bool isValidGraphName(const std::string &g_name);

    /**

     * @param g
     * @param file_name
     * Exceptions:
     *      InvalidGraphName()
     *      InvalidFileName()
     *      out_of_range() if one of the saved_graphs not exist
     *      OpenFileError()
     */
    void save(Graph g, const std::string &file_name);

    /**
     * @param file_name
     * @return
     * Exceptions:
     *       InvalidFileName()
     *       IllegalVertexName() - if vertex name is invalid.
     *       VertexAlreadyExists() - if vertex already exists in the graph.
     *       VertexNotExist() - if one of the vertices doesnt exist in the graph.
     *       SelfLoop() - if user tries to add a self loop.
     *       EdgeAlreadyExists() - if user tries to add parallel Edges
     *       std::bad_alloc() - if allocation problem
     */
    Graph load(const std::string &file_name);
    /**
     * false if name contains a ',' true otherwise.
     * @param file_name
     * @return
     */
    static bool isValidFileName(const std::string &file_name);
};


#endif //MTM_FINALPROJECT_CALC_H
