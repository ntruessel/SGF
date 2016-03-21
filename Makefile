CXX ?= g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

SRC = sgf.cc \
	  graph.cc \
	  triangle_free_graph.cc \
	  external_strategy.cc

all: sgf

sgf: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

