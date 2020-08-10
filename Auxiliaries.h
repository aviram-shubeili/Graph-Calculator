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
#define PRINT_LEN 5
#define DELETE_LEN 6
#define SAVE_LEN 4
#define LOAD_LEN 4

enum WorkMode {BATCH, SHELL};
enum Commands {DELETE, SAVE, LOAD, PRINT};
enum {PLUS='+',MINUS='-',MULT='*',INTER = '^' };
typedef  std::pair<const std::string, const unsigned int>  name_len_pair;

const std::map<Commands,const name_len_pair> enumToString = {
        {DELETE,std::make_pair("delete",DELETE_LEN)},
        {SAVE, std::make_pair("save",SAVE_LEN)},
        {LOAD, std::make_pair("load",LOAD_LEN)},
        {PRINT,std::make_pair("print",PRINT_LEN) }
};


const std::set<std::string> SAVED_WORDS = {
        "quit",
        "who",
        "print",
        "reset",
        "delete",
        "save",
        "load"
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
