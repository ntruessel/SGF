#include "triangle_free.hh"

Triangle_Free::Triangle_Free(Graph& g)
	: Property(g), available_edges((g.n() * (g.n() - 1)) / 2) {}

bool Triangle_Free::is_valid(uint16_t u, uint16_t v) {
	uint16_t n = g.n();
	if (u >= n || v >= n || u == v
			|| g.get(u,v) != Entry::empty || g.get(v,u) != Entry::empty) {
		return false;
	}

	for (uint16_t i = 0; i < n; i++) {
		if (g.get(u,i) != Entry::empty && g.get(v,i) != Entry::empty) {
			return false; // Triangle (u,v,i) found
		}
	}

	return true;
}
