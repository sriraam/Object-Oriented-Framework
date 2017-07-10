#pragma once
#include<glm/glm.hpp>
#include<glm/ext.hpp>
class camera
{
public:
	glm::mat4 View,Projection;
	float camX, camY, camZ;
	// Camera Spherical Coordinates
	float alpha, beta;
	float r;

	
	void camera_init();
	camera();
	~camera();
};

