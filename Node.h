#pragma once

class Node 
{
    
    public:
        Node();
        Node(double x , double y, int tag);
        double getX(int scale,int translate);
        double getY(int scale,int translate);
        bool compare(Node node);
        ~Node();

    public : 
            double x ,y , f,g,h;
            int tag ; 
    
};