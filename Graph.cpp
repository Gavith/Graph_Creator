#include "Graph.h"





Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::addNode(const char * name)
{
	Vertex* v = new Vertex(name);
	nodes.push_back(v);
}

void Graph::addNode(const char * name, int x, int y)
{
	Vertex* v = new Vertex(name);
	v->x = x;
	v->y = y;
	nodes.push_back(v);
}

bool Graph::addConnection(const char * name1, const char * name2, int weight)
{
	if (findNode(name1) && findNode(name2)) {
		getNode(name1)->addConnection(getNode(name2), weight);
		return true;
	}
	return false;
}

bool Graph::addConnection(Vertex * vert1, Vertex * vert2, int weight)
{
	if (findNode(vert1) && findNode(vert2)) {
		vert1->addConnection(vert2, weight);
		return true;
	}
	return false;
}

bool Graph::findNode(const char * name)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (strcmp((*i)->getName(), name) == 0) {
			return true;
		}
	}
	return false;
}

bool Graph::findNode(Vertex * node)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (*i == node) {
			return true;
		}
	}
	return false;
}

bool Graph::findConnection(Vertex * vert1, Vertex * vert2)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (*i == vert1) {
			return vert1->findConnection(vert2);
		}
	}
	return false;
}

bool Graph::findConnection(const char * vert1, const char * vert2)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (strcmp((*i)->getName() ,vert1) == 0) {
			return getNode(vert1)->findConnection(vert2);
		}
	}
	return false;
}

Vertex * Graph::getNode(const char * name)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (strcmp((*i)->getName(), name) == 0) {
			return *i;
		}
	}
	return nullptr;
}

void Graph::removeNode(const char * name)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (strcmp((*i)->getName(), name) == 0) {
			delete *i;
			nodes.erase(i);
		}
	}
}

void Graph::removeNode(Vertex * v)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if ((*i) == v) { 
			delete *i;
			nodes.erase(i);
		}
	}
}

void Graph::removeConnection(const char * name1, const char * name2)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (strcmp((*i)->getName(), name1) == 0) {
			getNode(name1)->removeConnection(getNode(name2));
		}
	}
}

void Graph::removeConnection(Vertex * v1, Vertex * v2)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if ((*i) == v1) {
			v1->removeConnection(v2);
		}
	}
}

void Graph::getShortestPath(const char* first, const char* last)
{
	if (findNode(first) && findNode(last)) {
		vector<Vertex*> path = dijkstra(nodes, getNode(first), getNode(last));
		if (path.empty()) {
			cout << "There is no path between the nodes given." << endl;
		}
		else {
			int length = 0;
			cout << "Your path is :";
			for (int i = 0; i < path.size(); i++) {
				cout << path.at(i)->getName() << " ";
				if (i < path.size() - 1) {
					vector<Edge*> temp = path.at(i)->getConnections();
					for (auto j = temp.begin(); j != temp.end(); j++) {
						if ((*j)->next == path.at(i + 1)) {
							length += (*j)->weight;
						}
					}
				}
			}

			cout << endl << "With length: " << length << endl;
		}
	}
	else {
		cout << "One of the nodes does not exist." << endl;
	}
	
}



vector<Vertex*> Graph::dijkstra(vector<Vertex*> graph, Vertex * source, Vertex * last)
{
	vector<Vertex*> Q;
	Map<Vertex*, int> dist;//all nodes

	
	
	dist.put(source, 0);
	for (auto i = graph.begin(); i != graph.end(); i++) {
		if ((*i) != source) {
			dist.put(*i, INF);
		}
		Q.push_back(*i);
	}

	while (!Q.empty()) {
		Vertex* min = *(Q.begin());
		for (auto i = Q.begin(); i != Q.end(); i++)
			if (dist.get(*i) < dist.get(min) && dist.get(*i) != INF)
				min = *i;

		for (auto i = Q.begin(); i != Q.end(); i++)
			if ((*i) == min) {
				Q.erase(i);
				break;
			}
		vector<Edge*> temp = min->getConnections();

		for (auto i = temp.begin(); i != temp.end(); i++) {
			int alt = dist.get(min) + (*i)->weight;
			if (alt < dist.get((*i)->next) || dist.get((*i)->next) == INF) {
				dist.set((*i)->next, alt);
			}
		}

	}
	//I have dist, so now I go through dist and find the node

	pathNode* head = new pathNode(source);
	head->length = 0;


	head = getTree(dist, head);
	pathNode* l = find(head, last);

	vector<Vertex*> path = vector<Vertex*>();
	while (l != nullptr) {
		path.insert(path.begin(), l->data);
		l = l->parent;
	}
	return path;
}

pathNode * Graph::getTree(Map<Vertex*, int> dist, pathNode * source)
{
	int d = dist.get(source->data);
	Vertex* v = source->data;

	vector<Edge*> temp = v->getConnections();

	for (auto i = temp.begin(); i != temp.end(); i++) {
		if (dist.get((*i)->next) - d == (*i)->weight) {
			pathNode * n = new pathNode((*i)->next);
			n->parent = source;
			source->nexts.push_back(n);
			getTree(dist, n);
		}
	}


	return source;
}

pathNode * Graph::find(pathNode * head, Vertex * f)
{
	if (head->data == f) {
		return head;
	}
	else {
		vector<pathNode*> temp = head->nexts;
		for (auto i = temp.begin(); i != temp.end(); i++) {
			pathNode* t = find(*i, f);
			if (t != nullptr) {
				return t;
			}
		}
	}
	return nullptr;
	
}





void Graph::printNodes()
{
	cout << endl;
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		cout << (*i)->getName() << endl;
	}
	cout << endl;
}

void Graph::printConnections(const char * name)
{
	getNode(name)->printConnections();
}
