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
	for (auto i = connections.begin(); i != connections.end(); i++) {//finds it
		if ((*i)->next == connected) {
			connections.erase(i);//erases and returns so it doesnt iterate past
			return true;
		}
	}
	return false;
}

bool Vertex::removeEdge(char * connected)//same as previous
{
	for (auto i = connections.begin(); i != connections.end(); i++) {
		if (strcmp((*i)->next->getName(), connected) == 0) {
			connections.erase(i);
			return true;
		}
	}
	return false;
}

void Vertex::addConnection(Vertex * next, int weight)//pushes to vector
{
	Edge* newEdge = new Edge(next);
	newEdge->weight = weight;
	connections.push_back(newEdge);
}

void Vertex::removeConnection(Vertex * next)
{
	for (auto i = connections.begin(); i != connections.end(); i++) {//finds it
		if ((*i)->next == next) {
			delete *i;//makes sure nothing breaks
			connections.erase(i);
			break;
		}
	}
}

bool Vertex::findConnection(Vertex * vert)
{
	for (auto i = connections.begin(); i != connections.end(); i++) {//basic check and sees if its there
		if ((*i)->next == vert) {
			return true;
		}
	}
	return false;
}

bool Vertex::findConnection(const char * vert)//same as above
{
	for (auto i = connections.begin(); i != connections.end(); i++) {
		if (strcmp((*i)->next->getName(), vert) == 0) {
			return true;
		}
	}
	return false;
}

vector<Edge*> Vertex::getConnections()
{
	return connections;
}

void Vertex::printConnections()
{
	for (auto i = connections.begin(); i != connections.end(); i++) {//a way to see all connections
		cout << "to: " << (*i)->next->getName() << " weight: " << (*i)->weight << endl;
	}
}
