CXX = /usr/local/bin/g++
COMP_FLAG = -std=c++11 -Wall -pedantic-errors -Werror -g
LIB_FLAG = -I/usr/local/include/python3.6m -fPIC
DEBUG_FLAG = -DNDEBUG
ZIP_NAME = gcalc.zip
EXEC = gcalc
PY_EXEC = libgraph.a PyInterface.o _graph.so graph_wrap.cpp
OBJS = GraphCalc.o Graph.o Calc.o Auxiliaries.o Exceptions.o CalcExceptions.o GraphExceptions.o
LIB_OBJS = PyInterface.o Graph.o GraphExceptions.o Auxiliaries.o Exceptions.o
PROJ_FILES = Auxiliaries.cpp Auxiliaries.h Calc.cpp Calc.h CalcExceptions.cpp CalcExceptions.h \
Exceptions.cpp Exceptions.h Graph.cpp Graph.h GraphCalc.cpp GraphCalc.h GraphExceptions.cpp GraphExceptions.h \
 test_in.txt test_out.txt Makefile # ************** add all files to PROJ_FILES!

$(EXEC): $(OBJS)
	$(CXX) $(COMP_FLAG) $(DEBUG_FLAG) *.cpp -o $(EXEC)


Auxiliaries.o: Auxiliaries.cpp GraphCalc.h Graph.h Auxiliaries.h Calc.h \
 GraphExceptions.h Exceptions.h CalcExceptions.h
	$(CXX)  -fPIC -c $(DEBUG_FLAG) $(COMP_FLAG) $^

Calc.o: Calc.cpp Calc.h Auxiliaries.h Graph.h GraphExceptions.h \
 Exceptions.h CalcExceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $^

CalcExceptions.o: CalcExceptions.cpp CalcExceptions.h Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $^

Exceptions.o: Exceptions.cpp Exceptions.h
	$(CXX) -fPIC  -c $(DEBUG_FLAG) $(COMP_FLAG) $^

GraphCalc.o: GraphCalc.cpp GraphCalc.h Graph.h Auxiliaries.h Calc.h \
 GraphExceptions.h Exceptions.h CalcExceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $^

Graph.o: Graph.cpp Graph.h Auxiliaries.h Calc.h GraphExceptions.h \
Exceptions.h CalcExceptions.h
	$(CXX) -fPIC  -c $(DEBUG_FLAG) $(COMP_FLAG) $^

GraphExceptions.o: GraphExceptions.cpp GraphExceptions.h Exceptions.h
	$(CXX)   -fPIC -c $(DEBUG_FLAG) $(COMP_FLAG) $^

PyInterface.o: PyInterface.cpp PyInterface.h Auxiliaries.h Graph.h Calc.h \
 GraphExceptions.h Exceptions.h CalcExceptions.h
	$(CXX) -fPIC -c $(DEBUG_FLAG) $(COMP_FLAG) PyInterface.cpp

libgraph.a: $(LIB_OBJS)
	ar -rs $@ $^

swig: libgraph.a
	swig -c++ -python -o graph_wrap.cpp graph.i
	$(CXX) -std=c++11 -DNDEBUG --pedantic-errors -Wall -Werror -I/usr/local/include/python3.6m -fPIC -shared graph_wrap.cpp libgraph.a -o _graph.so

tar:
	zip $(ZIP_NAME) $(PROJ_FILES)

clean:
	rm -f $(OBJS) $(EXEC) $(PY_EXEC) *.h.gch
