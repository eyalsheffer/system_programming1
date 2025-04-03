# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Source files
SRCS = main.cpp Graph.cpp Algorithms.cpp PriorityQueue.cpp UnionFind.cpp Node.cpp Stack.cpp Edge.cpp

# Header files
HEADERS = Graph.hpp Algorithms.hpp PriorityQueue.hpp UnionFind.hpp Node.hpp Stack.hpp Edge.hpp

# Output executable
TARGET = main

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Clean the build
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program (for convenience)
run: $(TARGET)
	./$(TARGET)
