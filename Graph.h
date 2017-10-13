#pragma once


#include<bits/stdc++.h>
#include "Edge.h"
#include <list>

using namespace std;

class Graph
{
    public:
        Graph(int numberNodes);
        void addEdge(Edge edge);
        ~Graph();

    public : int numberNodes;    // No. of vertices
        // In a weighted graph, we need to store vertex
        // and weight pair for every edge
        list<pair<Node *,double>> *adj;
    
};