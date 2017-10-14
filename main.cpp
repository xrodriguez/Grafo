// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
//#include <SFML/Text.hpp>
#include <iostream>
#include <list>

#include "Heuristics.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

using namespace std;


void draw(int numberNodes,vector<Node> nodes){
            // Create the main window
    int height = 1000 , width = 1000;
    sf::RenderWindow window(sf::VideoMode(width,height), "Grafo");
    
    vector<sf::CircleShape> shapes ;
    

    for (int i = 0; i < numberNodes; ++i){
        sf::CircleShape shape(1.f);

        shape.setFillColor(sf::Color::Green);
        //shape.setFillColor(sf::Color(255,0,0));
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
        sf::Font font;
        font.loadFromFile("arial.ttf");
        for (int i = 0; i < shapes.size(); ++i){
            window.draw(shapes.at(i));
            sf::Text text(to_string(i), font);
            text.setCharacterSize(15);
            text.setStyle(sf::Text::Bold);
            text.setColor(sf::Color::Red);
            text.setPosition(shapes.at(i).getPosition());
            window.draw(text);
        }
     // Declare and load a font
// Create a text
// Draw it

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

    vector<Node> nodes ;
    
    Graph graph(numberNodes);
	//read node from file
	ifstream readNode("listNode.txt");	//open the file
	if(!readNode){
		std::cout<<"Not FILE"<<std::endl;//file doesn't exist
	}
	char tmp;
	float x,y,t;
	int i=0;
	while(readNode >> t>>tmp>>x>>tmp>>y){
        nodes.push_back(Node(x,y,i));
		i++;
	}

	//read Edge from file
	ifstream readEdge("listEdge.txt");	//open the file
	if(!readEdge){
		std::cout<<"Not FILE"<<std::endl;//file doesn't exist
	}

	i=0;
    while(readEdge >> x>>tmp>>y){
        graph.addEdge(Edge(&nodes[x-1],&nodes[y-1]));
		i++;
	}

    graph.printGraph();
    //Heuristics h;
   //h.Astar(graph,nodes.at(0),nodes.at(9));
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
