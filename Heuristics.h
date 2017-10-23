#include "Node.h"
#include "Graph.h"

class Heuristics
{
	public:
		Heuristics();
		vector<Node> Astar(Graph graph , Node start,Node end);
		vector<Node> BidirectionalAstar(Graph graph , Node start,Node end);
		vector<Node> Dijkstra(Graph graph , Node start,Node end);
		vector<Node> contractionHierarchie(Graph graph , Node start,Node end);
		void preprocessing(Graph graph );
		//vector<Node> reconstruct_path(map<int, Node> cameFrom, Node current);
		bool haveEdge(int a, int b);
		//void Dijkstra(Graph graph , Node start );
		~Heuristics();
	
};