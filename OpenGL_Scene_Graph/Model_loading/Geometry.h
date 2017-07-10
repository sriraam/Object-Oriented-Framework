#pragma comment (lib, "glew32s.lib")
#define GLEW_STATIC
#include<gl/glew.h>

#include<GL/freeglut.h>
#include"off_io.h"
#include"Node.h"
class Geometry:public Node
{
public:
	//GLfloat pNormals[];
	LoadData mod_data;
	graphicData model;
	string model_name;
	GLuint VertexArrayID;
	GLuint VertexBufferObj;
	GLuint normalBuffer;
	GLuint modelBuffer;
	GLuint elementbuffer;
	void accept(Visitor &v);
	void create_vao();
	void draw();
	void set_model(string);
	Geometry();
	~Geometry();
};

