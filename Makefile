# Makefile for Matrix Operations

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Define source files
SRCS = MatrixQuestions.cpp

# Define the output executable
TARGET = matrix_operations

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean target
clean:
	rm -f $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run