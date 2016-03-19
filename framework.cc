#include <iostream>
#include <cinttypes>
#include <vector>
#include <memory>

#include <unistd.h>
#include <sys/socket.h>

#include "graph.hh"
#include "triangle_free_graph.hh"
#include "strategy.hh"
#include "external_strategy.hh"

using namespace std;

int main(void) {
	Graph *g(new Triangle_Free_Graph(3));
	Player p = Player::mini;

	Strategy *mini(new External_Strategy("mini", g->n(), p));
	Strategy *maxi(new External_Strategy("maxi", g->n(), p));

	Strategy *in, *out;
	while(!g->saturated()) {
		if (p == Player::mini) {
			in = mini;
			out = maxi;
		} else {
			in = maxi;
			out = mini;
		}
		pair<uint16_t, uint16_t> move = in->next_move();
		out->announce(move.first, move.second);
		g->set(move.first, move.second,
				(p == Player::mini ? Entry::mini : Entry::maxi));
		p = (p == Player::mini ? Player::maxi : Player::mini);
	}
	delete maxi;
	delete mini;
	delete g;
	return 0;
}
