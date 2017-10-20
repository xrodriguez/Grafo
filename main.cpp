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


void draw(Graph graph){
            // Create the main window
    int height = 1000 , width = 1000 , deltaWidth = 0 , deltaHeight = 0 ;
    RenderWindow window(sf::VideoMode(width,height), "Grafo");
    
    vector<sf::CircleShape> shapes ;
    vector<Node> shortestPath;
    Heuristics heuristics;    
    vector<Node> selectedNodes;
    Font font;
    font.loadFromFile("arial.ttf");
    vector<Node> limits;
    while (window.isOpen())
    {

        bool isSelectedNodes = false;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close()  ;
            
            if (event.type == sf::Event::Resized){
                window.clear();
                deltaWidth = event.size.width-width;
                deltaHeight = event.size.height-height;
            }
                
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left){
                    int x = event.mouseButton.x ;
                    x = (x*width)/(width+deltaWidth) ;
                    int y = event.mouseButton.y ;
                    y = (y*height)/(height+deltaHeight) ;
                    selectedNodes = graph.getNodesByPoint(x,y);
                    isSelectedNodes = true;
                }else if (event.mouseButton.button == sf::Mouse::Right){
                    window.clear();
                    limits.clear();
                    shortestPath.clear();

                }
            }
        }
        
        
        //nodes
        for (auto node=graph.nodes.begin(); node!=graph.nodes.end(); node++){
            CircleShape shape(2.f);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(node->x,node->y);
            window.draw(shape);

        }
        //edges 
        for (auto edge=graph.edges.begin(); edge!=graph.edges.end(); edge++){
            //cout << edge->start->x << " " << edge->end->x << endl;
            sf::VertexArray lines(Lines, 2);
            lines[0].position = Vector2f(edge->start->x,edge->start->y);
            lines[1].position = Vector2f(edge->end->x,edge->end->y);
            window.draw(lines);

        }

        if(!selectedNodes.empty() and isSelectedNodes){
            //cout<< selectedNodes.size() << endl;
            Text text(to_string((selectedNodes[0]).tag), font);
            text.setCharacterSize(15);
            //text.setStyle(Text::Bold);
            text.setColor(Color::Red);
            text.setPosition(selectedNodes[0].x,selectedNodes[0].y);
            window.draw(text);
            


            limits.push_back(selectedNodes[0]);
            if(limits.size() == 2) {
                shortestPath = heuristics.Astar(graph,limits[0],limits[1]);
                if(shortestPath.empty()){
                    cout << "ERROR : RUTA INVALIDA ";
                }

            }else if(limits.size() > 2) {
                window.clear();
                limits.clear();
                shortestPath.clear();
            }
        }

        // shortestPath
        for (auto node=shortestPath.begin(); node!=shortestPath.end(); node++) {
            auto nextNode = next(node,1);
            if(nextNode != shortestPath.end() ){ 
                VertexArray lines(Lines,2);
                lines[0].color = Color::Blue;
                lines[0].position = Vector2f(node->x,node->y);
                lines[1].color = Color::Blue;
                lines[1].position = Vector2f(nextNode->x,nextNode->y);
                window.draw(lines);            
            }
        }
        window.display();
    }
}

 

int main()
{
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

    Graph graph(nodes,edges);
    graph.printGraph();

    //shortestPath = h.Astar(graph,nodes.at(60),nodes.at(69));
    //shortestPath = h.Astar(graph,nodes.at(60),nodes.at(104));
    //NO CORRE
    //shortestPath = h.Astar(graph,nodes.at(4),nodes.at(72));
    //cout<< " size of nodes "<<shortestPath.size()<<endl;
    //= h.Astar(graph,nodes.at(0),nodes.at(9)); ;
    // shortestPath.push_back(nodes.at(0));
    // shortestPath.push_back(nodes.at(1));
    // shortestPath.push_back(nodes.at(2));
    // shortestPath.push_back(nodes.at(3));
    draw(graph);


    return 0;
}
