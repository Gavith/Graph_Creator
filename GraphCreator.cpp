#include <iostream>
#include <cstring>
#include "Graph.h"

using namespace std;

int main()
{
	Graph g = Graph();
	char* input = new char[10];
	while (input[0] != 'q') {
		cout << "1) add" << endl
			<< "2) remove" << endl
			<< "3) shortest" << endl
			<< "4) print" << endl
			<< "5) quit" << endl;
		cin.get(input, 10);
		cin.ignore(1000, '\n');
		if (strcmp(input, "add") == 0) {//adding
			cout << "edge or vertex? ";//To check what they want
			cin.get(input, 10);
			cin.ignore(1000, '\n');
			if (input[0] == 'v') {
				cout << "Vertex name? ";
				cin.get(input, 10);
				cin.ignore(1000, '\n');
				g.addNode(input);
			}
			else if (input[0] == 'e') {
				char* in1 = new char[10];
				int weight;
				cout << "Vertex 1? " ;
				cin.get(in1, 10);
				cin.ignore(1000, '\n');
				cout << "Vertex 2? ";
				cin.get(input, 10);
				cin.ignore(1000, '\n');
				cout << "Weight? ";
				cin >> weight;
				cin.ignore(1000, '\n');
				g.addConnection(in1, input, weight);
				delete[] in1;
			}
		} 
		else if (strcmp(input, "remove") == 0) { //Removal
			cout << "edge or vertex? ";//To check what they want
			cin.get(input, 10);
			cin.ignore(1000, '\n');
			if (input[0] == 'v') {
				cout << "Vertex name? ";
				cin.get(input, 10);
				cin.ignore(1000, '\n');
				if (g.findNode(input)) {
					g.removeNode(input);
				}
				else {
					cout << "That node does not exist" << endl;
				}
			}
			else if (input[0] == 'e') {
				char* in1 = new char[10];
				cout << "Vertex 1? ";
				cin.get(in1, 10);
				cin.ignore(1000, '\n');
				cout << "Vertex 2? ";
				cin.get(input, 10);
				cin.ignore(1000, '\n');
				if (g.findConnection(in1, input)) {
					g.removeConnection(in1, input);
				}
				else {
					cout << "The connection does not exist." << endl;
				}
			}
		}
		else if (strcmp(input, "shortest") == 0) {//shortest
			char* in1 = new char[10];
			cout << "What is the node you want to start from?" << endl;
			cin.get(input, 10);
			cin.ignore(1000, '\n');
			cout << "What is the node you want get to?" << endl;
			cin.get(in1, 10);
			cin.ignore(1000, '\n');
			g.getShortestPath(input, in1);

		}
		else if (strcmp(input, "print") == 0) {
			cout << "Nodes: " << endl;
			g.printNodes();
			cout << endl << "What is the name of the node that you want to see the connections for? " << endl;
			cin.get(input, 10);
			cin.ignore(1000, '\n');
			if (g.findNode(input)) {
				g.printConnections(input);
			}
			else {
				cout << "That node does not exist in the graph" << endl;
			}
		}
	}

	/*
	g.addNode("Test");
	g.addNode("Test2");
	g.addNode("Test3");
	g.addNode("Test4");
	//g.addConnection("Test", "Test2", 12);
	g.addConnection("Test", "Test3", 2);
	g.addConnection("Test3", "Test4", 4);
	g.addConnection("Test2", "Test4", 1);
	//g.addConnection("Test3", "Test2", 8);
	
	g.getShortestPath("Test", "Test2");
	*/
}
