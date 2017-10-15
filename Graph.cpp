#include "Graph.h"
#include "Node.h"
#include "Edge.h"

#include<bits/stdc++.h>
#include <list>

using namespace std;


Graph::Graph(vector<Node> nodes){
            this->numberNodes = nodes.size();
            this->nodes = nodes;
            adjacenseList = new list<pair<Node *,double>> [numberNodes];
        }  
        // function to add an edge to graph
void Graph::addEdge(Edge edge){
    adjacenseList[edge.start->tag].push_back(make_pair(edge.end, edge.weight));
    adjacenseList[edge.end->tag].push_back(make_pair(edge.start, edge.weight));
    this->edges.push_back(edge);
}

void Graph::printGraph(){
	for (int i = 0; i < this->numberNodes; i++){
		for (auto p=adjacenseList[i].begin(); p!=adjacenseList[i].end(); p++){
			cout << "(" << i << "," << p->first->tag << "," << p->second << ") ";
		}
		cout << endl ;
	}
}

list<Node> Graph::getSuccessors(Node node){
	list<Node> successors ;
	for (auto p=adjacenseList[node.tag].begin(); p!=adjacenseList[node.tag].end(); p++){	
		successors.push_back(*p->first);
	}
	return successors;
}


Graph::~Graph(){}