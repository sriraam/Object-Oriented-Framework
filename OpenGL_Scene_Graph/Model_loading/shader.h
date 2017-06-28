#pragma once


//#pragma comment (lib, "glew32s.lib")
//#define GLEW_STATIC
#include <GL/glew.h>
#include<GL/freeglut.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class shader
{
public:
	GLuint program;
	//shader();
	void loadshader(const std::string&, const std::string&);
	void Use();

	~shader() {
	}
};

