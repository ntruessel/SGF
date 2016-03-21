#include "triangle_free_graph.hh"

Triangle_Free_Graph::Triangle_Free_Graph(uint16_t n)
	: Graph(n)
	, available_edges(n * (n - 1) / 2) {}


void Triangle_Free_Graph::set(uint16_t u, uint16_t v, Entry e) {
	Graph::set(u,v,e);
	available_edges--;
	for (uint16_t i = 0; i < n(); i++) {
		if (i != u && i != v) {
			if ((adjacency_matrix[u][i] == Entry::mini ||
					adjacency_matrix[u][i] == Entry::maxi) &&
					adjacency_matrix[v][i] == Entry::empty) {
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
}

bool Triangle_Free_Graph::is_valid(uint16_t u, uint16_t v, Entry e) {
	(void) e;
	for (uint16_t i = 0; i < n(); i++) {
		if (adjacency_matrix[u][i] != Entry::empty &&
				adjacency_matrix[v][i] != Entry::empty) {
			return false; // Triangle u,v,i
		}
	}
	return true;
}

bool Triangle_Free_Graph::saturated(void) {
	return available_edges == 0;
}
