# Compiler
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

# Source and target
SRC := src/main.cpp
TARGET := sacompiler

# Default rule
all: $(TARGET)

$(TARGET): $(SRC) 
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean rule
clean:
	del /f $(TARGET).exe

.PHONY: all clean
