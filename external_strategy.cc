#include "external_strategy.hh"

#include <cstdlib>
#include <iostream>

#include <sys/socket.h>
#include <unistd.h>

#define EXTERNAL_FD 1
#define INTERNAL_FD 0

External_Strategy::External_Strategy(char const *program,
		uint16_t n, Player first_player) {
	socketpair(AF_UNIX, SOCK_STREAM, 0, fd);

	if (0 == fork()) {
		close(fd[INTERNAL_FD]);
		dup2(fd[EXTERNAL_FD], STDIN_FILENO);
		dup2(fd[EXTERNAL_FD], STDOUT_FILENO);
		close(fd[EXTERNAL_FD]);
		execl(program, program, (char *) NULL);
		abort();
	}

	close(fd[EXTERNAL_FD]);
	stream = fdopen(fd[INTERNAL_FD], "r+");

	fprintf(stream, "%" PRIu16 " %" PRIu8 "\n",
			n, (first_player == Player::mini ? 0 : 1));
	fflush(stream);
}

void External_Strategy::announce(uint16_t u, uint16_t v) {
	fprintf(stream, "%" PRIu16 " %" PRIu8 "\n", u, v);
}

std::pair<uint16_t, uint16_t> External_Strategy::next_move(void) {
	uint16_t u, v;
	fscanf(stream, "%" SCNu16 " %" SCNu16, &u, &v);
	return std::pair<uint16_t, uint16_t>(u,v);
}

External_Strategy::~External_Strategy(void) {
	fclose(stream);
	close(fd[INTERNAL_FD]);
}
