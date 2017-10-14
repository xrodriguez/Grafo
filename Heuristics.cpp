#include <iostream>

#include "Heuristics.h"
#include "Graph.h"
#include "Node.h"

#include <list>

using namespace std;

Heuristics::Heuristics(){};


bool compareNode(const Node& a, const Node& b) {
   return a.f < b.f;
}



// void Graph::Dijkstra(Node src)
// {
//     // Create a priority queue to store vertices that
//     // are being preprocessed. This is weird syntax in C++.
//     // Refer below link for details of this syntax
//     // http://geeksquiz.com/implement-min-heap-using-stl/
//     priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
 
//     // Create a vector for distances and initialize all
//     // distances as infinite (INF)
//     vector<int> dist(V, INF);
 
//     // Insert source itself in priority queue and initialize
//     // its distance as 0.
//     pq.push(make_pair(0, src));
//     dist[src] = 0;
 
//     /* Looping till priority queue becomes empty (or all
//       distances are not finalized) */
//     while (!pq.empty())
//     {
//         // The first vertex in pair is the minimum distance
//         // vertex, extract it from priority queue.
//         // vertex label is stored in second of pair (it
//         // has to be done this way to keep the vertices
//         // sorted distance (distance must be first item
//         // in pair)
//         int u = pq.top().second;
//         pq.pop();
 
//         // 'i' is used to get all adjacent vertices of a vertex
//         list< pair<int, int> >::iterator i;
//         for (i = adj[u].begin(); i != adj[u].end(); ++i)
//         {
//             // Get vertex label and weight of current adjacent
//             // of u.
//             int v = (*i).first;
//             int weight = (*i).second;
 
//             //  If there is shorted path to v through u.
//             if (dist[v] > dist[u] + weight)
//             {
//                 // Updating distance of v
//                 dist[v] = dist[u] + weight;
//                 pq.push(make_pair(dist[v], v));
//             }
//         }
//     }
 
//     // Print shortest distances stored in dist[]
//     printf("Vertex   Distance from Source\n");
//     for (int i = 0; i < V; ++i)
//         printf("%d \t\t %d\n", i, dist[i]);
// }


int calculateDistance(Node node1,Node node2){
	return sqrt(pow(node1.x-node2.x,2)+pow(node1.y-node2.y,2));
}

bool findNode(set<Node,bool (*)(const Node&, const Node&)> list , Node node){
	for (auto it = list.begin(); it !=list.end(); it++){	
		if(node.compare(*it)) return true;
	}
	return false;
}


void  Heuristics::Astar(Graph graph , Node start,Node end){
	
	//set<Node> openList;
   	set<Node, bool (*)(const Node&, const Node&) > openList(compareNode);
   	set<Node, bool (*)(const Node&, const Node&) > closedList(compareNode);
   	vector<pair<Node,Node>> cameFrom;

	openList.insert(start);
	start.f = 0 ;
	while(!openList.empty()){
		Node current = *openList.begin();
        if(current.compare(end)) return;

        openList.erase(openList.begin());
        closedList.insert(current);

		list<Node> successors = graph.getSuccessors(current);
		for (auto successor = successors.begin(); successor !=successors.end(); successor++){	
			double new_cost = current.g +  calculateDistance(*successor,current);
			if( findNode(closedList,*successor) || new_cost < (*successor).f){
				(*successor).g = new_cost;
    	       	(*successor).f = (*successor).g + 0;//calculateDistance(*successor,end);
    	       	cameFrom.push_back(make_pair((*successor),current));
			}
    		//if(successor in closedList)	
			// if(findNode(closedList,*successor)){
   //  			cout<< (*successor).tag << endl;
			//  	continue;
			// }
			// if(!findNode(openList,*successor)){
			//  	openList.insert(*successor);
			// }

   //  		double tentative_g = current.g + calculateDistance(*successor,current);
   //        	if(tentative_g >= (*successor).g){
   //        		continue;
   //        	}
   //        	cameFrom.push_back(make_pair((*successor),current));
   //        	cout << (*successor).tag << "-" << current.tag << endl ;
   //        	(*successor).g = tentative_g;
   //        	(*successor).f = (*successor).g + calculateDistance(*successor,end);
        }
	}
	cout << cameFrom.size() << endl ;
	return; 	
}




Heuristics::~Heuristics(){};
	