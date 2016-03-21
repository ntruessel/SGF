CXX ?= g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

SRC = triangle_free_graph_test.cc \
	  ../graph.cc \
	  ../triangle_free_graph.cc \

all: triangle_test

triangle_test: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

