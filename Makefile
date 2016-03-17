CXX ?= g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

SRC = graph.cc \
	  triangle_free_graph.cc \
	  framework.cc

all: framework

framework: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

