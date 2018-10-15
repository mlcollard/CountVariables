# Build for variableCount()

.PHONY: all
all : variableCount_u variableCount_t

variableCount_u : variableCount.o variableCount_u.o
	g++ -std=c++11 variableCount.o variableCount_u.o -lxml2 -o variableCount_u

variableCount_u.o : variableCount_u.cpp variableCount.hpp
	g++ -std=c++11 -c variableCount_u.cpp

variableCount.o : variableCount.cpp variableCount.hpp
	g++ -I/usr/include/libxml2 -std=c++11 -c variableCount.cpp

variableCount_t : variableCount.o variableCount_t.o
	g++ -std=c++11 variableCount.o variableCount_t.o -lxml2 -o variableCount_t

variableCount_t.o : variableCount_t.cpp variableCount.hpp
	g++ -std=c++11 -c variableCount_t.cpp

.PHONY: clean
clean : 
	@rm -f variableCount.o variableCount_u.o variableCount_u variableCount_t.o variableCount_t

.PHONY: run
run : variableCount_u
	./variableCount_u example.xml

.PHONY: test
test : variableCount_t
	./variableCount_t
