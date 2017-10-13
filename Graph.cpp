#include "Graph.h"
#include "Node.h"
#include "Edge.h"

#include<bits/stdc++.h>
#include <list>

using namespace std;


Graph::Graph(int numberNodes){
            this->numberNodes = numberNodes;
            adj = new list<pair<Node *,double>> [numberNodes];
        }  
        // function to add an edge to graph
void Graph::addEdge(Edge edge){

    adj[edge.start->tag].push_back(make_pair(edge.start, edge.weight));
    adj[edge.end->tag].push_back(make_pair(edge.end, edge.weight));
}

Graph::~Graph(){};