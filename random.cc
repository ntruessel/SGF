#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
#include <tuple>

#include "triangle_free_graph.hh"

using namespace std;

static vector<pair<uint16_t, uint16_t>> edges;
static Triangle_Free_Graph *g;

pair<uint16_t, uint16_t> random_edge(void) {
	pair<uint16_t, uint16_t> result = edges.back();
	edges.pop_back();
	return result;
}

void clean_edges(void) {
	if (!edges.empty()) {
		pair<uint16_t, uint16_t> e = edges.back();
		while (!edges.empty() && !g->is_valid(e.first, e.second, Entry::mini)) {
			edges.pop_back();
			e = edges.back();
		}
	}
}

int main(int argc, char *argv[]) {
	srand(time(0));

	uint16_t n, p;
	cin >> n >> p;
	g = new Triangle_Free_Graph(n);
	for (uint16_t i = 0; i < n; i++) {
		for (uint16_t j = i + 1; j < n; j++) {
			edges.emplace_back(i,j);
		}
	}
	random_shuffle(edges.begin(), edges.end(), [](int bound){ return rand() % bound; });

	uint16_t u, v;
	bool we_move = (p == 0 && strcmp(argv[1], "mini") == 0) ||
		(p == 1 && strcmp(argv[1], "maxi") == 0);

	while(!edges.empty()) {
		if (we_move) {
			tie(u,v) = random_edge();
			cout << u << " " << v << endl << flush;
			g->set(u,v,Entry::mini);
			clean_edges();
		} else {
			cin >> u >> v;
			g->set(u,v,Entry::mini);
			clean_edges();
		}
		we_move = !we_move;
	}
	assert(g->saturated());

	delete g;
	return 0;
}
