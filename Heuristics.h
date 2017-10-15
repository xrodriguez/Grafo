#include "Node.h"
#include "Graph.h"

class Heuristics
{
	public:
		Heuristics();
		vector<Node> Astar(Graph graph , Node start,Node end);
		//void Dijkstra(Graph graph , Node start );
		~Heuristics();
	
};