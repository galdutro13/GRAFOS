cmake_minimum_required(VERSION 3.25)
project(GRAFOS)

set(CMAKE_CXX_STANDARD 20)

add_executable(GRAFOS main.cpp LateConst.h)

add_executable(EMAIL_SPAM exercicio_10.cpp LateConst.h)

add_executable(DETECTOR_DE_CICLOS cycle_detector.cpp LateConst.h)