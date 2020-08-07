cmake_minimum_required(VERSION 3.17)
project(mtm_FinalProject)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(mtm_FinalProject
        Graph.cpp
        GraphCalc.cpp
        GraphCalc.h
        Auxiliaries.cpp
        Auxiliaries.h
        Calc.cpp
        Calc.h
        GraphExceptions.cpp
        GraphExceptions.h
        CalcExceptions.cpp
        CalcExceptions.h
        Exceptions.cpp
        Exceptions.h
        PyInterface.cpp
        PyInterface.h)
