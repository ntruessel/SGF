CXX ?= g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

all: framework

%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<
