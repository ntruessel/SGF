#include <iostream>
#include <cinttypes>
#include <vector>

using namespace std;

struct Graph {
	uint16_t n;
	vector<vector<uint8_t>> graph;
	uint64_t available_edges;
	uint8_t turn;

	Graph(uint16_t n, uint8_t turn):
		n(n),
		graph(vector<vector<uint8_t>>(n,vector<uint8_t>(n,0))),
		available_edges(n * (n - 1) / 2),
		turn(turn) {}

	bool valid(uint16_t u, uint16_t v) {
		if (u == v) {
			return false;
		}

		if (graph[u][v] != 0 && graph[v][u] != 0) {
			return false;
		}

		for (uint16_t i = 0; i < n; i++) {
			if (graph[u][i] != 0 && graph[v][i] != 0) {
				return false;
			}
		}

		return true;
	}

	uint64_t new_dead_edges(uint16_t u, uint16_t v) {
		uint64_t result = 1;
		for (uint16_t i = 0; i < n; i++) {
			if ((i != u && i != v) &&
					(graph[u][i] != 0 || graph[v][i] != 0)) {
				result++;
			}
		}
		return result;
	}

	void set(uint16_t u, uint16_t v) {
		if (!valid(u,v)) {
			cout << "Invalid input" << endl;
			exit(1);
		}

		graph[u][v] = turn + 1;
		graph[v][u] = turn + 1;

		available_edges -= new_dead_edges(u,v);

		turn = 1 - turn;
	}
};

int main(void) {
	ios::sync_with_stdio(false);

	Graph g(3,0);
	cout << g.n << " " << static_cast<uint16_t>(g.turn) << endl;
	while(g.available_edges > 0) {
		uint16_t u, v;
		cin >> u >> v;
		g.set(u,v);
	}
	return 0;
}
