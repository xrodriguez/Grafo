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
	cout<<  "size of map:    " <<cameFrom.size() <<endl;
	map<int, Node>::iterator iter ;
	for ( iter = cameFrom.begin(); iter !=cameFrom.end(); ++iter)
	{
		std::cout << iter->first << " => " << iter->second.tag << '\n';
	}


	while(  ! (cameFrom.find(current.tag) == cameFrom.end() ) ){
		//cout<<"FIND"<<endl;i++;if(i==2)break;
		//i++;if(i==20) break;
		cout<<"WHILE"<< current.tag <<endl;
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
	int k=0;
	///while(!openList.empty()){
	while(!openMap.empty()){
		k++;		
		Node* _bestCandidate = NULL;
		map<int,Node* >::iterator _it;
		if (k==2)
		{
			//cout<< "kkk:  "<<openMap[5]->f<<endl;
			//cout<< "kkk   "<<openMap[7]->f<<endl;
			//cout<< "kkk   "<<openMap[0]->f<<endl;
		}



		for ( _it = openMap.begin(); _it != openMap.end(); ++_it )
        {
            Node* _toExplore_candidate = _it->second;
            if ( _bestCandidate == NULL )
            {
            	_bestCandidate = _toExplore_candidate;
            }
            else if ( _toExplore_candidate->f < _bestCandidate->f )
            {
                	_bestCandidate = _toExplore_candidate;
            }
        }

        Node current = *(_bestCandidate);

        //Node* _nextToExplore = _bestCandidate;
        openMap.erase( current.tag );
        closedMap[current.tag] = &current;

        map<int, Node>::iterator iter ;
		for ( iter = map_node.begin(); iter !=map_node.end(); ++iter)
		{
			std::cout << iter->first << " => " << iter->second.tag << '\n';
		}


        //if(current.compare(end)) {
        if(current.tag == end.tag) {
        	cout <<"Ruta:::::::::::::::::::::::::::::::::::::::::::::::::::::: "<<"FIN"<<endl; 
        	return reconstruct_path(map_node,current);
        }



		list<Node> neighbors = graph.getNeighbors(current);
		cout<<"                 nodo: "<<current.tag<<   " size: " <<neighbors.size() <<endl;
		for (auto neighbor = neighbors.begin(); neighbor !=neighbors.end(); neighbor++){
			cout<<"FOR:::::::::::::::::::::::::::::::::::::"<<endl;

			if (    !(closedMap.find( (*neighbor).tag ) == closedMap.end() ) )
            {
            	cout<<"continue..............."<< (*neighbor).tag <<endl;
                continue;
            }

			if(  (openMap.find( (*neighbor).tag ) == openMap.end())   ){
				Node* neighborAux = new  Node((*neighbor).x , (*neighbor).y, (*neighbor).tag)  ;
				//neighborAux.f = (*neighbor).f;
				//neighborAux.g = (*neighbor).g;
				openMap[(*neighbor).tag ] = neighborAux;
				cout<<" BEFORE INSERT:  "<<(*neighbor).tag <<endl;
			}

			tentative_g = current.g + calculateDistance(*neighbor,current);
			cout<< "suma:  " <<current.g <<" + "<<calculateDistance(*neighbor,current)<< " comp:  "<< (*neighbor).g <<endl;
			if (tentative_g >= (*neighbor).g){
				cout<<"Second continue...."<< tentative_g << " <> "<<(*neighbor).g<<endl;
                continue;
			}
			cout<<"inserttttttttttttttttt "<< (*neighbor).tag <<endl;
			//tmpList.insert(*neighbor);

			map_node[(*neighbor).tag] = current;

			(*neighbor).g = tentative_g;

			(*neighbor).f = (*neighbor).g + calculateDistance(*neighbor,end);

			Node neighborAux = Node((*neighbor).x , (*neighbor).y, (*neighbor).tag);
				neighborAux.f = (*neighbor).f;
				neighborAux.g = (*neighbor).g;
			cout<< "hhh:::::    "<<calculateDistance(neighborAux,end)<<endl;
			cout<< "ggg:::::    "<<neighborAux.g<<endl;
			cout<< "fff:::::    "<<neighborAux.f<<endl;
			cout<<"inserttttttttttttttttt  2) "<< (*neighbor).tag <<endl;
			openMap[ (*neighbor).tag]->g = neighborAux.g;// = new Node((*neighbor).x , (*neighbor).y, (*neighbor).tag);// &neighborAux;
			openMap[ (*neighbor).tag]->f = neighborAux.f; 
			//cout<< "kkkkk:  "<<openMap[5]->f<<endl;
			//cout<< "kkkkk   "<<openMap[7]->f<<endl;
			//cout<< "kkkkk   "<<openMap[0]->f<<endl;
			cout<<"FINAL FOR:  "<< (*neighbor).tag <<" - "<<openMap[ (*neighbor).tag]->f<<endl;
			//openMap[ (*neighbor).tag]-> 
			//free(*neighborAux)	;
        }
        //if(k==20) break;
	}
	return failure; 	
}




Heuristics::~Heuristics(){};
	
