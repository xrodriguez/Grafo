#pragma once


#include "Node.h"

class Edge
{

    public : Node *start;
         Node *end;
         double weight ;
	public:
		Edge(Node *start , Node *end );
		~Edge();
	
};