#ifndef SCENE_H
#define SCENE_H

#endif

#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include<gl/glew.h>


#include<GL/freeglut.h>
//#include<iostream>
#include<glm/glm.hpp>
#include<glm/ext.hpp>
//#include<fstream>
#include<vector>
//#include<string>
#include"shader.h"
#include"camera.h"

//#include "off_io.h"

class scene
{
public:
	scene();
	~scene();
	static scene *instance;
	shader shader_main;
	shader shader_light;
	GLuint VertexArrayID;
	GLuint lightVAO;
	GLuint normalVAO;

	


	glm::mat4 View, Model, Projection;

	GLint modelLoc, viewLoc, projLoc;

	GLuint lightcolor_loc, materialcolor_loc;
	GLuint lightposLoc;
	GLint viewPosLoc;
	GLint specBoolLoc;
	GLint diffBoolLoc;
	GLint ambientBoolLoc;
	GLuint MatrixID;
	glm::mat4 mvp;

	GLuint VertexBuffer;
	GLuint VertexBuffer2;
	//GLuint normalBuffer;
	//GLuint modelBuffer;
	//GLuint elementbuffer;

	bool spec_bool;
	bool diff_bool;
	bool ambient_bool;


	//GLuint g_ShaderProgram = 0;
	//glGenVertexArrays(1, &VertexArrayID);

	bool use_normals ;
	// Camera Position
	

	// Mouse Tracking Variables
	int startX, startY, tracking ;



	// Light attributes
	glm::vec3 lightPos;

	 void display1();
	 void init();
	 void setInstance();
	 static void displaywrapper();
	 static void mousebuttonwrapper(int,int,int,int);
	 static void mousemotionwrapper(int,int);
	 void processKeys(unsigned char, int, int);
	 void processMouseButtons(int, int, int, int);
	 void processMouseMotion(int xx, int yy);
	 int run(int argc, char** argv);
};

