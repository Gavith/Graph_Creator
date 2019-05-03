#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	Graph g = Graph();
	g.addNode("Test");
	g.addNode("Test2");
	g.addConnection("Test", "Test2", 20);
	g.addConnection("Test2", "Test", 30);
	
	g.printNodes();
	g.printConnections("Test");
}
