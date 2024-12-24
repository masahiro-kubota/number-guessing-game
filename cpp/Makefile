TARGET = main
SRCS = main.cpp
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TEXT = "this is a sample"

all: $(TARGET)

$(TARGET): $(SRCS)
	@$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	@rm -f $(TARGET)
