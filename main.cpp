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
using namespace sf;


void draw(Graph graph ,vector<Node> shortestPath ){
            // Create the main window
    int height = 1000 , width = 1000 , deltaWidth = 0 , deltaHeight = 0 ;
    sf::RenderWindow window(sf::VideoMode(width,height), "Grafo");
    
    vector<sf::CircleShape> shapes ;
    Font font;
    font.loadFromFile("arial.ttf");
    vector<Node> limits;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::Resized){
                window.clear();
                deltaWidth = event.size.width-width;
                deltaHeight = event.size.height-height;
                //std::cout << "new width: " << event.size.width << std::endl;
                //std::cout << "new height: " << event.size.height << std::endl;
            }
                
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left){
                    //std::cout << "the right button was pressed" << std::endl;
                    //std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    //std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    int x = event.mouseButton.x ;
                    x = (x*width)/(width+deltaWidth) ;
                    int y = event.mouseButton.y ;
                    y = (y*height)/(height+deltaHeight) ;
                    //std::cout << "dx: " << deltaWidth << std::endl;
                    //std::cout << "mouse x-d: " << x << std::endl;
                    //std::cout << "mouse y-d: " << y << std::endl;
                    
                    vector<Node> nearNodes = graph.getNodesByPoint(x,y);
                    if(!nearNodes.empty()){
                        //cout<< nearNodes.size() << endl;
                        Text text(to_string((nearNodes[0]).tag), font);
                        text.setCharacterSize(15);
                        text.setStyle(Text::Bold);
                        text.setColor(Color::Red);
                        //text.setPosition((nearNodes[0]).getX(width,-8200),(nearNodes[0]).getY(width,200));
                        text.setPosition(nearNodes[0].x,nearNodes[0].y);
                        window.draw(text);
                        //if(limits.size() < 2 ) {
                        //}
                        limits.push_back(nearNodes[0]);
                        if(limits.size() == 2) {
                            //limits.erase(limits.begin());
                            //limits.push_back(nearNodes[0]);
                            cout << "DESDE : " << (limits[0]).tag << "HASTA: " << (limits[1]).tag << endl;
                        }else if(limits.size() > 2) {
                            window.clear();
                            limits.clear();
                        }
                        cout<<limits.size() << endl;
                    }
                }else if (event.mouseButton.button == sf::Mouse::Right){
                    window.clear();
                    limits.clear();
                }
            }
        }

        
        //nodes
        for (auto node=graph.nodes.begin(); node!=graph.nodes.end(); node++){
            CircleShape shape(2.f);
            shape.setFillColor(sf::Color::Green);
            //shape.setFillColor(sf::Color(255,0,0));
            //Vector2i coordenates = window.mapCoordsToPixel(Vector2f(node->x,node->y));
            //shape.setPosition(node->getX(width,-8200),node->getY(width,200));
            shape.setPosition(node->x,node->y);
            window.draw(shape);
            // print text

        }
        //edges 
        for (auto edge=graph.edges.begin(); edge!=graph.edges.end(); edge++){
            //cout << edge->start->x << " " << edge->end->x << endl;
            sf::VertexArray lines(Lines, 2);
            //lines[0].position = Vector2f(edge->start->getX(width,-8200),edge->start->getY(width,200));
            lines[0].position = Vector2f(edge->start->x,edge->start->y);
            //lines[1].position = Vector2f(edge->end->getX(width,-8200),edge->end->getY(width,200));
            lines[1].position = Vector2f(edge->end->x,edge->end->y);
            window.draw(lines);

        }

        //for (auto node=shortestPath.begin(); node!=shortestPath.end(); node++) {
            //cout << node->tag << endl;
            // auto nextNode = next(node,1);
            // if(nextNode != shortestPath.end() ){
            //     VertexArray lines(Lines,2);
            //     lines[0].color = Color::Blue;
            //     lines[0].position = Vector2f(node->getX(width,-8200),node->getY(width,200));
            //     lines[1].position = Vector2f(nextNode->getX(width,-8200),nextNode->getY(width,200));
            //     lines[1].color = Color::Blue;
            //     window.draw(lines);            
            // }
        //}
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
    //int numberNodes;
    vector<Node> nodes ;
    vector<Edge> edges ;
    string line;
    ifstream file("data/Graphs/100points.data");  //open the file
    if (file.is_open()){
        int i = 0 , numberNodes;
        while(getline (file,line)){
            vector<string> result;
            istringstream iss(line);
            for(std::string line; iss >> line; )
                result.push_back(line);
            if(i == 0 ){
                numberNodes = stoi(result[1]);
            }else if( i < numberNodes+1){
                nodes.push_back(Node(stoi(result[0]),stoi(result[1]),i-1));                
            }else if(i == numberNodes+1 ){
                int numberEdges = stoi(result[1]);
            }else{
                 edges.push_back(Edge(&nodes[stoi(result[0])],&nodes[stoi(result[1])]));
            }
            i++;
        }
        file.close();
    }
    else { 
        cout << "Unable to open file";
    }
    cout << nodes.size()<< endl;
    cout << edges.size()<< endl;
    Graph graph(nodes,edges);
    graph.printGraph();
    vector<Node> shortestPath; 
    Heuristics h;

    //vector<Node> shortestPath = h.Astar(graph,nodes.at(0),nodes.at(10));

    //= h.Astar(graph,nodes.at(0),nodes.at(9)); ;
    // shortestPath.push_back(nodes.at(0));
    // shortestPath.push_back(nodes.at(1));
    // shortestPath.push_back(nodes.at(2));
    // shortestPath.push_back(nodes.at(3));
    draw(graph,shortestPath);


    return 0;
}
