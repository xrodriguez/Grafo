#include <iostream>

#include "Heuristics.h"
#include "Graph.h"
#include "Node.h"

#include <list>

using namespace std;

Heuristics::Heuristics(){};
void  Heuristics::Astar(Graph graph , Node start,Node end){
	
	list<Node> openList;
	list<Node> closedList;

	openList.push_back(start);
	start.f = 0 ;
	//while(!openList.empty()){
	//cout<< "a star" << endl ;
		
	//}
	
}
Heuristics::~Heuristics(){};
	