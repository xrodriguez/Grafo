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
    cout << "Number initial nodes : " << start.size()<< endl;
    cout << "Number end nodes : " << end.size()<< endl;
    cout << "Number searchs : " << start.size()*end.size()<< endl;
    cout << "Time sequential search : " << t1-t0 << endl ;
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
                cout << "ERROR : RUTA INVALIDA " << endl;
            }else{
            }
            # pragma omp critical
            shortestPaths.push_back(shortestPath);
        }
    }
    double t1 = omp_get_wtime();
    cout << "Number initial nodes : " << start.size() << endl;
    cout << "Number end nodes : " << end.size() << endl;
    cout << "Number searchs : " << start.size()*end.size() << endl;
    cout << "Time parallel search : " << t1-t0 << endl ;
    return shortestPaths;
}   



void draw(Graph graph){
            // Create the main window
    int height = 1000 , width = 1000 , deltaWidth = 0 , deltaHeight = 0 ;
    RenderWindow window(sf::VideoMode(width,height), "Grafo");
    
    vector<CircleShape> shapes ;
    
    vector<vector<Node>> shortestPaths;
    
    Heuristics heuristics;    
    vector<Node> selectedNode ;
    vector<Node> selectedNodes;

    Font font;
    font.loadFromFile("arial.ttf");
    
    vector<Node> start;
    vector<Node> end;
    
    while (window.isOpen()) {

        bool simpleSearch = false , multipleSearch = false;
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
                        //selectedNode = graph.getNodesByPoint(x,y);
                        if(start.empty()){
                            window.clear();
                            start = graph.getNodesByPoint(x,y);
                            Text text(to_string((start[0]).tag), font);
                            text.setCharacterSize(15);
                            //text.setStyle(Text::Bold);
                            text.setColor(Color::Red);
                            text.setPosition(start[0].x,start[0].y);
                            window.draw(text);

                        }else if(end.empty()){
                            end = graph.getNodesByPoint(x,y);
                            Text text(to_string((end[0]).tag), font);
                            text.setCharacterSize(15);
                            //text.setStyle(Text::Bold);
                            text.setColor(Color::Red);
                            text.setPosition(end[0].x,end[0].y);
                            window.draw(text);
                        }
                        simpleSearch = true;
                    }else if (event.mouseButton.button == Mouse::Right){
                        double x = event.mouseButton.x ;
                        x = (x*width)/(width+deltaWidth) ;
                        double y = event.mouseButton.y ;
                        y = (y*height)/(height+deltaHeight);
                        //cout << "x " << x << endl;
                        //cout << "y " << y << endl;
                        int radio = 30;
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
                        multipleSearch = true;
                    }
                    break;
                case Event::TextEntered :
                    if (event.text.unicode == 99 ){
                        window.clear();
                        start.clear();
                        end.clear();
                        shortestPaths.clear();
                        cout << "Clean ... "<< endl;
                    }
                default:
                    break;
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

        if(!start.empty() and !end.empty() ){
            if(simpleSearch){
                shortestPaths = sequentialSearch(graph,start,end);
            }else if(multipleSearch){
                shortestPaths = parallelSearch(graph,start,end);
            }
            selectedNode.clear();
            start.clear();
            end.clear();
        }

        //shortestPath
        if(!shortestPaths.empty()){
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