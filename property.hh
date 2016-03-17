#pragma once

#include "graph.hh"

class Property {
	protected:
		Property(Graph& g);
	public:
		Graph& g;
		virtual bool is_valid(uint16_t u, uint16_t v) = 0;
		virtual bool game_ended(uint16_t u, uint16_t v) = 0;
};
