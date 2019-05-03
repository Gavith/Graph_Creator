#include "Edge.h"

Edge::Edge()
{

}

Edge::Edge(int weight)
{
	this->weight = weight;
}

Edge::Edge(Vertex * next)
{
	this->next = next;
}

Edge::Edge(Vertex * next, int weight)
{
	this->next = next;
	this->weight = weight;
}


Edge::~Edge()
{

}
