// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

using namespace std;
# define INF 0x3f3f3f3f
 
// iPair ==>  Integer Pair
typedef pair<int, int> iPair;
 
class Node{
    public : double x , y ;
             int tag ;

    public : 
        Node(){
            this->x = 0;
            this->y = 0;
            this->tag = 0;
        }
        Node(double x , double y, int tag){
            this->x = x;
            this->y = y;
            this->tag = tag;
        }

};

class Edge
{
    public : Node *start;
             Node *end;
             double weight ;
    public : 
        Edge(Node *start , Node *end ){
            this->start = start;
            this->end = end;
            this->weight = sqrt(pow(start->x-end->x,2)+pow(start->y-end->y,2));
        }
};


class Graph
{

    public : int numberNodes;    // No. of vertices
            // In a weighted graph, we need to store vertex
            // and weight pair for every edge
            list<pair<Node *,double>> *adj;
 
    public:
        Graph(int numberNodes){
            this->numberNodes = numberNodes;
            adj = new list<pair<Node *,double>> [numberNodes];
        }  
        // function to add an edge to graph
        void addEdge(Edge edge){

            adj[edge.start->tag].push_back(make_pair(edge.start, edge.weight));
            adj[edge.end->tag].push_back(make_pair(edge.end, edge.weight));
        }
        // prints shortest path from s
        //void shortestPath(int s);
};


void draw(int numberNodes,vector<Node> nodes){
            // Create the main window
    int height = 1000 , width = 1000;
    sf::RenderWindow window(sf::VideoMode(width,height), "Grafo");
    
    vector<sf::CircleShape> shapes ;
    

    for (int i = 0; i < numberNodes; ++i){
        sf::CircleShape shape(1.f);
        shape.setFillColor(sf::Color::Green);
        sf::Vector2i v2;
        v2 = window.mapCoordsToPixel(sf::Vector2f(nodes.at(i).x,nodes.at(i).y));
        shape.setPosition( ( v2.x/(width))-8200, v2.y/(height) +200);
        shapes.push_back(shape);
    }


	





    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < shapes.size(); ++i){
            window.draw(shapes.at(i));
        }
     

        window.display();
    }
}

 
 
// Prints shortest paths from src to all other vertices
// void Graph::shortestPath(int src)
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
 
// Driver program to test methods of graph class





int main()
{
    // create the graph given in above fugure
    int numberNodes = 10;
    vector< vector <double> > data = {    {8825224.158,276682.7726},
                                            {8731925.253,323651.0204},
                                            {8714685.216,317992.8898},
                                            {8674105.475,299797.1793},
                                            {8677175.367,307975.169},
                                            {8696761.014,271186.3761},
                                            {8806301.525,291282.6593},
                                            {8820167.84,306122.8728},
                                            {8758790.967,239770.5303},
                                            {8787311.209,312266.0346}
                                        };
    vector< vector <double> > dataEdges {
        {1,2},
        {2,3},
        {3,4},
        {4,5},
        {4,10},
        {5,6},
        {6,7},
        {7,8},
        {8,9},
        {9,10}
    };

    vector<Node> nodes ;
    
    Graph g(numberNodes);

    /*for (int i = 0; i < numberNodes; ++i){
        Node node(data[i][0],data[i][1],i);
        nodes.push_back(node);
    }*/

	//read node from file
	ifstream readNode("listNode.txt");	//open the file
	if(!readNode){
		std::cout<<"Not FILE"<<std::endl;//file doesn't exist
	}
	char tmp;
	float x2=0, y2=0, t;
	int i=0;
	while(readNode >> t>>tmp>>x2>>tmp>>y2){
		Node node(x2,y2,i);
        nodes.push_back(node);
		i++;
	}



	//read Edge from file
	ifstream readEdge("listEdge.txt");	//open the file
	if(!readEdge){
		std::cout<<"Not FILE"<<std::endl;//file doesn't exist
	}
	//char tmp;
	//float x2=0, y2=0, t;
	i=0;
	while(readEdge >> t>>tmp>>x2>>tmp>>y2){
		Edge edge(&nodes[x2-1],&nodes[y2-1]);
        //  making above shown graph
        g.addEdge(edge);
		i++;
	}




    /*for (int i = 0; i < dataEdges.size(); ++i)
    {
        Edge edge(&nodes[dataEdges[i][0]-1],&nodes[dataEdges[i][1]-1]);
        //  making above shown graph
        g.addEdge(edge);
    }*/

    //cout << nodeOne.x << endl;
    //cout << edge.start->x << endl;
    // g.addEdge(0, 7, 8);
    // g.addEdge(1, 2, 8);
    // g.addEdge(1, 7, 11);
    // g.addEdge(2, 3, 7);
    // g.addEdge(2, 8, 2);
    // g.addEdge(2, 5, 4);
    // g.addEdge(3, 4, 9);
    // g.addEdge(3, 5, 14);
    // g.addEdge(4, 5, 10);
    // g.addEdge(5, 6, 2);
    // g.addEdge(6, 7, 1);
    // g.addEdge(6, 8, 6);
    // g.addEdge(7, 8, 7);
 
    //g.shortestPath(0);
    draw(numberNodes,nodes);


 
    return 0;
}
