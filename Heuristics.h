#include "Node.h"
#include "Graph.h"

class Heuristics
{
	public:
		Heuristics();
		vector<Node> Astar(Graph graph , Node start,Node end);
		vector<Node> reconstruct_path(vector<Node> a, Node b);
		bool haveEdge(int a, int b);
		//void Dijkstra(Graph graph , Node start );
		~Heuristics();
	
};