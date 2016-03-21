#include "triangle_free_graph.hh"

Triangle_Free_Graph::Triangle_Free_Graph(uint16_t n)
	: Graph(n)
	, available_edges(n * (n - 1) / 2) {}


void Triangle_Free_Graph::set(uint16_t u, uint16_t v, Entry e) {
	Graph::set(u,v,e);
	available_edges--;
	for (uint16_t i = 0; i < n(); i++) {
		if (u == i | v == i) {
			continue;
		}
		if ((adjacency_matrix[u][i] == Entry::mini ||		// - other edge is
				adjacency_matrix[u][i] == Entry::maxi) &&	//   taken
				adjacency_matrix[v][i] == Entry::empty) {	// - not counted yet
			adjacency_matrix[v][i] = Entry::blocked;
			adjacency_matrix[i][v] = Entry::blocked;
			available_edges--; // (u i) or (v i) would complete a triangle
		} else if ((adjacency_matrix[v][i] == Entry::mini ||
				adjacency_matrix[v][i] == Entry::maxi) &&
				adjacency_matrix[u][i] == Entry::empty) {
			adjacency_matrix[u][i] = Entry::blocked;
			adjacency_matrix[i][u] = Entry::blocked;
			available_edges--; // (u i) or (v i) would complete a triangle
		}
	}
}

bool Triangle_Free_Graph::is_valid(uint16_t u, uint16_t v, Entry e) {
	return u < n() && v < n() && u != v &&			// Sanity check
		(e == Entry::mini || e == Entry::maxi) &&	// only mini/maxi
		adjacency_matrix[u][v] == Entry::empty;		// only empty edges
	// We don't have to check whether (u,v) creates a triangle, because then
	// adjacency_matrix[u][v] would be Entry::blocked
}

bool Triangle_Free_Graph::saturated(void) {
	return available_edges == 0;
}
