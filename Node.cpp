#include "Node.h"

Node::Node(){
            this->x = 0;
            this->y = 0;
            this->tag = 0;
        }

Node::Node(double x , double y, int tag){
            this->x = x;
            this->y = y;
            this->tag = tag;
        }

bool Node::compare(Node node){
	return this->x == node.x and this->y == node.y;
}

Node::~Node(){};
