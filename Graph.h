#pragma once
#include "Vertex.h"
class Graph
{
public:
	Graph();
	~Graph();
	void addNode(const char* name);
	void addNode(const char* name, int x, int y);
	bool addConnection(const char* name1, const char* name2);
	bool addConnection(Vertex* vert1, Vertex* vert2);
	bool findNode(Vertex* node);

private:
	vector<Vertex*> nodes;
};

