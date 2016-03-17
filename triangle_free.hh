#pragma once

#include "property.hh"

class Triangle_Free: public Property {
	private:
		uint32_t available_edges;
	public:
		Triangle_Free(Graph& g);
		virtual bool is_valid(uint16_t u, uint16_t v);
		virtual bool game_ended(uint16_t u, uint16_t v);
};
