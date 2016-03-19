#pragma once

#include <utility>
#include <inttypes.h>

class Strategy {
	public:
		virtual void announce(uint16_t u, uint16_t v) = 0;
		virtual std::pair<uint16_t, uint16_t> next_move(void) = 0;
		virtual ~Strategy(void) { };
};
