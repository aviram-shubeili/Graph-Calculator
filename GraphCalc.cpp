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
#define WITHOUT_COMPLEMENT 1

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

bool startsWith(const string& line,const string& starter);

void startCalc(istream &input, ostream &output, WorkMode mode);

string & ltrim(string &str);

string & rtrim(string &str);

string & trim(string &str);
void printWho(ostream &output);

void reset();


int findBinOperPos(const string &str, char& oper);

bool isBinaryOper(char c);

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
        else if(startsWith(current_line,"print(")) {
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
            string src_g;
            int end_of_dest = current_line.find("=");
            if(end_of_dest == string::npos) {
                // ERROR: no command.
            }
            dest_g = current_line.substr(0, end_of_dest);
            src_g = current_line.substr(end_of_dest + 1);
            trim(src_g);

            // *** init a graph ***
            if(startsWith(src_g,"{")) {
                // TODO: exception may be thrown from Graph or from Calc
                calc.addGraph(dest_g,Graph(src_g));
            }
            // !Graph
            if(startsWith(src_g,"!")) {
                // TODO exception from Calc!
                calc.addGraph(dest_g,calc.getGraph(src_g.substr(WITHOUT_COMPLEMENT)));

            }
                // g1 <oper> g2
            else {
                string g1, g2;
                char oper;
                // TODO catch Exception from findoperpos....!
                int op_pos = findBinOperPos(src_g, oper);
                // there is no operand
                if(op_pos == string::npos) {
                    calc.addGraph(dest_g,calc.getGraph(src_g));
                }
                    // there is an operand
                else {
                    g1 = src_g.substr(START_OF_LINE,op_pos);
                    g2 = src_g.substr(op_pos+1);
                    // TODO Exceptions
                    calc.addGraph(dest_g, calc.applyOper(g1, oper, g2));
                }

            }

        }

        if(mode == SHELL) {
            output << "Gcalc>";
        }
    }
}
/**
 * returns the position of the first operand in str and stores it in operand
 * @param str
 * @param operand
 * @return
 * Exceptions:
 *      InvalidGraphName() if operand pos = 0
 */
int findBinOperPos(const string &str, char& oper) {
    int pos;
    for(char c : str) {
        if(isBinaryOper(c)) {
            pos = str.find(c);
            break;
        }
    }
    if(pos == START_OF_LINE) {
        // TODO throw InvalidGraphName();
    }
    return pos;
}

bool isBinaryOper(char c) {
    return c == '+' or c == '-' or c == '^' or c == '*';
}

/**
 * TODO
 * @param name
 * @return
 * TODO Exceptions:
 *
 */


bool startsWith(const string& line,const string& starter) {
    return line.find(starter) == START_OF_LINE;
}

string & rtrim(string &str) {
    for(string::reverse_iterator r_it = str.rbegin(); r_it != str.rend() ; r_it++) {

    }

}

string & ltrim(string &str) {
    return str;
}

string & trim(string &str) {
    return ltrim(rtrim(str));
}