#pragma once

#include <vector>
#include <cstdint>

enum Entry {
	empty = 0,
	mini = 1,
	maxi = 2
};

class Graph {
	private:
		std::vector<std::vector<Entry>> adjacency_matrix;
	public:
		Graph(uint16_t n);
		uint16_t n(void);
		void set(uint16_t u, uint16_t v, Entry e);
		Entry get(uint16_t u, uint16_t v);
};
