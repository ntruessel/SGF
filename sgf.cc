#include <iostream>
#include <cinttypes>
#include <cstring>
#include <vector>
#include <memory>

#include <getopt.h>
#include <unistd.h>
#include <sys/socket.h>

#include "graph.hh"
#include "triangle_free_graph.hh"
#include "strategy.hh"
#include "external_strategy.hh"

using namespace std;

static struct Config {
	char *mini_program_name = NULL;
	char *maxi_program_name = NULL;
} conf;

static uint32_t play(uint16_t n, Player first_player) {
	Graph *g(new Triangle_Free_Graph(n));
	Strategy *mini, *maxi;
	if (conf.mini_program_name != NULL) {
		mini = (new External_Strategy(conf.mini_program_name, Player::mini, n, first_player));
	} else {
		mini = (new External_Strategy("mini", Player::mini, n, first_player));
	}
	if (conf.maxi_program_name != NULL) {
		maxi = (new External_Strategy(conf.maxi_program_name, Player::maxi, n, first_player));
	} else {
		maxi = (new External_Strategy("maxi", Player::maxi, n, first_player));
	}

	uint32_t result = 1;
	Strategy *current_player = first_player == Player::mini ? mini : maxi;
	uint16_t u, v;
	tie(u, v) = current_player->next_move();
	if (!g->is_valid(u, v,
				current_player == mini ? Entry::mini : Entry::maxi)) {
		cerr << "Invalid move from ";
		cerr << (current_player == mini ? "mini" : "maxi");
		cerr << endl;
		return 1;
	}
	g->set(u, v, current_player == mini ? Entry::mini : Entry::maxi);

	while(!g->saturated()) {
		current_player = current_player == mini ? maxi : mini;
		current_player->announce(u, v);
		tie(u,v) = current_player->next_move();
		if (!g->is_valid(u, v,
					current_player == mini ? Entry::mini : Entry::maxi)) {
			cerr << "Invalid move from ";
			cerr << (current_player == mini ? "mini" : "maxi");
			cerr << endl;
			return 1;
		}
		g->set(u, v, current_player == mini ? Entry::mini : Entry::maxi);
		result++;
	}
	current_player = current_player == mini ? maxi : mini;
	current_player->announce(u, v);

	delete maxi;
	delete mini;
	delete g;

	return result;
}

int main(int argc, char *argv[]) {
	while (true) {
		static struct option options[] =
		{
			{ "mini", required_argument, 0, 0},
			{ "maxi", required_argument, 0, 1},
			{0, 0, 0, 0}
		};
		int c;
		int getopt_index = 0;
		c = getopt_long (argc, argv, "", options, &getopt_index);
		if (c == -1) {
			break;
		}
		switch(c) {
			case 0:
				conf.mini_program_name = strdup(optarg);
				break;
			case 1:
				conf.maxi_program_name = strdup(optarg);
				break;
		}
	}
	cout << "# n	edges played" << endl;
	for (uint16_t n : {10, 20, 50, 100, 200, 500, 1000}) {
		cout << n << "	" << play(n, Player::mini) << endl;
	}
	return 0;
}
