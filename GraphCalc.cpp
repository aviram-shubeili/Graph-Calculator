//
// Created by avira on 03/08/2020.
//

#include "GraphCalc.h"
#include "Graph.h"
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <memory>
#include "Calc.h"
#define BATCH_MODE (argc == 3)
#define SHELL_MODE (argc == 1)
#define START_OF_LINE 0
#define PRINT_LEN 6


enum WorkMode {BATCH, SHELL};
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cin;
using std::cout;
using std::string;
using std::shared_ptr;

const char* kClose = ")";
void startCalc(istream &input, ostream &output, WorkMode mode);

string & ltrim(string &str);

string & rtrim(string &str);

void printWho(ostream &output);

void reset();


/**
 * TODO
 * @param line
 * @return
 */
bool isValidQuit(string& line) {
    //TODO:
    return true;
}
int main(int argc, char* argv[]) {






    if(BATCH_MODE) {
        // TODO: is slicing??
        ifstream temp_input(argv[1]);
        ofstream temp_output(argv[2]);
        if(!temp_input || !temp_output) {
            // TODO cant open file!
        }
        startCalc(temp_input, temp_output, BATCH);
    }
    else if(SHELL_MODE) {
        startCalc(cin, cout, SHELL);
    }
    else {
        // TODO: argc > 3 --> FATAL ERROR!!!!
        return 0;
    }



    return 0;



}

void startCalc(istream &input, ostream &output, WorkMode mode) {

    Calc calc;
    string current_line;
    if(mode == SHELL) {
        output << "Gcalc>";
    }
    // TODO: exceptions catch
    while(std::getline(input, current_line) ) {
        ltrim(rtrim(current_line));
        // ****************** who ******************
        if(current_line == "who") {
            output << calc;
        }
            // ****************** resetting ******************
        else if(current_line == "reset") {
            calc.reset();
        }
            // ****************** quitting ******************
        else if(current_line == "quit") {
            break;
        }

            // ****************** printing ******************
        else if(current_line.find("print(") == START_OF_LINE) {
            string to_print = current_line.substr(PRINT_LEN);
            // doesnt end with )
            if(to_print.substr(to_print.length()-1) != kClose) {
                // TODO ERROR: print doesnt end with ).
            }
            else {
                to_print.pop_back();
                // TODO if invalid expression --> need to catch an out_of_range exception
                (calc.getGraph(to_print)).print();
            }
        }
            // ******************* starts with a Graph Name ************
        else {
            string dest_g;
            string rest;
            int end = current_line.find("=");
            if(end == string::npos) {
                // ERROR: no command.
            }
            dest_g = current_line.substr(0,end);
            rest = current_line.substr(end+1);

        }
        output << "Gcalc>" ;
    }
}
/**
 * TODO
 * @param name
 * @return
 * TODO Exceptions:
 *
 */




string & rtrim(string &str) {
    return str;
}

string & ltrim(string &str) {
    return str;
}
