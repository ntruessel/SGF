#pragma once

#include <cstdio>
#include "strategy.hh"

enum class Player {
	maxi,
	mini,
};

class External_Strategy : public Strategy {
	private:
		int fd[2];
		FILE *stream;
	public:
		External_Strategy(char const *program, uint16_t n, Player first_player);
		virtual void announce(uint16_t u, uint16_t v);
		virtual std::pair<uint16_t, uint16_t> next_move(void);
		virtual ~External_Strategy(void);
};
