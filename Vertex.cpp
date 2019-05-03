#include "Vertex.h"



Vertex::Vertex()
{
}

Vertex::Vertex(const char * name)
{
	this->name = new char(strlen(name) + 1);
	strcpy(this->name, name);
}


Vertex::~Vertex()
{
	connections.clear();
}

void Vertex::setName(const char * name)
{
	if (this->name) delete this->name;
	this->name = new char(strlen(name) + 1);
	strcpy(this->name, name);
}

char * Vertex::getName()
{
	return name;
}

bool Vertex::removeEdge(Vertex * connected)
{
	for (auto i = connections.begin(); i != connections.end(); i++) {
		if ((*i)->next == connected) {
			connections.erase(i);
			return true;
		}
	}
	return false;
}

bool Vertex::removeEdge(char * connected)
{
	for (auto i = connections.begin(); i != connections.end(); i++) {
		if (strcmp((*i)->next->getName(), connected) == 0) {
			connections.erase(i);
			return true;
		}
	}
	return false;
}

void Vertex::addConnection(Vertex * next)
{
	Edge* newEdge = new Edge(next);
	connections.push_back(newEdge);
}