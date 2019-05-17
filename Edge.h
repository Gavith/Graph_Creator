#pragma once
//Nothing fancy in this class, just data management
class Vertex;

class Edge
{
public:
	Edge();
	Edge(int weight);
	Edge(Vertex* next);
	Edge(Vertex* next, int weight);
	~Edge();
	
	int weight;

	Vertex* next;

};
