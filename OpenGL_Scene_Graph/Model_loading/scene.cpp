#include "scene.h"


scene* scene::instance = NULL;
void scene::display1()
{
	// Camera matrix
	
	//glUseProgram(g_ShaderProgram);
	//shader_main.Use();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	shader_light.Use();


	modelLoc = glGetUniformLocation(shader_light.program, "model");
	viewLoc = glGetUniformLocation(shader_light.program, "view");
	projLoc = glGetUniformLocation(shader_light.program, "projection");

	specBoolLoc = glGetUniformLocation(shader_light.program, "specBool");
	diffBoolLoc = glGetUniformLocation(shader_light.program, "diffBool");
	ambientBoolLoc = glGetUniformLocation(shader_light.program, "ambientBool");

	lightcolor_loc = glGetUniformLocation(shader_light.program, "lightColor");
	materialcolor_loc = glGetUniformLocation(shader_light.program, "materialcolor");
	lightposLoc = glGetUniformLocation(shader_light.program, "lightPos");
	viewPosLoc = glGetUniformLocation(shader_main.program, "viewPos");

	//glUniform3f(viewPosLoc, 5.25 * sin(40 * 3.14f / 180.0f) * cos(45 * 3.14f / 180.0f), 5.25 * cos(40 * 3.14f / 180.0f) * cos(45 * 3.14f / 180.0f), 5.25*sin(45 * 3.14f / 180.0f));
	glUniform3f(viewPosLoc, camX, camY, camZ);

	// Set matrices
	// Camera matrix
	//View = glm::lookAt(
	//	glm::vec3(5.25 * sin(40 * 3.14f / 180.0f) * cos(45 * 3.14f / 180.0f), 5.25 * cos(40 * 3.14f / 180.0f) * cos(45 * 3.14f / 180.0f), 5.25*sin(45 * 3.14f / 180.0f)), // Camera is at (4,3,3), in World Space
	//	glm::vec3(0, 0, 0), // and looks at the origin
	//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	//	);
	glUniform3f(lightcolor_loc, 1, 1, 1);
	glUniform3f(materialcolor_loc, 1.0, .3, .3);
	glUniform3f(lightposLoc, lightPos.x, lightPos.y, lightPos.z);
	

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(scene::View));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(Projection));
	Model = glm::mat4();
	//	Model = glm::translate(Model, lightPos);
	Model = glm::scale(Model, glm::vec3(.5f)); // Make it a smaller cube
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Model));
	if (spec_bool) {
		glUniform3f(specBoolLoc, 1.0, 1.0, 1.0);
	}
	else {
		glUniform3f(specBoolLoc, 0.0, 0.0, 0.0);
	}
	if (diff_bool) {
		glUniform3f(diffBoolLoc, 1.0, 1.0, 1.0);
	}
	else {
		glUniform3f(diffBoolLoc, 0.0, 0.0, 0.0);
	}

	if (ambient_bool) {
		glUniform3f(ambientBoolLoc, 1.0, 1.0, 1.0);
	}
	else {
		glUniform3f(ambientBoolLoc, 0.0, 0.0, 0.0);
	}


	// Draw the light object (using light's vertex attributes)
	//glBindVertexArray(normalVAO);
	glBindVertexArray(lightVAO);
	//glDrawArrays(GL_POINTS, 0, model.nVertices);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(GL_TRIANGLES, model.nTris * 3, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);

	glutSwapBuffers();
}


void scene::init() {

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


	//**it is used above all many vertex||color bind,databuffer and used this VetexarrayID at display func 
	//**where we use shader object and drawarray or element

	/*//**LOADING THE .off model file 
	off_io off_loader;

	ifstream inFile("cube1.off", ios::in);
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
	*/

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &VertexBuffer);
	//glGenBuffers(1, &normalBuffer);
	//glGenBuffers(1, &modelBuffer);

       

	

	// some GL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//Not neccessary to be written inside init(),usually written in main()

	//So we need three 3D points in order to make a triangle
	static const GLfloat g_Vertex_Buffer_data[] = {
		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f,
	};


	//LoadData ld;
	std::cout << "CHECK for vert 1 from model" << mod_data.verts[1];

	model.nVertices = mod_data.verts.size();
	model.pVertices = new GLfloat[mod_data.verts.size() * 3];
	model.pNormals = new GLfloat[mod_data.vertnormal.size() * 3];
	//GLfloat *model_ver = new GLfloat[mod_data.size()*3];

	for (int i = 0; i < model.nVertices; i++) {
		for (int j = 0; j < 3; j++)
			model.pVertices[i * 3 + j] = mod_data.verts[i][j];
	}
	model.nTris = mod_data.tris.size();
	model.pIndices = new GLuint[mod_data.tris.size() * 3];

	//std::cout << "first INDICES is" << mod_data.tris[model.nTris-1][0]<<"\n";
	for (int i = 0; i < model.nTris; i++) {
		for (int j = 0; j < 3; j++) {
			model.pIndices[i * 3 + j] = mod_data.tris[i][j];

		}
	}

	for (int i = 0; i < model.nVertices; i++) {
		for (int j = 0; j < 3; j++) {
			model.pNormals[i * 3 + j] = mod_data.vertnormal[i][j];
		}
	}

	//std::cout << "list of vertNormal is\n";
	//	std::cout << model.nVertices << "\n";
	//std::cout << mod_data.vertnormal.size() << "\n";
	//std::cout << mod_data.vertnormal[0] << "\n";
	//for (int i = 0; i < model.nTris;i++) {
	//	std::cout << model.pIndices[i ]<<"\n";

	//}
	std::cout << "No. of indices is :" << model.nTris;
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {



		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,


		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,


		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,


		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,



		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};


	//why we are usig this ? 
	//need to create a Vertex Array Object 
	//glGenVertexArrays(1, &normalVAO);
	//glGenVertexArrays(1, &VertexArrayID);

	/*
	glBindVertexArray(VertexArrayID);

	//bind & data comes together//not compulsory..
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	*/
	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
/*
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

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
	


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.nTris * sizeof(GLuint) * 3, model.pIndices, GL_STATIC_DRAW);



	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	 */
	//glDisableVertexArrayAttrib(1);
	//glDisableVertexArrayAttrib(0);
	/*glBindVertexArray(normalVAO);

	glBindBuffer(GL_ARRAY_BUFFER,normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*model.nVertices*3,model.pNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	*/

	//second vertex buffer for inverted triangle
	//how to display them

                  

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates



	// Model matrix : an identity matrix (model will be at the origin)
	Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around



}
//void runMainLoop(int val) {
//	display1();
//	glutTimerFunc(1000 / 60, runMainLoop, 0);
//}

void scene::processKeys(unsigned char key, int xx, int yy)
{
	switch (key) {

	case 27:
		glutLeaveMainLoop();
		break;

	case 'c':
		printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
		break;
	case'e':
		spec_bool = !spec_bool;
		break;
	case'w':
		diff_bool = !diff_bool;
		break;
	case'q':
		ambient_bool = !ambient_bool;
		break;

	}

	//  uncomment this if not using an idle func
	glutPostRedisplay();
}
// Mouse Events
//

void scene::processMouseButtons(int button, int state, int xx, int yy)
{
	// start tracking the mouse
	if (state == GLUT_DOWN) {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}

	//stop tracking the mouse
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha -= (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			r += (yy - startY) * 0.01f;
			if (r < 0.1f)
				r = 0.1f;
		}
		tracking = 0;
	}
}

// Track mouse motion while buttons are pressed

void scene::processMouseMotion(int xx, int yy)
{

	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX = -xx + startX;
	deltaY = yy - startY;

	// left mouse button: move camera
	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0f)
			betaAux = 85.0f;
		else if (betaAux < -85.0f)
			betaAux = -85.0f;
		rAux = r;
	}
	// right mouse button: zoom
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r + (deltaY * 0.01f);
		if (rAux < 0.1f)
			rAux = 0.1f;
	}



	camX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camY = rAux *   					  	       sin(betaAux * 3.14f / 180.0f);

	//  uncomment this if not using an idle func
	glutPostRedisplay();
}

void scene::setInstance() {
	std::cout << "GlutFramework::setInstance()" << std::endl;
	instance = this;
}


void scene::displaywrapper() {
	instance->display1();
}

void scene::mousemotionwrapper(int x,int y) {
	instance->processMouseMotion(x,y);
}

void scene::mousebuttonwrapper(int but,int state,int x, int y) {
	instance->processMouseButtons(but,state,x,y);
}


int scene::run(int argc, char** argv)
{

	setInstance();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("simple rectangle");


	glewExperimental = true; // Needed in core profile

	

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	//shader shader_main;
	//	shader_main.loadshader("vertexshader.vert", "fragmentshader.frag");
	shader_light.loadshader("ver_model.vert", "frag_model.frag");
	//shader_norm.loadshader("ver_normal.vert", "frag_normal.frag");
	init();
	// glEnable(GL_DEPTH_TEST);
	//load shaders
	//GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, "vertexshader.vert");
	//GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, "fragmentshader.frag");



	//std::vector<GLuint> shaders;
	//shaders.push_back(vertexShader);
	//shaders.push_back(fragmentShader);

	// Create the shader program.
	//g_ShaderProgram = CreateShaderProgram(shaders);
	//assert(g_ShaderProgram != 0);

	

	glutDisplayFunc(displaywrapper);

	glutMouseFunc(mousebuttonwrapper);
	glutMotionFunc(mousemotionwrapper);

	//	glutMouseWheelFunc(mouseWheel);
	//	return from main loop
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//MatrixID = glGetUniformLocation(shader_main.program, "MVP");

	//glutIdleFunc(display1);
	glutMainLoop();

	//glutTimerFunc(1000 / 60, runMainLoop, 0);

	

}


scene::scene()
{

	 spec_bool = true;
	 diff_bool = true;
	 ambient_bool = true;

	 use_normals = false;

	// Mouse Tracking Variables
	 tracking = 0;

	// Camera Spherical Coordinates
	 alpha = 40.0f; beta = 45.0f;
	 r = 5.25f;

	// Light attributes
	 lightPos =	glm::vec3 (1.5f, 2.0f, 1.3f);
}


scene::~scene()
{

}
