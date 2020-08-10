//
// Created by avira on 03/08/2020.
//

#ifndef MTM_FINALPROJECT_GRAPHCALC_H
#define MTM_FINALPROJECT_GRAPHCALC_H
#include "Graph.h"
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <memory>
#include <algorithm>
#include "Calc.h"
#include "Auxiliaries.h"
#define BATCH_MODE (argc == 3)
#define SHELL_MODE (argc == 1)
#define START_OF_LINE 0

#define WITHOUT_COMPLEMENT 1
#define WITHOUT_OPEN_BRACKET 1

/**
 * This function is the Calculator's driver after the workmode is defined.
 */
void startCalc(std::istream& input, std::ostream &output, WorkMode mode);

/**
 *      breaks down string to graph name and file name and initiate the save function.
 * @param s_save
 * Exceptions:
 *      CommandNotInFormat()
 *      InvalidGraphName()
 *      InvalidFileName()
 *      out_of_range() if one of the saved_graphs not exist
 *      OpenFileError()
 */
void initSave(const std::string &s_save, Calc &calc);

bool isACommand(std::string line, Commands command);
#endif //MTM_FINALPROJECT_GRAPHCALC_H

