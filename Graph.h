#pragma once


#include<bits/stdc++.h>
#include "Edge.h"
#include "Node.h"
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
        Node getNode(int tag);
        list<Node> getNeighbors(Node node);
        vector<Node> getNodesByPoint(double x , double y);
        vector<Node> getNodesByArea(double x , double y , int radio );
        ~Graph();

    
};