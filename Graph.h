#pragma once


#include<bits/stdc++.h>
#include "Edge.h"
#include <list>
#include <vector>

using namespace std;

class Graph
{
    public : 
    	int numberNodes; 
    	vector<Edge> edges;
    	vector<Node> nodes;
        list<pair<Node *,double>> *adjacenseList;

    public:
        Graph(vector<Node> nodes,vector<Edge> edges);
        //void addEdge(Edge edge);
        void printGraph();
        vector<Node> getNodes();
        vector<Edge> getEdges();
        list<Node> getSuccessors(Node node);
        vector<Node> getNodesByPoint(double x , double y);
        ~Graph();

    
};