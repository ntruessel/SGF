#pragma once

#include <vector>
#include <cstdint>

enum Entry {
	empty = 0,
	mini = 1,
	maxi = 2
};

class Graph {
	protected:
		std::vector<std::vector<Entry>> adjacency_matrix;
		Graph(uint16_t n);
	public:
		uint16_t n(void);
		virtual bool is_valid(uint16_t u, uint16_t v, Entry e) = 0;
		virtual bool saturated(void) = 0;
		virtual void set(uint16_t u, uint16_t v, Entry e);
		Entry get(uint16_t u, uint16_t v);
};
