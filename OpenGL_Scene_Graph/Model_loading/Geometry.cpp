#include "Geometry.h"


void Geometry::accept(Visitor &v) {
	v.visit(this);
}


Geometry::Geometry()
{
	off_io off_loader;

	ifstream inFile("model_name", ios::in);
	if (inFile.bad()) {
		cout << "File error" << endl;
		return;
	}

	if (!off_loader.Load(inFile, &mod_data)) {
		std::cout << "OFF File is not loaded";
	}
	else {
		std::cout << "OFF File is loaded successfully";

	}

	create_vao();
}

void Geometry::create_vao() {

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &normalBuffer);
	glGenBuffers(1, &modelBuffer);
	glGenBuffers(1, &elementbuffer);


	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*model.nVertices * 3, model.pNormals, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);


	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*model.nVertices * 3, model.pVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the normal vectors
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.nTris * sizeof(GLuint) * 3, model.pIndices, GL_STATIC_DRAW);



	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Geometry::draw() {
	glBindVertexArray(VertexArrayID);
	glDrawElements(GL_TRIANGLES, model.nTris * 3, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void Geometry::set_model(string name="cube1.off") {
	model_name = name;
}

Geometry::~Geometry()
{
}
