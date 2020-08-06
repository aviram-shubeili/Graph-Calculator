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
            return 0;
        }
        startCalc(temp_input, temp_output, BATCH);
    }
    else if(SHELL_MODE) {
        startCalc(cin, cout, SHELL);
    }
    else {
        // FATAL ERROR - tried to run with 1 or more than 2 arguments.
        std::cerr << RunError().what();
        return 0;
    }

    return 0;

}
Graph evaluate(std::string data, Calc &calc) {

    for(size_t i = 0; i < data.length() ; i++ ) {

        switch (data[i]) {
            case PLUS:
                return evaluate(data.substr(0, i), calc) +
                       evaluate(data.substr(i + 1), calc);

            case MINUS:
                return evaluate(data.substr(0, i), calc) -
                       evaluate(data.substr(i + 1), calc);


            case MULT:
                return evaluate(data.substr(0, i), calc) *
                       evaluate(data.substr(i + 1), calc);

            case INTER:
                return evaluate(data.substr(0, i), calc) ^
                       evaluate(data.substr(i + 1), calc);

            case COMPL:
                return !evaluate(data.substr(0, i), calc);

        }
    }
    data = trim(data);
    if(calc.saved_graphs.find(data) != calc.saved_graphs.end()) {
        return calc.saved_graphs.at(data);
    }
    return Graph(data);
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
                    output << (evaluate(to_print,calc)).getString();
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
                // ****************** saving ******************
            else if (startsWith(current_line, "save(")) {
                string to_save = current_line.substr(SAVE_LEN);
                // doesnt end with )
                if (to_save.substr(to_save.length() - 1) != ")") {
                    throw CommandNotInFormat();
                }
                else {
                    // deleting ')' character
                    to_save.pop_back();
                    to_save = trim(to_save);
                    initSave(to_save,calc);
                }
            }
                // ******************* starts with a Graph Name ************
            else {
                string dest_g;
                string src_g;
                size_t end_of_dest = current_line.find('=');
                if (end_of_dest == string::npos) {
                    throw NoAssignmentOp();
                }
                dest_g = current_line.substr(0, end_of_dest);
                src_g = current_line.substr(end_of_dest + 1);
                src_g = trim(src_g);


                calc.addGraph(dest_g, evaluate(src_g,calc));












                // ********** loading a graph from binary file
                if(startsWith(src_g,"load(")) {
                    string file_name = src_g.substr(LOAD_LEN);
                    if (file_name.substr(file_name.length() - 1) != ")") {
                        throw CommandNotInFormat();
                    } else {
                        // deleting ')' character
                        file_name.pop_back();
                        file_name = trim(file_name);

                        calc.addGraph(dest_g, calc.load(file_name));
                    }


                }
                /*
                // *** init a graph ***
                else if (startsWith(src_g, "{")) {
                }
                    // !Graph
                else if (startsWith(src_g, "!")) {
                    calc.addGraph(dest_g, !calc.getGraph(src_g.substr(WITHOUT_COMPLEMENT)));

                }
                    // g1 <oper> g2
                else {
                    string g1, g2;
                    char oper;
                    size_t op_pos = findBinOperPos(src_g, oper);
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
*/
            }


        }
        catch (CommandNotInFormat& e) {
            output << e.what();
        }
        catch (InvalidFileName& e) {
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
        catch (CalcExceptions& e) {
            output << e.what();
        }
        catch (std::bad_alloc& e) {
            std::cerr << "Error: FATAL - allocation failed." << std::endl;
            break;
        }
        catch(...) {
            cout << "Error: Unknown Error Occurred \n" ;
        }
        if (mode == SHELL) {
            output << "Gcalc>";
        }

    }
}

void initSave(const string &s_save, Calc &calc) {
    size_t sep_pos = s_save.find(",");
    if(sep_pos == string::npos) {
        throw CommandNotInFormat();
    }
    string g_name = s_save.substr(0,sep_pos);
    string file_name = s_save.substr(sep_pos + 1);
    g_name = trim(g_name);
    file_name = trim(file_name);
    calc.save(g_name,file_name);


}

/**
 * returns the position of the first operand in str and stores it in operand
 * @param str
 * @param operand
 * @return
 * Exceptions:
 *      InvalidGraphName() if operand pos = 0
 */
size_t findBinOperPos(const string &str, char& oper) {
    size_t pos = string::npos;
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


