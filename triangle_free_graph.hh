#pragma once

#include "graph.hh"

class Triangle_Free_Graph : public Graph {
	private:
		uint16_t available_edges;
	public:
		Triangle_Free_Graph(uint16_t n);
		virtual void set(uint16_t u, uint16_t v, Entry e);
		virtual bool is_valid(uint16_t u, uint16_t v, Entry e);
		virtual bool saturated(void);
};
