%module graph
%include <std_string.i>
%include "PyInterface.h"
%{
#include "PyInterface.h"
using std::string;
typedef Graph* graph_ptr;
%}
