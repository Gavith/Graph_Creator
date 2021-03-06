#include "Edge.h"
#include <cstring>
#include <vector>

using namespace std;

class Vertex
{
public:
	Vertex();
	Vertex(const char* name);
	~Vertex();
	//if graphics are ever added
	int x;
	int y;

	void setName(const char* name);
	char* getName();
	bool removeEdge(Vertex* connected);
	bool removeEdge(char* connected);
	void addConnection(Vertex* next, int weight);
	void removeConnection(Vertex* next);
	bool findConnection(Vertex* vert);
	bool findConnection(const char* vert);
	vector<Edge*> getConnections();
	void printConnections();
private:


	char* name;
	vector<Edge*> connections;

};
