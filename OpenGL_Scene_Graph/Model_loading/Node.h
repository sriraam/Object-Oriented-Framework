#pragma once
#include "Visitor.h"

class Node
{
public:
	virtual void accept(Visitor &v) = 0;

	Node();
	~Node();
};

