CXX = g++
STD = -std=c++17
WARNINGS = -Wall -Wextra -Weffc++
ERRORS = -pedantic-errors 
SANITIZERS = -fsanitize=address,undefined
COVERAGE = --coverage
DEBUGGING = -g
CXXFLAGS = $(STD) $(WARNINGS) $(ERRORS) $(DEBUGGING)

default: build

build: main.cpp linked_list.hpp tests.cpp
	$(CXX) $(CXXFLAGS) main.cpp tests.cpp

test: main.cpp linked_list.hpp tests.cpp
	$(CXX) $(CXXFLAGS) main.cpp tests.cpp && ./a.out

coverage: clean main.cpp linked_list.hpp tests.cpp
	$(CXX) $(STD) $(DEBUGGING) $(COVERAGE) main.cpp tests.cpp && ./a.out && gcov -mr tests.cpp

memoryerrortest: main.cpp linked_list.hpp tests.cpp
	$(CXX) $(STD) $(DEBUGGING) $(SANITIZERS) main.cpp tests.cpp && ./a.out

.PHONY: clean

clean:
	rm -f *.gcda *.gcno *.gcov a.out


