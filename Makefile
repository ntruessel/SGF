CXX ?= g++
CXXFLAGS = -std=c++11 -g -Wall -Wextra

SRC = $(wildcard *.cc)

all: framework

framework: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

