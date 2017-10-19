#include <iostream>

#include "Heuristics.h"
#include "Graph.h"
#include "Node.h"
#include <list>
#include <vector>
#include <map>

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
		//if(node.compare(*it)) return true;
		if(node.tag==(*it).tag) return true;
	}
	return false;
}


bool haveEdge(int a, int b){
	return true;
}

vector<Node> reconstruct_path( map<int, Node> cameFrom ,Node current  ){
	vector<Node> path;
	path.push_back(current);
	int i=0;
	map<int, Node>::iterator iter ;

	while(  ! (cameFrom.find(current.tag) == cameFrom.end() ) ){
		current = cameFrom[current.tag];
		path.push_back(current);
	}
	return path;
}



vector<Node>  Heuristics::Astar(Graph graph , Node start,Node end){
	vector<Node> failure ;
	cout<<  "NODOS: " <<start.tag<<" - "<<end.tag<<endl;
	double tentative_g;
   	map<int,Node*> openMap;
   	map<int,Node*> closedMap;
   	map<int, Node> map_node;

	start.g = 0 ;
	openMap[start.tag] = &start;
	start.f = calculateDistance(start,end);
	while(!openMap.empty()){
		Node* bestNode = NULL;
		map<int,Node* >::iterator _it;

		for ( _it = openMap.begin(); _it != openMap.end(); ++_it )
        {
            Node* candidate = _it->second;
            if ( bestNode == NULL )
            {
            	bestNode = candidate;
            }
            else if ( candidate->f < bestNode->f )
            {
                	bestNode = candidate;
            }
        }

        Node current = *(bestNode);
        openMap.erase( current.tag );
        closedMap[current.tag] = &current;

        map<int, Node>::iterator iter ;

        if(current.tag == end.tag) {
        	cout <<"Ruta:::::::::::::::::::::::::::::::::::::::::::::::::::::: "<<"FIN"<<endl; 
        	return reconstruct_path(map_node,current);
        }

		list<Node> neighbors = graph.getNeighbors(current);
		for (auto neighbor = neighbors.begin(); neighbor !=neighbors.end(); neighbor++){
			//cout<<"FOR:::::::::::::::::::::::::::::::::::::"<<endl;
			if (    !(closedMap.find( (*neighbor).tag ) == closedMap.end() ) ){
                continue;
            }

			if(  (openMap.find( (*neighbor).tag ) == openMap.end())   ){
				Node* neighborAux = new  Node((*neighbor).x , (*neighbor).y, (*neighbor).tag)  ;
				openMap[(*neighbor).tag ] = neighborAux;
			}

			tentative_g = current.g + calculateDistance(*neighbor,current);
			if (tentative_g >= (*neighbor).g){
                continue;
			}

			map_node[(*neighbor).tag] = current;
			(*neighbor).g = tentative_g;
			(*neighbor).f = (*neighbor).g + calculateDistance(*neighbor,end);

			Node neighborAux = Node((*neighbor).x , (*neighbor).y, (*neighbor).tag);
				neighborAux.f = (*neighbor).f;
				neighborAux.g = (*neighbor).g;

			openMap[ (*neighbor).tag]->g = neighborAux.g;// = new Node((*neighbor).x , (*neighbor).y, (*neighbor).tag);// &neighborAux;
			openMap[ (*neighbor).tag]->f = neighborAux.f; 

        }
	}
	return failure; 	
}


vector<Node>  Heuristics::BidirectionalAstar(Graph graph , Node start,Node end){
	vector<Node> failure ;
	cout<<  "NODOS: " <<start.tag<<" - "<<end.tag<<endl;
	double tentative_g;
   	map<int,Node*> openMap;
   	map<int,Node*> closedMap;
   	map<int,Node*> openMap2;
   	map<int,Node*> closedMap2;

   	map<int, Node> map_node;

	start.g = 0 ;
	openMap[start.tag] = &start;
	start.f = calculateDistance(start,end);
	
	while(!openMap.empty() && !openMap2.empty()  ){
		
		//to first process
		Node* bestNode = NULL;		
		map<int,Node* >::iterator _it;
		for ( _it = openMap.begin(); _it != openMap.end(); ++_it ){
            Node* candidate = _it->second;
            if ( bestNode == NULL ){
            	bestNode = candidate;
            }
            else if ( candidate->f < bestNode->f ){
                	bestNode = candidate;
            }
        }

        Node current = *(bestNode);
        openMap.erase( current.tag );
        closedMap[current.tag] = &current;

        map<int, Node>::iterator iter ;

        if(current.tag == end.tag) {
        	cout <<"Ruta:::::::::::::::::::::::::::::::::::::::::::::::::::::: "<<"FIN"<<endl; 
        	return reconstruct_path(map_node,current);
        }


		list<Node> neighbors = graph.getNeighbors(current);
		for (auto neighbor = neighbors.begin(); neighbor !=neighbors.end(); neighbor++){
			if (    !(closedMap.find( (*neighbor).tag ) == closedMap.end() ) ){
                continue;
            }

			if(  (openMap.find( (*neighbor).tag ) == openMap.end())   ){
				Node* neighborAux = new  Node((*neighbor).x , (*neighbor).y, (*neighbor).tag)  ;
				openMap[(*neighbor).tag ] = neighborAux;
			}

			tentative_g = current.g + calculateDistance(*neighbor,current);
			if (tentative_g >= (*neighbor).g){
                continue;
			}
			map_node[(*neighbor).tag] = current;
			(*neighbor).g = tentative_g;
			(*neighbor).f = (*neighbor).g + calculateDistance(*neighbor,end);
			Node neighborAux = Node((*neighbor).x , (*neighbor).y, (*neighbor).tag);
			neighborAux.f = (*neighbor).f;
			neighborAux.g = (*neighbor).g;
			openMap[ (*neighbor).tag]->g = neighborAux.g;// = new Node((*neighbor).x , (*neighbor).y, (*neighbor).tag);// &neighborAux;
			openMap[ (*neighbor).tag]->f = neighborAux.f; 
        }



        //to second process.


		Node* bestNode = NULL;		
		map<int,Node* >::iterator _it;
		for ( _it = openMap2.begin(); _it != openMap2.end(); ++_it ){
            Node* candidate = _it->second;
            if ( bestNode == NULL ){
            	bestNode = candidate;
            }
            else if ( candidate->f < bestNode->f ){
                	bestNode = candidate;
            }
        }
        Node current = *(bestNode);
        openMap.erase( current.tag );
        closedMap[current.tag] = &current;






	}
	return failure; 	
}




Heuristics::~Heuristics(){};
	
