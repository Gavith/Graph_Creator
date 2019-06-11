#include "Vertex.h"
#include "Map.h"
#include <iostream>
constexpr auto INF = -1; //using -1 as infinity as a placeholder;;

struct pathNode {
	pathNode* parent;
	vector<pathNode*> nexts;

	Vertex* data;
	int length;

	pathNode() {
		parent = nullptr;
		nexts = vector<pathNode*>();

		data = nullptr;
	}

	pathNode(Vertex* h) {
		parent = nullptr;
		nexts = vector<pathNode*>();

		data = h;
	}
};

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
	bool findConnection(Vertex* vert1, Vertex* vert2);
	bool findConnection(const char* vert1, const char* vert2);
	Vertex* getNode(const char* name);
	
	void removeNode(const char* name);
	void removeNode(Vertex* v);
	void removeConnection(const char* name1, const char* name2);
	void removeConnection(Vertex* v1, Vertex* v2);
	
	void getShortestPath(const char* first, const char* last);
	
	void printNodes();
	void printConnections(const char* name);

private:
	vector<Vertex*> nodes;
	vector<Vertex*> dijkstra(vector<Vertex*> graph, Vertex* source, Vertex * last);

	pathNode* getTree(Map<Vertex*, int> dist, pathNode* source);
	pathNode* find(pathNode* head, Vertex* f);
};

