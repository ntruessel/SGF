#include <iostream>
#include <cinttypes>
#include <vector>

#include <unistd.h>
#include <sys/socket.h>

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
		if ((u >= n) || (v >= n) || (u == v)) {
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
	int minifd[2];
	int maxifd[2];
	socketpair(AF_UNIX, SOCK_STREAM, 0, maxifd);
	socketpair(AF_UNIX, SOCK_STREAM, 0, minifd);

	if (0 == fork()) {
		close(minifd[0]);
		dup2(minifd[1], STDIN_FILENO);
		dup2(minifd[1], STDOUT_FILENO);
		close(minifd[1]);
		execl("mini", "mini", (char *) NULL);
	}
	close(minifd[1]);
	FILE *mini = fdopen(minifd[0], "r+");

	if (0 == fork()) {
		close(maxifd[0]);
		dup2(maxifd[1], STDIN_FILENO);
		dup2(maxifd[1], STDOUT_FILENO);
		close(maxifd[1]);
		execl("maxi", "maxi", (char *) NULL);
	}
	close(maxifd[1]);
	FILE *maxi = fdopen(maxifd[0], "r+");

	Graph g(3,0);
	fprintf(maxi, "%" PRIu16 " %" PRIu8 "\n", g.n, g.turn);
	fprintf(mini, "%" PRIu16 " %" PRIu8 "\n", g.n, g.turn);

	FILE *in;
	FILE *out;

	while(g.available_edges > 0) {
		if (g.turn == 0) {
			in = mini;
			out = maxi;
		} else {
			in = maxi;
			out = mini;
		}

		uint16_t u, v;
		if (fscanf(in, "%" SCNu16 " %" SCNu16, &u, &v) < 2) {
			cerr << "Incomplete input" << endl;
			exit(1);
		}
		fprintf(out, "%" PRIu16 " %" PRIu8 "\n", u, v);
		g.set(u,v);
	}
	return 0;
}
