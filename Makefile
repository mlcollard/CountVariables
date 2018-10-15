# Build for variableCount()

variableCount_u : variableCount.o variableCount_u.o
	g++ -std=c++11 variableCount.o variableCount_u.o -lxml2 -o variableCount_u

variableCount_u.o : variableCount_u.cpp variableCount.hpp
	g++ -std=c++11 -c variableCount_u.cpp

variableCount.o : variableCount.cpp variableCount.hpp
	g++ -I/usr/include/libxml2 -std=c++11 -c variableCount.cpp
