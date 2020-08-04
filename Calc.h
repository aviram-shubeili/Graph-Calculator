//
// Created by avira on 04/08/2020.
//

#ifndef MTM_FINALPROJECT_CALC_H
#define MTM_FINALPROJECT_CALC_H
#include "Auxiliaries.h"
#include "Graph.h"

class Calc {
    std::map<std::string,Graph> graphs;

public:
    Calc();
    Calc(const Calc&) = delete;
    Calc& operator=(const Calc&) = delete;
    ~Calc();

    /**
     * Checks if g_name is valid and adds the graph to the memory
     * @param g
     * TODO
     * Exceptions:
     *
     */
    void addGraph(std::string g_name, Graph& g);
    /**
     * if graph Exists in memory return a copy of it, if not - exception will be thrown
     *
     * @param g_name
     * @return
     * TODO:
     * Exceptions
     *      out_of_range() if not exists
     */
    Graph getGraph(std::string g_name) const;
    /**
     * reset the graph map
     */
    void reset();

    /**
     * print to os the names of all graphs known to Calc.
     * @param os
     * @param to_print
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const Calc &to_print);
};


#endif //MTM_FINALPROJECT_CALC_H
