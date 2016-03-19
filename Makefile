CXX ?= g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

SRC = framework.cc \
	  graph.cc \
	  triangle_free_graph.cc \
	  external_strategy.cc

all: framework

framework: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

