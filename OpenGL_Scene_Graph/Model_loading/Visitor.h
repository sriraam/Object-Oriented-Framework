#pragma once
#include"Geometry.h"
#include"Transform_node.h"
class Visitor
{
public:
	Visitor();
	virtual void visit(Geometry *e) = 0;
	virtual void visit(Transform_node *e) = 0;
	virtual void visit(Group_node *e) = 0;
	~Visitor();
};

