# Compiler
CXX = g++

# Flags
CXXFLAGS = -std=c++11 -Wall -g

# Source files (list them explicitly)
SRC = Graph.cpp Edge.cpp Node.cpp Algorithms.cpp UnionFind.cpp PriorityQueue.cpp Stack.cpp
OBJ = Graph.o Edge.o Node.o Algorithms.o UnionFind.o PriorityQueue.o Stack.o  # Object files for source code

# Test files (list them explicitly)
TEST_SRC = graphTest.cpp algoTest.cpp dataTest.cpp
TEST_OBJ = graphTest.o algoTest.o dataTest.o  # Object files for tests

# Executable names
TARGET = main
TEST_TARGET = test  # For running tests

# Default target (build the main program)
all: Main

# Build the main executable (includes main.cpp)
Main: $(OBJ) main.o
	$(CXX) -o $(TARGET) $(OBJ) main.o

# Compile object files for source files
Graph.o: Graph.cpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c Graph.cpp

Edge.o: Edge.cpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Edge.cpp

Node.o: Node.cpp Node.hpp
	$(CXX) $(CXXFLAGS) -c Node.cpp

Algorithms.o: Algorithms.cpp Algorithms.hpp Graph.hpp PriorityQueue.hpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c Algorithms.cpp

UnionFind.o: UnionFind.cpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c UnionFind.cpp

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.hpp
	$(CXX) $(CXXFLAGS) -c PriorityQueue.cpp

Stack.o: Stack.cpp Stack.hpp
	$(CXX) $(CXXFLAGS) -c Stack.cpp

main.o: main.cpp Graph.hpp Algorithms.hpp PriorityQueue.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Test target (compile only the necessary object files and build the test executable)
Test: $(OBJ) $(TEST_OBJ)
	$(CXX) -o $(TEST_TARGET) $(OBJ) $(TEST_OBJ)

# Compile test object files
graphTest.o: graphTest.cpp Graph.hpp Algorithms.hpp PriorityQueue.hpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c graphTest.cpp

algoTest.o: algoTest.cpp Graph.hpp Algorithms.hpp PriorityQueue.hpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c algoTest.cpp

dataTest.o: dataTest.cpp Graph.hpp Algorithms.hpp PriorityQueue.hpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c dataTest.cpp

# Build the graphTest executable (without including the main program)
graphTest: $(OBJ) graphTest.o
	$(CXX) -o graphTest $(OBJ) graphTest.o

# Run the test executable
test: Test
	./$(TEST_TARGET)

# Run Valgrind memory check on the main executable
valgrind: Main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Clean build files
clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET) graphTest

.PHONY: all clean test
