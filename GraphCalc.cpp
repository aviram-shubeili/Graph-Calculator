//
// Created by avira on 03/08/2020.
//

#include "GraphCalc.h"
#include "Auxiliaries.h"
#include "Calc.h"

using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cin;
using std::cout;
using std::string;
using std::shared_ptr;




int main(int argc, char* argv[]) {

    if(BATCH_MODE) {
        ifstream temp_input(argv[1]);
        ofstream temp_output(argv[2]);
        if(!temp_input || !temp_output) {
            // FATAL ERROR
            std::cerr << OpenFileError().what();
        }
        startCalc(temp_input, temp_output, BATCH);
    }
    else if(SHELL_MODE) {
        startCalc(cin, cout, SHELL);
    }
    else {
        // FATAL ERROR - tried to run with 1 or more than 2 arguments.
        std::cerr << RunError().what();
    }

    return 0;

}

void startCalc(istream &input, ostream &output, WorkMode mode) {

    Calc calc;
    string current_line;
    if(mode == SHELL) {
        output << "Gcalc>";
    }
    while (std::getline(input, current_line)) {
        try {
            current_line = trim(current_line);
            // ****************** who ******************
            if (current_line == "who") {
                output << calc;
            }
                // ****************** resetting ******************
            else if (current_line == "reset") {
                calc.reset();
            }
                // ****************** quitting ******************
            else if (current_line == "quit") {
                break;
            }

                // ****************** printing ******************
            else if (startsWith(current_line, "print(")) {
                string to_print = current_line.substr(PRINT_LEN);
                // doesnt end with )
                if (to_print.substr(to_print.length() - 1) != ")") {
                    throw CommandNotInFormat();
                }
                else {
                    // deleting ')' character
                    to_print.pop_back();
                    (calc.getGraph(to_print)).print(output);
                }
            }
                // ****************** deleting ******************
            else if (startsWith(current_line, "delete(")) {
                string to_delete = current_line.substr(DELETE_LEN);
                // doesnt end with )
                if (to_delete.substr(to_delete.length() - 1) != ")") {
                    throw CommandNotInFormat();
                }
                else {
                    // deleting ')' character
                    to_delete.pop_back();
                    calc.erase(to_delete);
                }
            }
                // ******************* starts with a Graph Name ************
            else {
                string dest_g;
                string src_g;
                int end_of_dest = current_line.find("=");
                if (end_of_dest == string::npos) {
                    throw NoAssignmentOp();
                }
                dest_g = current_line.substr(0, end_of_dest);
                src_g = current_line.substr(end_of_dest + 1);
                src_g = trim(src_g);

                // *** init a graph ***
                if (startsWith(src_g, "{")) {
                    calc.addGraph(dest_g, Graph(src_g));
                }
                // !Graph
                else if (startsWith(src_g, "!")) {
                    calc.addGraph(dest_g, !calc.getGraph(src_g.substr(WITHOUT_COMPLEMENT)));

                }
                    // g1 <oper> g2
                else {
                    string g1, g2;
                    char oper;
                    int op_pos = findBinOperPos(src_g, oper);
                    // there is no operand
                    if (op_pos == string::npos) {
                        calc.addGraph(dest_g, calc.getGraph(src_g));
                    }
                        // there is an operand
                    else {
                        g1 = src_g.substr(START_OF_LINE, op_pos);
                        g2 = src_g.substr(op_pos + 1);
                        calc.addGraph(dest_g, calc.applyOper(g1, oper, g2));
                    }

                }

            }


        }
    catch (CommandNotInFormat& e) {
        output << e.what();
    }
    catch (std::out_of_range& e) {
        output << "Error: Graph not found. \n";
    }
    catch (NoAssignmentOp& e) {
        output << e.what();
    }
    catch (InvalidGraphName& e) {
        output << e.what();
    }
    catch (GraphExceptions& e) {
        output << e.what();
    }
    catch(...) {
        cout << "   Unknown Error Occurred";
    }
        if (mode == SHELL) {
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
    int pos = string::npos;
    for(char c : str) {
        if(isBinaryOper(c)) {
            pos = str.find(c);
            oper = c;
            break;
        }
    }
    if(pos == START_OF_LINE) {
        throw InvalidGraphName();
    }
    return pos;
}

bool isBinaryOper(char c) {
    return c == '+' or c == '-' or c == '^' or c == '*';
}


