#include "Transform_node.h"



Transform_node::Transform_node()
{
	Model = glm::mat4();
}

glm::mat4 Transform_node::getModel() {

	return Model;
}
void Transform_node::accept(Visitor &v) {
	v.visit(this);
}
Transform_node::~Transform_node()
{
}
