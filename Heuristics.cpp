#include <iostream>

#include "Heuristics.h"
#include "Graph.h"
#include "Node.h"

#include <list>
#include <vector>
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


bool haveEdge(int a, int b){
	return true;
}

vector<Node> reconstruct_path( vector<Node> listRuta ,Node current  ){
	vector<Node> path;

	path.push_back(current);

	for (int i = listRuta.size() -1; i > 0; --i)
	{
		if(  haveEdge(   listRuta[i -1].tag , path.begin()   )  ){
			current = listRuta[i-1];
			path.push_back( current );			
		}
	}



}



vector<Node>  Heuristics::Astar(Graph graph , Node start,Node end){
	
	//set<Node> openList;
	cout<<  "NODOS: " <<start.tag<<" - "<<end.tag<<endl;
	double tentative_g;
   	set<Node, bool (*)(const Node&, const Node&) > openList(compareNode);
   	set<Node, bool (*)(const Node&, const Node&) > closedList(compareNode);
   	vector<pair<Node,Node>> cameFrom;
   	set<Node, bool (*)(const Node&, const Node&) > tmpList(compareNode);
   	vector<Node> listRuta;
	//openList.insert(start);
	//start.f = 0 ;
	start.g = 0 ;
	openList.insert(start);
	start.f = calculateDistance(start,end);
	//cout<< "Heuristics"<<start.f<<endl;
	int k=0;
	while(!openList.empty()){
		k++;
		//cout<<"While"<<endl;
		Node current = *openList.begin();
		//cout<<"start :  "<<start.g<<endl;
		//cout<<"current :  "<<current.g<<endl;
        if(current.compare(end)) {
        	for(int i=0; i<listRuta.size(); i++){
        		cout<<"   ->  " << listRuta[i].tag << " "<<endl;
        	}
        	cout <<"Ruta:::::::::::::::::::::::::::::::::::::::::::::::::::::: "<< listRuta.size() << endl ;cout<<"FIN"<<endl; return listRuta;

        }
        //cout<<"Paso1...... "<<endl;
        openList.erase(openList.begin());
        closedList.insert(current);

		list<Node> successors = graph.getSuccessors(current);
		cout<<"                 nodo: "<<current.tag<<   " size: " <<successors.size() <<endl;
		for (auto successor = successors.begin(); successor !=successors.end(); successor++){
			//cout<<"Paso2.............."<<endl;

			//double new_cost = current.g +  calculateDistance(*successor,current);
			if( findNode(closedList,*successor) ){
				cout<<"continue.... "<< (*successor).tag<<endl;
				continue;
			}

			if( !findNode(openList,*successor) ){
				//cout<<"Segundo IF......."<<endl;
				openList.insert(*successor);
				cout<<" Second IF tag:  "<<(*successor).tag <<endl;
				//(*successor).g = new_cost;
    	       	//(*successor).f = (*successor).g + 0;//calculateDistance(*successor,end);
    	       	//cameFrom.push_back(make_pair((*successor),current));
			}

			/*if( findNode(closedList,*successor) || new_cost < (*successor).f){
				(*successor).g = new_cost;
    	       	(*successor).f = (*successor).g + 0;//calculateDistance(*successor,end);
    	       	cameFrom.push_back(make_pair((*successor),current));
			}*/			

			tentative_g = current.g + calculateDistance(*successor,current);
			cout<< "SUMA:  " <<current.g <<" + "<<calculateDistance(*successor,current)<< " comp:  "<< (*successor).g <<endl;
			if (tentative_g >= (*successor).g){
				cout<<"Second continue...."<< tentative_g << " <> "<<(*successor).g<<endl;
                continue;
			}
			cout<<"INSERRRRRRRRRRRRRRRRR"<<endl;
			tmpList.insert(*successor);
			listRuta.push_back(*successor);
			//cout<<"INSERT NEW PATH........................................................."<<endl;
			(*successor).g = tentative_g;



			(*successor).f = (*successor).g + calculateDistance(*successor,end);


			for (auto it = openList.begin(); it !=openList.end(); it++){	
				if((*successor).tag == (*it).tag ) {
					cout<<"CHANGE VALUE: "  <<  (*openList.begin()).tag << endl;
					openList.erase(*it);
        			openList.insert( (*successor) );
					
					//return true;
				}
			}


			cout<<"VALOR queue: "<< (*openList.begin()).g << endl;
			cout<<"VALOR neighbor: "<<(*successor).g<<endl;




			//gScore[neighbor] := tentative_gScore
            //fScore[neighbor] := gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)
			
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

        //if(k==4) break;

	}
	cout <<"Ruta:::::::::::::::::::::::::::::::::::::::::::::::::::::: "<< tmpList.size() << endl ;
	return listRuta; 	
}




Heuristics::~Heuristics(){};
	