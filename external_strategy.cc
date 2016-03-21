#include "external_strategy.hh"

#include <cstdlib>
#include <iostream>

#include <signal.h>
#include <sys/prctl.h>
#include <unistd.h>

#define WRITE_FD 1
#define READ_FD 0

External_Strategy::External_Strategy(char const *program,
		uint16_t n, Player first_player) {
	pipe(fdi);
	pipe(fdo);

	if (0 == fork()) {
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		close(fdi[READ_FD]);
		close(fdo[WRITE_FD]);
		dup2(fdi[WRITE_FD], STDOUT_FILENO);
		dup2(fdo[READ_FD], STDIN_FILENO);
		close(fdi[WRITE_FD]);
		close(fdo[READ_FD]);
		execl(program, program, (char *) NULL);
		abort();
	}

	close(fdi[WRITE_FD]);
	close(fdo[READ_FD]);
	streami = fdopen(fdi[READ_FD], "r");
	streamo = fdopen(fdo[WRITE_FD], "w");

	fprintf(streamo, "%" PRIu16 " %" PRIu8 "\n",
		n, (first_player == Player::mini ? 0 : 1));
	fflush(streamo);
}

void External_Strategy::announce(uint16_t u, uint16_t v) {
	fprintf(streamo, "%" PRIu16 " %" PRIu16 "\n", u, v);
	fflush(streamo);
}

std::pair<uint16_t, uint16_t> External_Strategy::next_move(void) {
	uint16_t u, v;
	fscanf(streami, "%" SCNu16 " %" SCNu16, &u, &v);
	return std::pair<uint16_t, uint16_t>(u,v);
}

External_Strategy::~External_Strategy(void) {
	fclose(streamo);
	fclose(streami);
	close(fdi[READ_FD]);
	close(fdo[WRITE_FD]);
}
