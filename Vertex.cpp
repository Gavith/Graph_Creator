#include "Vertex.h"
#include <iostream>

using namespace std;

Vertex::Vertex()
{
}

Vertex::Vertex(const char * name)
{
	this->name = new char[(int)strlen(name) + 1];
	strcpy(this->name, name);
}


Vertex::~Vertex()
{
	connections.clear();
}

void Vertex::setName(const char * name)
{
	if (this->name) delete this->name;
	this->name = new char[(int)strlen(name) + 1];
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

void Vertex::addConnection(Vertex * next, int weight)
{
	Edge* newEdge = new Edge(next);
	newEdge->weight = weight;
	connections.push_back(newEdge);
}

void Vertex::removeConnection(Vertex * next)
{
	for (auto i = connections.begin(); i != connections.end(); i++) {
		if ((*i)->next == next) {
			connections.erase(i);
		}
	}
}

void Vertex::printConnections()
{
	for (auto i = connections.begin(); i != connections.end(); i++) {
		cout << (*i)->next->getName() << " " << (*i)->weight << endl;
	}
}
