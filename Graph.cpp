#include "Graph.h"



Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::addNode(const char * name)
{
	Vertex* v = new Vertex(name);
	nodes.push_back(v);
}

void Graph::addNode(const char * name, int x, int y)
{
	Vertex* v = new Vertex(name);
	v->x = x;
	v->y = y;
	nodes.push_back(v);
}

bool Graph::addConnection(Vertex * vert1, Vertex * vert2)
{
	if (findNode(vert1) && findNode(vert2)) {}
		vert1->addConnection(vert2);
		return true;
	}

}
