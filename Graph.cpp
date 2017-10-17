#include "Graph.h"
#include "Node.h"
#include "Edge.h"

#include<bits/stdc++.h>
#include <list>

using namespace std;


Graph::Graph(vector<Node> nodes,vector<Edge> edges){
    this->numberNodes = nodes.size();
    this->nodes = nodes;
    this->edges = edges;
    adjacenseList = new list<pair<Node *,double>> [numberNodes];
    for (auto edge=(this->edges).begin(); edge!= (this->edges).end(); edge++) {
	    adjacenseList[edge->start->tag].push_back(make_pair(edge->end, edge->weight));
	    adjacenseList[edge->end->tag].push_back(make_pair(edge->start, edge->weight));
    }
}  
        // function to add an edge to graph
// void Graph::addEdge(Edge edge){
//     for (auto edge=(this->edges).begin(); edge!= (this->edges).end(); edge++) {
// 	    adjacenseList[edge.start->tag].push_back(make_pair(edge.end, edge.weight));
// 	    adjacenseList[edge.end->tag].push_back(make_pair(edge.start, edge.weight));
// 	    this->edges.push_back(edge);
//     }
// }

void Graph::printGraph(){
	for (int i = 0; i < this->numberNodes; i++){
		for (auto p=adjacenseList[i].begin(); p!=adjacenseList[i].end(); p++){
			cout << "(" << i << "," << p->first->tag << "," << p->second << ") ";
		}
		cout << endl ;
	}
}

list<Node> Graph::getNeighbors(Node node){
	list<Node> successors ;
	for (auto p=adjacenseList[node.tag].begin(); p!=adjacenseList[node.tag].end(); p++){	
		successors.push_back(*p->first);
	}
	return successors;
}

vector<Node> Graph::getNodesByPoint(double x , double y){
    double radio = 10 ;
    vector<Node> nearNodes ;
	//cout << x << " " << y << endl;
    for (auto node=(this->nodes).begin(); node!= (this->nodes).end(); node++) {
    	if( (node->x > x-radio and node->x < x+radio) 
			and (node->y > y-radio and node->y < y+radio) ){
			nearNodes.push_back(*node);
		}
    }
    return nearNodes;
}


Graph::~Graph(){}