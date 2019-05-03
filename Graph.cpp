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

bool Graph::addConnection(const char * name1, const char * name2, int weight)
{
	if (findNode(name1) && findNode(name2)) {
		getNode(name1)->addConnection(getNode(name2), weight);
		return true;
	}
	return false;
}

bool Graph::addConnection(Vertex * vert1, Vertex * vert2, int weight)
{
	if (findNode(vert1) && findNode(vert2)) {
		vert1->addConnection(vert2, weight);
		return true;
	}
	return false;
}

bool Graph::findNode(const char * name)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (strcmp((*i)->getName(), name) == 0) {
			return true;
		}
	}
	return false;
}

bool Graph::findNode(Vertex * node)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (*i == node) {
			return true;
		}
	}
	return false;
}

Vertex * Graph::getNode(const char * name)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (strcmp((*i)->getName(), name) == 0) {
			return *i;
		}
	}
	return nullptr;
}

void Graph::removeNode(const char * name)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (strcmp((*i)->getName, name) == 0) {
			nodes.erase(i);
		}
	}
}

void Graph::removeNode(Vertex * v)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if ((*i) == v) { 
			nodes.erase(i);
		}
	}
}

void Graph::removeConnection(const char * name1, const char * name2)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (strcmp((*i)->getName, name1) == 0) {
			getNode(name1)->removeConnection(getNode(name2));
		}
	}
}

void Graph::removeConnection(Vertex * v1, Vertex * v2)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if ((*i) == v1) {
			v1->removeConnection(v2);
		}
	}
}

void Graph::printNodes()
{
	cout << endl;
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		cout << (*i)->getName() << endl;
	}
	cout << endl;
}

void Graph::printConnections(const char * name)
{
	getNode(name)->printConnections();
}
