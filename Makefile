CXX = g++

CXXFLAGS = -std=c++11 -Wall -g

SRC = Graph.cpp Edge.cpp Node.cpp Algorithms.cpp UnionFind.cpp PriorityQueue.cpp Stack.cpp
OBJ = Graph.o Edge.o Node.o Algorithms.o UnionFind.o PriorityQueue.o Stack.o  

TEST_SRC = graphTest.cpp algoTest.cpp dataTest.cpp
TEST_OBJ = graphTest.o algoTest.o dataTest.o  

TARGET = main
TEST_TARGET = test  

all: Main

Main: $(OBJ) main.o
	$(CXX) -o $(TARGET) $(OBJ) main.o

Graph.o: Graph.cpp Graph.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Graph.cpp

Edge.o: Edge.cpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Edge.cpp

Node.o: Node.cpp Node.hpp
	$(CXX) $(CXXFLAGS) -c Node.cpp

Algorithms.o: Algorithms.cpp Algorithms.hpp Graph.hpp PriorityQueue.hpp UnionFind.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c Algorithms.cpp

UnionFind.o: UnionFind.cpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c UnionFind.cpp

PriorityQueue.o: PriorityQueue.cpp PriorityQueue.hpp
	$(CXX) $(CXXFLAGS) -c PriorityQueue.cpp

Stack.o: Stack.cpp Stack.hpp
	$(CXX) $(CXXFLAGS) -c Stack.cpp

main.o: main.cpp Graph.hpp Algorithms.hpp PriorityQueue.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Test: $(OBJ) $(TEST_OBJ)
	$(CXX) -o $(TEST_TARGET) $(OBJ) $(TEST_OBJ)

graphTest.o: graphTest.cpp Graph.hpp Algorithms.hpp PriorityQueue.hpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c graphTest.cpp

algoTest.o: algoTest.cpp Graph.hpp Algorithms.hpp PriorityQueue.hpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c algoTest.cpp

dataTest.o: dataTest.cpp Graph.hpp Algorithms.hpp PriorityQueue.hpp UnionFind.hpp
	$(CXX) $(CXXFLAGS) -c dataTest.cpp

graphTest: $(OBJ) graphTest.o
	$(CXX) -o graphTest $(OBJ) graphTest.o

test: Test
	./$(TEST_TARGET)

valgrind: Main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET) graphTest

.PHONY: all clean test
