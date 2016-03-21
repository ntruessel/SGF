#include "../triangle_free_graph.hh"
#include <cassert>

int main(void) {
	Entry e = Entry::mini;
	Graph *g = new Triangle_Free_Graph(4);

	g->set(0,1,e);
	assert(!g->saturated());
	g->set(0,2,e);
	assert(!g->saturated());
	g->set(0,3,e);
	assert(g->saturated());
	delete g;

	g = new Triangle_Free_Graph(4);
	g->set(0,1,e);
	assert(!g->saturated());
	g->set(1,2,e);
	assert(!g->saturated());
	g->set(2,3,e);
	assert(!g->saturated());
	g->set(3,0,e);
	assert(g->saturated());
	delete g;

	g = new Triangle_Free_Graph(5);
	g->set(0,1,e);
	assert(!g->saturated());
	g->set(1,2,e);
	assert(!g->saturated());
	g->set(2,3,e);
	assert(!g->saturated());
	g->set(3,4,e);
	assert(!g->saturated());
	g->set(4,0,e);
	assert(g->saturated());
	delete g;

	return 0;
}
