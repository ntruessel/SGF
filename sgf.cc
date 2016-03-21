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

static uint32_t play(uint16_t n, Player first_player) {
	Graph *g(new Triangle_Free_Graph(n));
	Strategy *mini(new External_Strategy("mini", n, first_player));
	Strategy *maxi(new External_Strategy("maxi", n, first_player));

	uint32_t result = 1;
	Strategy *current_player = first_player == Player::mini ? mini : maxi;
	pair<uint16_t, uint16_t> last_move = current_player->next_move();
	g->set(last_move.first, last_move.second,
			current_player == mini ? Entry::mini : Entry::maxi);

	while(!g->saturated()) {
		current_player = current_player == mini ? maxi : mini;
		current_player->announce(last_move.first, last_move.second);
		last_move = current_player->next_move();
		g->set(last_move.first, last_move.second,
				current_player == mini ? Entry::mini : Entry::maxi);
		result++;
	}

	delete maxi;
	delete mini;
	delete g;

	return result;
}

int main(void) {
	cout << play(3, Player::mini) << endl;
	return 0;
}
