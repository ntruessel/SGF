#include "graph.hh"

using namespace std;

Graph::Graph(uint16_t n)
	: adjacency_matrix(n, vector<Entry>(n, Entry::empty)) {}

uint16_t Graph::n(void) {
	return adjacency_matrix.size();
}

void Graph::set(uint16_t u, uint16_t v, Entry e) {
	if (u < n() && v < n() && (e == Entry::empty || is_valid(u,v,e))) {
		adjacency_matrix[u][v] = e;
		adjacency_matrix[v][u] = e;
	}
}

Entry Graph::get(uint16_t u, uint16_t v) {
	if (u < n() && v < n()) {
		return adjacency_matrix[u][v];
	}
	return adjacency_matrix[0][0];
}

Graph::~Graph(void) {}
