#include "Group_node.h"



Group_node::Group_node()
{

}
void Group_node::accept(Visitor &v) {
	v.visit(this);
}

Group_node::~Group_node()
{
}
