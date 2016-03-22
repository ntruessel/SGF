#pragma once

#include <cstdio>
#include "strategy.hh"

class External_Strategy : public Strategy {
	private:
		int fdi[2];
		int fdo[2];
		FILE *streami, *streamo;
	public:
		External_Strategy(char const *program, Player us,
				uint16_t n, Player first_player);
		virtual void announce(uint16_t u, uint16_t v);
		virtual std::pair<uint16_t, uint16_t> next_move(void);
		virtual ~External_Strategy(void);
};
