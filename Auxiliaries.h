//
// Created by avira on 04/08/2020.
//

#ifndef MTM_FINALPROJECT_AUXILIARIES_H
#define MTM_FINALPROJECT_AUXILIARIES_H
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <memory>
#include <set>
#include <utility>
#include <assert.h>
#include <algorithm>
#include <iterator>
#include "Graph.h"
#include "Calc.h"
#include "GraphExceptions.h"
#include "CalcExceptions.h"

enum WorkMode {BATCH, SHELL};

// TODO add to saved words ?
const std::set<std::string> SAVED_WORDS = {
        "quit",
        "who",
        "print",
        "reset",
        "delete",

};


/**
 * check if line starts with substring starter
 */
bool startsWith(const std::string& line,const std::string& starter);

/**
 * check if line ends with substring ender
 */
bool endsWith(const std::string& line, const std::string& ender);

/**
 * trim all white spaces from the end of the string and returns a copy of the trimmed str
 */
std::string rtrim(std::string &str);

/**
 * trim all white spaces from the start of the string and returns a copy of the trimmed str
 */
std::string ltrim(std::string &str);

/**
 * trim all white spaces from the start and end of the string and returns a copy of the trimmed str
 */
std::string trim(std::string &str);

#endif //MTM_FINALPROJECT_AUXILIARIES_H
