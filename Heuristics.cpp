#include <iostream>

#include "Heuristics.h"
#include "Graph.h"
#include "Node.h"
#include <list>
#include <vector>
#include <map>
#include <fstream>


using namespace std;

Heuristics::Heuristics(){};


bool compareNode(const Node& a, const Node& b) {
   return a.f < b.f;
}


int calculateDistance(Node node1,Node node2){
	return sqrt(pow(node1.x-node2.x,2)+pow(node1.y-node2.y,2));
}

int calculateDistance2(Node node1,Node node2){
	return 0; //sqrt(pow(node1.x-node2.x,2)+pow(node1.y-node2.y,2));
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






/*
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
			if (    !(closedMap.find( (*neighbor).tag ) == closedMap.end() ) ){ //closed contain neighbor
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
*/

/*
vector<Node>  Heuristics::Dijkstra(Graph graph , Node start,Node end){
	vector<Node> failure ;
	cout<<  "NODOS: " <<start.tag<<" - "<<end.tag<<endl;
	double tentative_g;
   	map<int,Node*> openMap;
   	map<int,Node*> closedMap;
   	map<int, Node> map_node;

	start.g = 0 ;
	openMap[start.tag] = &start;
	start.f = calculateDistance2(start,end);
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

			tentative_g = current.g + calculateDistance2(*neighbor,current);
			if (tentative_g >= (*neighbor).g){
                continue;
			}

			map_node[(*neighbor).tag] = current;
			(*neighbor).g = tentative_g;
			(*neighbor).f = (*neighbor).g + calculateDistance2(*neighbor,end);

			Node neighborAux = Node((*neighbor).x , (*neighbor).y, (*neighbor).tag);
				neighborAux.f = (*neighbor).f;
				neighborAux.g = (*neighbor).g;

			openMap[ (*neighbor).tag]->g = neighborAux.g;// = new Node((*neighbor).x , (*neighbor).y, (*neighbor).tag);// &neighborAux;
			openMap[ (*neighbor).tag]->f = neighborAux.f; 

        }
	}
	return failure; 	
}
*/


/*
vector<Node>  Heuristics::contractionHierarchie(Graph graph , Node start,Node end){
	vector<Node> output;

	cout<<"preprocessing"<<endl;

	if(graph.numberNodes == 0){
		cout<<"have Not nodes"<<endl;
	}else{
		cout<<"have "<< graph.numberNodes <<" Nodes"<<endl;
	}

	int k = 0;
	cout<< graph.nodes[0].tag <<endl;
	return output;
}



float maxDistance(Graph graph){

	float max = 0;


	for(int m=0;m<graph.numberNodes;m++){
  		for(int n=0;n<graph.numberNodes;n++){
  			if(max < calculateDistance(graph.nodes[m],graph.nodes[n])  ){
	  			max = calculateDistance(graph.nodes[m],graph.nodes[n] );
			}
		}
	}	

	return max;
}
*/


void  Heuristics::preprocessing(Graph graph ){
	vector<Node> shortestPath;
	shortestPath = Astar(graph,graph.nodes[644],graph.nodes[7474]);


	//float max = calculateDistance(graph.nodes[0],graph.nodes[2]);

/*
	float mediaDistance = maxDistance(graph);



	ofstream myfile;
  	myfile.open ("preprocessed/10000points.data");
  	

  	for(int m=0;m<graph.numberNodes;m++){
  		for(int n=0;n<graph.numberNodes;n++){
  			if(mediaDistance*0.90 < calculateDistance(graph.nodes[m],graph.nodes[n])  ){
	  			shortestPath = Astar(graph,graph.nodes[m],graph.nodes[n]);
			  	myfile <<graph.nodes[m].tag << " "<< graph.nodes[n].tag <<" ";// "Writing this to a file.\n";
			  	for(int i=0; i<shortestPath.size(); i++){
			  		myfile <<shortestPath[i].tag<<" ";
			  	}
			  	myfile<<"\n";
			}
		}  	
	}

  	myfile.close();
*/	
}










Heuristics::~Heuristics(){};
	
