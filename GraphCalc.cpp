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

void startCalc(istream &input, ostream &output, WorkMode mode) {

    Calc calc;
    string current_line;
    if(mode == SHELL) {
        output << "Gcalc> ";
    }
    while (std::getline(input, current_line)) {
#ifndef NDEBUG
        output << "**********  " << current_line << "   **********" << std::endl;
#endif
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
            else if (isACommand(current_line,PRINT)) {
                string to_print = current_line.substr(PRINT_LEN);
                to_print = trim(to_print);
                if (not (startsWith(to_print, "(") and endsWith(to_print, ")"))) {
                    throw CommandNotInFormat();
                } else {
                    // deleting '(' character
                    to_print = to_print.substr(WITHOUT_OPEN_BRACKET);
                    // deleting ')' character
                    to_print.pop_back();
                    to_print = trim(to_print);
                    output << (makeGraph(to_print, calc)).getString();
                }
            }
                // ****************** deleting ******************
                // TODO stopped here!!
            else if (isACommand(current_line,DELETE)) {

                    string to_delete = current_line.substr(DELETE_LEN);
                    to_delete = trim(to_delete);
                    if (not(startsWith(to_delete, "(") and endsWith(to_delete, ")"))) {
                        throw CommandNotInFormat();
                    } else {
                        // deleting '(' character
                        to_delete = to_delete.substr(WITHOUT_OPEN_BRACKET);
                        // deleting ')' character
                        to_delete.pop_back();
                        to_delete = trim(to_delete);
                        calc.erase(to_delete);
                    }

            }
                // ****************** saving ******************
            else if (isACommand(current_line,SAVE)) {
                string to_save = current_line.substr(SAVE_LEN);
                to_save = trim(to_save);

                // doesnt begin with ( or doesnt end with )
                if (not (startsWith(to_save, "(") and endsWith(to_save, ")"))) {
                    throw CommandNotInFormat();
                }
                else {
                    // deleting '(' character
                    to_save = to_save.substr(WITHOUT_OPEN_BRACKET);
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

                calc.addGraph(dest_g, makeGraph(src_g, calc));

            }


        }
        catch (std::out_of_range& e) {
            output << "Error: Graph not found. \n";
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
            output << "Gcalc> ";
        }

    }
}

void initSave(const string &s_save, Calc &calc) {
    size_t sep_pos = s_save.find_last_of(",");
    if(sep_pos == string::npos) {
        throw CommandNotInFormat();
    }
    string g_name = s_save.substr(0,sep_pos);
    string file_name = s_save.substr(sep_pos + 1);
    g_name = trim(g_name);
    file_name = trim(file_name);
    calc.save(makeGraph(g_name, calc), file_name);


}

bool isACommand(std::string line, Commands command) {

    return startsWith(line, enumToString.at(command).first) and
           line.length() >  enumToString.at(command).second and
           (line[enumToString.at(command).second] == ' ' or line[enumToString.at(command).second] == '(');
}

Graph makeGraph(std::string data, Calc &calc) {

    for(int  i = data.length() - 1; i >= 0 ; i-- ) {

        switch (data.at(i)) {
            case PLUS:
                return makeGraph(data.substr(0, i), calc) +
                       makeGraph(data.substr(i + 1), calc);

            case MINUS:
                return makeGraph(data.substr(0, i), calc) -
                       makeGraph(data.substr(i + 1), calc);


            case MULT:
                return makeGraph(data.substr(0, i), calc) *
                       makeGraph(data.substr(i + 1), calc);

            case INTER:
                return makeGraph(data.substr(0, i), calc) ^
                       makeGraph(data.substr(i + 1), calc);


        }
    }
    data = trim(data);

    // *************** loading a graph from binary file ***************
    if(isACommand(data, LOAD)) {
        string file_name = data.substr(LOAD_LEN);
        file_name = trim(file_name);
        if (not (startsWith(file_name, "(") and endsWith(file_name, ")"))) {
            throw CommandNotInFormat();
        } else {
            // deleting '(' character
            file_name = file_name.substr(WITHOUT_OPEN_BRACKET);
            // deleting ')' character
            file_name.pop_back();
            file_name = trim(file_name);
            return calc.load(file_name);
        }
    }
    // *************** need to complement ***************
    if(startsWith(data, "!")) {
        string compl_data;
        compl_data = data.substr(WITHOUT_COMPLEMENT);
        return !makeGraph(compl_data,calc);
    }
    // if data is saved
    if(calc.saved_graphs.find(data) != calc.saved_graphs.end()) {

        return calc.saved_graphs.at(data);
    }
    // it isnt a saved graph - lets try to make one.
    return Graph(data);
}

