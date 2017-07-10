#pragma once
#include<glm/glm.hpp>
#include<glm/ext.hpp>
#include "Group_node.h"

class Transform_node: public Group_node
{
public:
	void accept(Visitor &v);
	glm::mat4 getModel();
	glm::mat4 Model;
	Transform_node();
	~Transform_node();
};

