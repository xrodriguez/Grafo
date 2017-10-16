#include "Node.h"
# define INF 0x3f3f3f3f

Node::Node(){
            this->x = 0;
            this->y = 0;
            this->tag = 0;
        }

Node::Node(double x , double y, int tag){
            this->x = x;
            this->y = y;
            this->tag = tag;
            this->f = INF;//0;
            this->g = INF;//0;
        }


double Node::getX(int scale,int translate){
    return this->x ;//(this->x/scale)+translate;
}

double Node::getY(int scale,int translate){
    return this->y ;//(this->y/scale)+translate;
}


bool Node::compare(Node node){
	return this->x == node.x and this->y == node.y;
}

Node::~Node(){};
