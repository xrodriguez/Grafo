#pragma once

class Node 
{
    
    public:
        Node();
        Node(double x , double y, int tag);
        bool compare(Node node);
        ~Node();

    public : 
            double x ,y , f,g,h;
            int tag ; 
    
};