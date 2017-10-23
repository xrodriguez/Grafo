// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
//#include <SFML/Text.hpp>
#include <iostream>
#include <list>
#include <omp.h>
#include "Heuristics.h"
#include "Graph.h"
#include "Node.h"
#include "Edge.h"

using namespace std;
using namespace sf;

vector<vector<Node>> sequentialSearch(Graph graph,vector<Node> start, vector<Node> end){
    int i,j ;
    vector<Node> shortestPath;
    vector<vector<Node>> shortestPaths;
    Heuristics heuristics; 
    double t0 = omp_get_wtime();
    for( i=0; i < start.size(); i++){
        for( j=0; j < end.size(); j++){
           shortestPath = heuristics.Astar(graph,start[i],end[j]);
            if(shortestPath.empty()){
                cout << "ERROR : RUTA INVALIDA ";
            }else{
                shortestPaths.push_back(shortestPath);
            }
        }
    }
    double t1 = omp_get_wtime();
    cout << "time sequential search : " << t1-t0 << endl ;
    return shortestPaths;
} 
 
vector<vector<Node>> parallelSearch(Graph graph,vector<Node> start, vector<Node> end){
    int i,j;
    vector<Node> shortestPath;
    vector<vector<Node>> shortestPaths;
    Heuristics heuristics; 
    double t0 = omp_get_wtime();
    #pragma omp parallel for num_threads(4) schedule(dynamic) private(shortestPath,i,j) shared(shortestPaths,graph,start,end)
    for( i=0; i < start.size(); i++){
        for( j=0; j < end.size(); j++){
            shortestPath = heuristics.Astar(graph,start[i],end[j]);
            if(shortestPath.empty()){
                cout << "ERROR : RUTA INVALIDA ";
            }else{
                shortestPaths.push_back(shortestPath);
            }
        }
    }
    double t1 = omp_get_wtime();
    cout << "time parallel search : " << t1-t0 << endl ;
    //#pragma omp barrier 
    return shortestPaths;
}   



void draw(Graph graph){
            // Create the main window
    int height = 1000 , width = 1000 , deltaWidth = 0 , deltaHeight = 0 ;
    RenderWindow window(sf::VideoMode(width,height), "Grafo");
    
    vector<CircleShape> shapes ;
    vector<Node> shortestPath;
    vector<vector<Node>> shortestPaths;
    
    Heuristics heuristics;    
    vector<Node> selectedNode ;
    vector<Node> selectedNodes;

    Font font;
    font.loadFromFile("arial.ttf");
    vector<Node> limits;
    
    vector<Node> start;
    vector<Node> end;
    
    while (window.isOpen()) {

        bool isSelectedNode = false , selectedNodes = false;
        Event event;
        while (window.pollEvent(event)){
            switch (event.type) {

                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    window.clear();
                    deltaWidth = event.size.width-width;
                    deltaHeight = event.size.height-height;
                    break;
                
                case Event::MouseButtonPressed :
                    if (event.mouseButton.button == Mouse::Left){
                        int x = event.mouseButton.x ;
                        x = (x*width)/(width+deltaWidth) ;
                        int y = event.mouseButton.y ;
                        y = (y*height)/(height+deltaHeight) ;
                        selectedNode = graph.getNodesByPoint(x,y);
                        isSelectedNode = true;
                    }else if (event.mouseButton.button == Mouse::Right){
                        double x = event.mouseButton.x ;
                        x = (x*width)/(width+deltaWidth) ;
                        double y = event.mouseButton.y ;
                        y = (y*height)/(height+deltaHeight);
                        //cout << "x " << x << endl;
                        //cout << "y " << y << endl;
                        int radio = 40;
                        if(start.empty()){
                            window.clear();
                            start = graph.getNodesByArea(x,y,radio);
                        }else if(end.empty()){
                            end = graph.getNodesByArea(x,y,radio);
                        }
                        //isSelectedNodes = true;
                        CircleShape area;
                        area.setFillColor(Color::Red);
                        area.setOrigin(radio,radio);
                        area.setPosition(x,y);
                        area.setRadius(radio);
                        area.setOutlineThickness(4);
                        area.setOutlineColor(Color::Red);
                        window.draw(area);
                    }
                    break;
                case Event::TextEntered :
                    if (event.text.unicode == 99 ){
                        window.clear();
                        limits.clear();
                        start.clear();
                        end.clear();
                        shortestPath.clear();
                        shortestPaths.clear();
                        cout << "Clean ... "<< endl;
                    }
                default:
                    break;
            }
            // if (event.type == sf::Event::Closed)
            //     window.close()  ;
            
            // if (event.type == sf::Event::Resized){
            //     window.clear();
            //     deltaWidth = event.size.width-width;
            //     deltaHeight = event.size.height-height;
            // }
                
            // if (event.type == sf::Event::MouseButtonPressed) {
            //     if (event.mouseButton.button == sf::Mouse::Left){
            //         int x = event.mouseButton.x ;
            //         x = (x*width)/(width+deltaWidth) ;
            //         int y = event.mouseButton.y ;
            //         y = (y*height)/(height+deltaHeight) ;
            //         selectedNodes = graph.getNodesByPoint(x,y);
            //         isSelectedNodes = true;
            //     }else if (event.mouseButton.button == sf::Mouse::Right){
            //         window.clear();
            //         limits.clear();
            //         shortestPath.clear();

            //     }
            // }
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

        if(!selectedNode.empty() and isSelectedNode){
            //cout<< selectedNodes.size() << endl;
            Text text(to_string((selectedNode[0]).tag), font);
            text.setCharacterSize(15);
            //text.setStyle(Text::Bold);
            text.setColor(Color::Red);
            text.setPosition(selectedNode[0].x,selectedNode[0].y);
            window.draw(text);
        

            limits.push_back(selectedNode[0]);
            if(limits.size() == 2) {
                shortestPath = heuristics.Astar(graph,limits[0],limits[1]);
                if(shortestPath.empty()){
                    cout << "ERROR : RUTA INVALIDA ";
                }else{
                    shortestPaths.push_back(shortestPath);
                }

            }else if(limits.size() > 2) {
                window.clear();
                limits.clear();
                shortestPath.clear();
                shortestPaths.clear();
            }
        }


        if(!start.empty() and !end.empty()){
            cout << start.size() << endl;
            cout << end.size() << endl;
            //shortestPaths = sequentialSearch(graph,start,end);
            shortestPaths = parallelSearch(graph,start,end);
            cout<< shortestPaths.size() << endl;
            start.clear();
            end.clear();
        }

        //shortestPath
        for (auto shortestPath = shortestPaths.begin(); shortestPath!=shortestPaths.end(); shortestPath++) {
            for (auto node=(*shortestPath).begin(); node!=(*shortestPath).end(); node++) {
                auto nextNode = next(node,1);
                if(nextNode != (*shortestPath).end() ){ 
                    VertexArray lines(Lines,2);
                    Color color(23, 165, 137);
                    lines[0].color = color;
                    lines[0].position = Vector2f(node->x,node->y);
                    lines[1].color = color;
                    lines[1].position = Vector2f(nextNode->x,nextNode->y);
                    window.draw(lines);            
                }
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
    ifstream file("data/Graphs/1000points.data");  //open the file
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
    //graph.printGraph();
    Heuristics heuristics;
    heuristics.preprocessing(graph);
    
    draw(graph);


    return 0;
}