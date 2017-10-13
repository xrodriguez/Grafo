#include "Edge.h"
#include "Node.h"
#include <math.h>


Edge::Edge(Node *start , Node *end ){
        this->start = start;
        this->end = end;
        this->weight = sqrt(pow(start->x-end->x,2)+pow(start->y-end->y,2));
    }
Edge::~Edge(){};
