#pragma once


#include<bits/stdc++.h>
#include "Edge.h"
#include <list>

using namespace std;

class Graph
{
    public : 
    	int numberNodes; 
        list<pair<Node *,double>> *adjacenseList;

    public:
        Graph(int numberNodes);
        void addEdge(Edge edge);
        void printGraph();
        list<Node> getSuccessors(Node node);
        ~Graph();

    
};