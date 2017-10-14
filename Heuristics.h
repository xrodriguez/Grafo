#include "Node.h"
#include "Graph.h"

class Heuristics
{
	public:
		Heuristics();
		void Astar(Graph graph , Node start,Node end);
		//void Dijkstra(Graph graph , Node start );
		~Heuristics();
	
};