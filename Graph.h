#pragma once
#include "Vertex.h"
#include <iostream>

class Graph
{
public:
	Graph();
	~Graph();
	void addNode(const char* name);
	void addNode(const char* name, int x, int y);
	bool addConnection(const char* name1, const char* name2, int weight);
	bool addConnection(Vertex* vert1, Vertex* vert2, int weight);
	bool findNode(const char* name);
	bool findNode(Vertex* node);
	Vertex* getNode(const char* name);
	

	void printNodes();
	void printConnections(const char* name);

private:
	vector<Vertex*> nodes;
	
};

