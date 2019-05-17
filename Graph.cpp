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

void Graph::addNode(const char * name, int x, int y)//prob will never get used
{
	Vertex* v = new Vertex(name);
	v->x = x;
	v->y = y;
	nodes.push_back(v);
}

bool Graph::addConnection(const char * name1, const char * name2, int weight)
{
	if (findNode(name1) && findNode(name2)) {//if both nodes exist
		getNode(name1)->addConnection(getNode(name2), weight);//add it
		return true;
	}
	return false;
}

bool Graph::addConnection(Vertex * vert1, Vertex * vert2, int weight)//same as above
{
	if (findNode(vert1) && findNode(vert2)) {
		vert1->addConnection(vert2, weight);
		return true;
	}
	return false;
}

bool Graph::findNode(const char * name)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {//check every node
		if (strcmp((*i)->getName(), name) == 0) {//if it exists
			return true;//return
		}
	}
	return false;
}

bool Graph::findNode(Vertex * node)//same as above
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
	for (auto i = nodes.begin(); i != nodes.end(); i++) {//find the ndoe
		if (*i == vert1) {
			return vert1->findConnection(vert2);//have the vertex do the check
		}
	}
	return false;
}

bool Graph::findConnection(const char * vert1, const char * vert2)//same as above
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
	for (auto i = nodes.begin(); i != nodes.end(); i++) {//find it
		if (strcmp((*i)->getName(), name) == 0) {//return the ndoe
			return *i;
		}
	}
	return nullptr;
}

void Graph::removeNode(const char * name)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {//finds it
		if (strcmp((*i)->getName(), name) == 0) {
			delete *i;//makes sure nothing breaks
			nodes.erase(i);
			break;
		}
	}
}

void Graph::removeNode(Vertex * v)//same as above
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if ((*i) == v) { 
			delete *i;
			nodes.erase(i);
			break;
		}
	}
}

void Graph::removeConnection(const char * name1, const char * name2)
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {//find the first node
		if (strcmp((*i)->getName(), name1) == 0) {
			getNode(name1)->removeConnection(getNode(name2));//have teh vertex do the rest of the work
			break;
		}
	}
}

void Graph::removeConnection(Vertex * v1, Vertex * v2)//same as above
{
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if ((*i) == v1) {
			v1->removeConnection(v2);
			break;
		}
	}
}

void Graph::getShortestPath(const char* first, const char* last)
{
	if (findNode(first) && findNode(last)) {//if they both exist
		vector<Vertex*> path = dijkstra(nodes, getNode(first), getNode(last));//the algorithm
		if (path.empty()) {//if there are no nodes
			cout << "There is no path between the nodes given." << endl;
		}
		else {
			int length = 0;
			cout << "Your path is :";
			for (int i = 0; i < path.size(); i++) {//display path
				cout << path.at(i)->getName() << " ";
				if (i < path.size() - 1) {//calculate path length
					vector<Edge*> temp = path.at(i)->getConnections();
					for (auto j = temp.begin(); j != temp.end(); j++) {//find the right connection
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
	Q.push_back(source);
	for (auto i = graph.begin(); i != graph.end(); i++) {//set all lengths to infinity
		if ((*i) != source) {
			dist.put(*i, INF);
			Q.push_back(*i);
		}
		//add it to the lsit
	}

	while (!Q.empty()) {//while there are still nodes
		Vertex* min = *(Q.begin());
		for (auto i = Q.begin(); dist.get(min) == -1 && i != Q.end(); i++) {
			min = *i;
		}
		
		for (auto i = Q.begin(); i != Q.end(); i++)//find min
			if (dist.get(*i) < dist.get(min) && dist.get(*i) != INF)
				min = *i;

		for (auto i = Q.begin(); i != Q.end(); i++)//remove the min Q
			if ((*i) == min) {
				Q.erase(i);
				break;
			}
		vector<Edge*> temp = min->getConnections();

		for (auto i = temp.begin(); i != temp.end(); i++) {//go through connections
			//if the new length from the node we are on is less that the one there previously, relpace it
			int alt = dist.get(min) + (*i)->weight;
			if (alt < dist.get((*i)->next) || dist.get((*i)->next) == INF) {
				dist.set((*i)->next, alt);
			}
		}

	}
	//I have dist, so now I go through dist and find the node

	pathNode* head = new pathNode(source);
	head->length = 0;

	//find tree foreward
	head = getTree(dist, head);
	pathNode* l = find(head, last);

	vector<Vertex*> path = vector<Vertex*>();
	while (l != nullptr) {//work backwards
		path.insert(path.begin(), l->data);
		l = l->parent;
	}
	return path;
}

pathNode * Graph::getTree(Map<Vertex*, int> dist, pathNode * source)
{
	//get dist
	int d = dist.get(source->data);
	Vertex* v = source->data;

	vector<Edge*> temp = v->getConnections();

	for (auto i = temp.begin(); i != temp.end(); i++) {//find the rigt connection
		if (dist.get((*i)->next) - d == (*i)->weight) {//if the connection has the correct dist addition
			pathNode * n = new pathNode((*i)->next);//add it to the tree
			n->parent = source;
			source->nexts.push_back(n);
			getTree(dist, n);//recurse
		}
	}


	return source;
}

pathNode * Graph::find(pathNode * head, Vertex * f)//finds in tree
{
	if (head->data == f) {
		return head;
	}
	else {
		vector<pathNode*> temp = head->nexts;
		for (auto i = temp.begin(); i != temp.end(); i++) {//for every
			pathNode* t = find(*i, f);//recurse
			if (t != nullptr) {//if we found it
				return t;
			}
		}
	}
	return nullptr;
	
}





void Graph::printNodes()
{
	cout << endl;
	for (auto i = nodes.begin(); i != nodes.end(); i++) {//for every
		cout << (*i)->getName() << endl;//print
	}
	cout << endl;
}

void Graph::printConnections(const char * name)
{
	getNode(name)->printConnections();//go to vertex
}
