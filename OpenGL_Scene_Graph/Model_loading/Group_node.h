#pragma once
#include"Node.h"
class Group_node:Node
{
public:
	Group_node();
	void accept(Visitor &v);
	~Group_node();
};

