CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -O3

SRC = sgf.cc \
	  graph.cc \
	  triangle_free_graph.cc \
	  external_strategy.cc

STRATEGY_SRC = graph.cc \
			   triangle_free_graph.cc

all: sgf

sgf: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

%: %.cc $(STRATEGY_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $+
