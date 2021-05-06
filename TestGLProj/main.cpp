#include <GL/glew.h>
#include <GL/freeglut.h>

//glm library
#include <glm/glm.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Shader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Shader shader; // loads our vertex and fragment shaders
Shader shader2;
Shader shader3;
Model* car;
Model* wheel1;
Model* platform1;
Model* platform2;
Model* platform3;
Model* platform4;
Model* platform5;
Model* platform6;
Model* platform7;
Model* platform8;
Model* platform9;
Model* platform10;
Model* platform11;
Model* startingLine;
float rot;
bool thirdPerson = false;
bool alt = true;
//Model *sphere;
glm::mat4 projection; // projection matrix
glm::mat4 view; // where the camera is looking
glm::mat4 model; // where the model (i.e., the myModel) is located wrt the camera
glm::mat4 model2;
glm::vec3 eye(-100.0f, 300.0f, 20.0f);
glm::vec3 center(-100.0f, 0.0f, 0.0f);
glm::vec3 eye1(-100.0f, 300.0f, 20.0f);
glm::vec3 center1(-100.0f, 0.0f, 0.0f);
glm::vec4 up(0.0f, 1.0f, 0.0f,0.0f);
glm::vec3 eye2(0.0f, 5.0f, 20.0f);
glm::vec3 center2(0.0f, 0.0f, 0.0f);
//Variables Added 5/6/21
glm::mat4 carTrans;
float rotation = 0.0f;
glm::vec4 move(0.0f, 0.0f, 15.0f, 1.0f);
glm::vec4 lookatdirection(0,0,-1,0);
float cameradistance = 20;
float cameraheight = 5;
//End
float angle = 0;
enum key_state { NOTPUSHED, PUSHED } keyarr[256];
//bool keyarr[256];
/* report GL errors, if any, to stderr */
void checkError(const char* functionName)
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cerr << "GL error " << error << " detected in " << functionName << std::endl;
	}
}

void initShader(void)
{
	shader.InitializeFromFile("shaders/phong.vert", "shaders/phong.frag");
	shader.AddAttribute("vertexPosition");
	shader.AddAttribute("vertexNormal");

	//green shading
	shader2.InitializeFromFile("shaders/phong.vert", "shaders/green.frag");
	shader2.AddAttribute("vertexPosition");
	shader2.AddAttribute("vertexNormal");

	//black shading
	shader3.InitializeFromFile("shaders/phong.vert", "shaders/black.frag");
	shader3.AddAttribute("vertexPosition");
	shader3.AddAttribute("vertexNormal");

	checkError("initShader");
}

void initRendering(void)
{
	glClearColor(0.117f, 0.565f, 1.0f, 0.0f); // Dodger Blue
	checkError("initRendering");
}

void init(void)
{
	// Perspective projection matrix.
	projection = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 1000.0f);


	// Load identity matrix into model matrix (no initial translation or rotation)


	initShader();
	initRendering();
}

/* This prints in the console when you start the program*/
void dumpInfo(void)
{
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	checkError("dumpInfo");
}

/*This gets called when the OpenGL is asked to display. This is where all the main rendering calls go*/
void display(void)
{
	if (thirdPerson) {
		eye = eye2;
		center = center2;
	}
	else {
		eye = eye1;
		center = center1;
	}
	//glm::rot
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// camera positioned at 20 on the z axis, looking into the screen down the -Z axis.
	//view = view * glm::translate(0.0f, -0.5f, -fpcPos) * glm::rotate(view, -fpcRotate, x2);
	view = glm::lookAt(glm::vec3(move - (glm::rotate(rotation, 0.0f, 1.0f, 0.0f) * lookatdirection * cameradistance) + glm::vec4(0.0f, cameraheight, 0.0f, 0.0f)), glm::vec3(move), glm::vec3(up));
	carTrans = glm::translate(glm::vec3(move)) * glm::rotate(rotation, 0.0f,1.0f, 0.0f);
	car->render(view * carTrans * glm::translate(0.0f, -2.0f, 00.0f) * glm::scale(1.5f, 2.5f, 1.0f), projection);

	startingLine->render(view * model2 * glm::translate(0.0f, -4.0f, -6.0f) * glm::scale(5.0f, 10.0f, 1.0f), projection);
	platform1->render(view * model2 * glm::translate(0.0f, -4.0f, 20.0f) * glm::scale(5.0f, 10.0f, 25.0f), projection);
	platform2->render(view * model2 * glm::translate(0.0f, -4.0f, -32.0f) * glm::scale(5.0f, 10.0f, 25.0f), projection);
	platform3->render(view * model2 * glm::translate(-45.0f, -4.0f, -55.0f) * glm::scale(50.0f, 10.0f, 5.0f), projection);
	platform4->render(view * model2 * glm::translate(-100.0f, -4.0f, -75.0f) * glm::scale(5.0f, 10.0f, 25.0f), projection);
	platform5->render(view * model2 * glm::translate(-120.0f, -4.0f, -100.0f) * glm::scale(25.0f, 10.0f, 5.0f), projection);
	platform6->render(view * model2 * glm::translate(-140.0f, -4.0f, -75.0f) * glm::scale(5.0f, 10.0f, 25.0f), projection);
	platform7->render(view * model2 * glm::translate(-190.0f, -4.0f, -55.0f) * glm::scale(50.0f, 10.0f, 5.0f), projection);
	platform8->render(view * model2 * glm::translate(-235.0f, -4.0f, 20.0f) * glm::scale(5.0f, 10.0f, 75.0f), projection);
	platform9->render(view * model2 * glm::translate(-160.0f, -4.0f, 90.0f) * glm::scale(75.0f, 10.0f, 5.0f), projection);
	platform10->render(view * model2 * glm::translate(-90.0f, -4.0f, 70.0f) * glm::scale(5.0f, 10.0f, 25.0f), projection);
	platform11->render(view * model2 * glm::translate(-40.0f, -4.0f, 50.0f) * glm::scale(45.0f, 10.0f, 5.0f), projection);

	//wheel1->render(view * glm::translate(0.0f, -2.0f, 0.0f) * glm::scale(1.5f, 2.5f, 1.0f) * glm::rotate(90.0f,0.0f,0.0f, 0.0f), projection);

	glutSwapBuffers(); // Swap the buffers.
	checkError("display");
}

/*This gets called when nothing is happening (OFTEN)*/
void idle()
{
	glutPostRedisplay(); // create a display event. Display calls as fast as CPU will allow when put in the idle function
}

/*Called when the window is resized*/
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	checkError("reshape");
}

/*Called when a normal key is pressed*/
void keyboard(unsigned char key, int x, int y)
{
	//glutIgnoreKeyRepeat(key);
	/*switch (key) {
	case 27: // this is an ascii value
		exit(0);
		break;
	case 99: // change camera
		if (thirdPerson) {
			thirdPerson = false;
		}
		else {
			thirdPerson = true;
		}
		break;
	}*/
	glm::vec4 lookatdir = glm::rotate(rotation, 0.0f, 1.0f, 0.0f) * lookatdirection;
	glm::vec4 x1 = glm::vec4(glm::normalize(glm::cross(glm::vec3(up), glm::vec3(lookatdir))), 0.0f);
	if (key == 't') 
		thirdPerson = true;
	if (key == 'b')
		thirdPerson = false;
	if (key == 'w') {
		/*
		model *= glm::translate(0.0f, 0.0f, -0.4f);
		eye2 += glm::vec3(0.0f, 0.0f, -0.4f);
		center2 += glm::vec3(0.0f, 0.0f, -0.4f);
		keyarr['w'] = PUSHED;
		*/
		move += lookatdir;
	}
	if (key == 'a') {
		//model *= glm::translate(0.0f, 0.0f, -0.4f);
		//model *= glm::rotate(2.0f, 0.0f, 1.0f, 0.0f) * glm::translate(0.0f, 0.0f, -0.4f);
		move += lookatdir;
		rotation += 5.0f;
		keyarr['a'] = PUSHED;
	}
	if (key == 'd') {
		//model *= glm::translate(0.0f, 0.0f, -0.4f);
		//model *= glm::rotate(-2.0f, 0.0f, 1.0f, 0.0f) * glm::translate(0.0f, 0.0f, -0.4f);
		rotation -= 5.0f;
		move += lookatdir;
		keyarr['d'] = PUSHED;
	}
	if (key == 's') {
		/*
		model *= glm::translate(0.0f, 0.0f, 0.4f);
		eye2 += glm::vec3(0.0f, 0.0f, 0.4f);
		center2 += glm::vec3(0.0f, 0.0f, 0.4f);
		*/
		move -= lookatdir;
		keyarr['s'] = PUSHED;
	}
	/*
	if (key == 'a' && key == 'w') {
		model *= glm::rotate(3.0f, 0.0f, 4.0f, 0.0f);
	}
	*/
}

void keyUp(unsigned char key, int x, int y) {
	if (key == 'a')
		keyarr['a'] = NOTPUSHED;
	if (key == 'w')
		keyarr['w'] = NOTPUSHED;

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glewInit();
	dumpInfo();
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard);
	//glutIgnoreKeyRepeat;
	glEnable(GL_DEPTH_TEST);
	car = new Model(&shader3, "models/dodge-challenger_model.obj", "models/");
	startingLine = new Model(&shader2, "models/plane.obj", "models/");
	platform1 = new Model(&shader, "models/plane.obj", "models/");
	platform2 = new Model(&shader, "models/plane.obj", "models/");
	platform3 = new Model(&shader, "models/plane.obj", "models/");
	platform4 = new Model(&shader, "models/plane.obj", "models/");
	platform5 = new Model(&shader, "models/plane.obj", "models/");
	platform6 = new Model(&shader, "models/plane.obj", "models/");
	platform7 = new Model(&shader, "models/plane.obj", "models/");
	platform8 = new Model(&shader, "models/plane.obj", "models/");
	platform9 = new Model(&shader, "models/plane.obj", "models/");
	platform10 = new Model(&shader, "models/plane.obj", "models/");
	platform11 = new Model(&shader, "models/plane.obj", "models/");
	//wheel1 = new Model(&shader, "models/wheel1.obj", "models/");
	glutMainLoop();

	return 0;
}






/*#include <GL/glew.h>
#include <GL/freeglut.h>

//glm library
#include <glm/glm.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Shader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Shader shader; // loads our vertex and fragment shaders
Model *bodyCylinder; //Body
Model *lArmCylinder; //Left Arm
Model *rArmCylinder; //Right Arm
Model* headCylinder; //Head
Model* lLegCylinder; //Left Leg
Model* rLegCylinder; //Right Leg
Model* sphere;
Model* plane;
glm::mat4 projection; // projection matrix
glm::mat4 view; // where the camera is looking
glm::mat4 empty;
glm::mat4 model; // where the model (i.e., the myModel) is located wrt the camera
glm::mat4 model3; // where the model (i.e., the myModel) is located wrt the camera
glm::vec3 move(0.0f, 0.0f, 20.0f);
glm::vec3 center(0.0f, 0.0f, 0.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);
glm::vec3 move2(0.0f, 1.8f, 1.0f);
glm::vec3 center2(0.0f, 1.8f, -1.0f);
glm::vec3 up2(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::mat4 inverted;
glm::vec3 forward;
float angle = 1;
float angle2 = -1;
float boyMove = 0.0f;
float boyRotate = 0.0f;
float cCenter = 0;
float cCenter2 = 0;
float cEye = 0;
float aLimit = 21;
float bLimit = -21;
float fpcPos;
float fpcRotate;
bool uPressed = false;
bool dPressed = false;
bool lPressed = false;
bool rPressed = false;
bool sForward = true;
bool fpc = false;

/* report GL errors, if any, to stderr 
void checkError(const char *functionName)
{
	GLenum error;
	while (( error = glGetError() ) != GL_NO_ERROR) {
		std::cerr << "GL error " << error << " detected in " << functionName << std::endl;
	}
}

void initShader(void)
{
	shader.InitializeFromFile("shaders/phong.vert", "shaders/phong.frag");
	shader.AddAttribute("vertexPosition");
	shader.AddAttribute("vertexNormal");

	checkError ("initShader");
}

void initRendering(void)
{
	glClearColor (0.117f, 0.565f, 1.0f, 0.0f); // Dodger Blue
	checkError ("initRendering");
}

void init(void) 
{	
	// Perspective projection matrix.
	projection = glm::perspective(45.0f, 800.0f/600.0f, 1.0f, 1000.0f);

	
	// Load identity matrix into model matrix (no initial translation or rotation)
	

	initShader ();
	initRendering ();
}

/* This prints in the console when you start the program
void dumpInfo(void)
{
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
	checkError ("dumpInfo");
}

/*This gets called when the OpenGL is asked to display. This is where all the main rendering calls go
void display(void)
{
	glm::vec3 x1 = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), center - move));
	glm::vec3 x2 = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::rot
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// camera positioned at 20 on the z axis, looking into the screen down the -Z axis.
	if (!fpc)
		view = glm::lookAt(move, center, up);
	else {
		view = empty;
		view = view * glm::translate(0.0f, -0.5f, -fpcPos) * glm::rotate(view, -fpcRotate, x2) ;
		//view = view * glm::translate(0.0f, -0.5f, fpcPos);
	}

	sphere->render(view * glm::translate(5.0f, 0.0f, -10.0f), projection);

	model = model * glm::translate(0.0f, 0.0f, boyMove);

	//model = glm::scale(2.0f, 3.0f, 2.0f);
	model = glm::rotate(model, boyRotate, x2);
	//model = model * glm::translate(0.0f, 0.0f, boyMove);

	/*model2 = glm::scale(2.0f, 3.0f, 2.0f);
	model3 = glm::scale(2.0f, 3.0f, 2.0f);
	model2 = glm::rotate(angle += 1, 0.0f, 0.0f, 1.0f); // Speed of rotation. 
	model3 = glm::rotate(angle += 1, 0.0f, 0.0f, 1.0f); // Speed of rotation.
	bodyCylinder->render(view * model, projection); // Render current active model
	// All is a child of Body

	if (!fpc)
		headCylinder->render(view * model * glm::translate(0.0f, 1.3f, 0.0f) * glm::scale(0.5f, 0.3f, 0.5f), projection);

	//model = model * glm::translate(0.0f, 1.0f, 0.0f);
	if (angle == aLimit)
		sForward = false;
	if (angle == bLimit)
		sForward = true;
	/*if (sForward)
		angle++;
	if (!sForward)
		angle--;*/
	/*model = model * glm::rotate(angle, 1.0f, 0.0f, 0.0f); // Speed of rotation
	model = model * glm::translate(0.0f, -1.0f, 0.0f);
	lArmCylinder->render(view * model * glm::translate(0.0f, 1.0f, 0.0f) * glm::rotate(angle, 1.0f, 0.0f, 0.0f) * glm::translate(0.0f, -1.0f, 0.0f) * glm::translate(-1.0f, -0.2f, 0.0f)* glm::scale(0.2f, 1.2f, 0.2f), projection);
	lLegCylinder->render(view * model * glm::translate(0.0f, -1.0f, 0.0f) * glm::rotate(angle, 1.0f, 0.0f, 0.0f) * glm::translate(0.0f, 1.0f, 0.0f) * glm::translate(-0.3f, -2.2f, 0.0f) * glm::scale(0.2f, 1.2f, 0.2f), projection);

	/*model = glm::scale(2.0f, 3.0f, 2.0f);
	model = model * glm::translate(0.0f, 0.0f, boyMove);
	model = model * glm::rotate(boyRotate, x2);
	inverted = glm::inverse(model);
	forward = glm::normalize(glm::vec3(inverted[2])) * glm::vec3(1, 1, -1);
	model = model * glm::translate(forward);

	model = model * glm::translate(0.0f, 0.0f, boyMove);

	//model = glm::scale(2.0f, 3.0f, 2.0f);
	model = glm::rotate(model, boyRotate, x2);

	//model = model * glm::translate(0.0f, 1.0f, 0.0f);
	/*if (sForward)
		angle2--;
	if (!sForward)
		angle2++;*/
	/*model = model * glm::rotate(angle2, 1.0f, 0.0f, 0.0f); // Speed of rotation
	model = model * glm::translate(0.0f, -1.0f, 0.0f);
	rArmCylinder->render(view * model * glm::translate(0.0f, 1.0f, 0.0f) * glm::rotate(angle2, 1.0f, 0.0f, 0.0f) * glm::translate(0.0f, -1.0f, 0.0f) * glm::translate(1.0f, -0.2f, 0.0f) * glm::scale(0.2f, 1.2f, 0.2f), projection);
	rLegCylinder->render(view * model * glm::translate(0.0f, -1.0f, 0.0f) * glm::rotate(angle2, 1.0f, 0.0f, 0.0f) * glm::translate(0.0f, 1.0f, 0.0f) * glm::translate(0.3f, -2.2f, 0.0f) * glm::scale(0.2f, 1.2f, 0.2f), projection);
	

	if (uPressed) {
		if (cCenter <= 45) {
			cCenter += 1;
			center = center + x2 * .25f;
		}
	}
	if (dPressed) {
		if (cCenter >= -45) {
			cCenter -= 1;
			center = center - x2 * .25f;
		}
	}
	if (lPressed) {
		center = center + x1 * .25f;
	}
	if (rPressed) {
		center = center + x1 * -.25f;
	}
	plane->render(view * glm::translate(0.0f,-5.0f,0.0f)*glm::scale(20.0f,1.0f,20.0f), projection);
	
	//fpcPos = boyMove;
	//fpcPos = 0;
	//fpcRotate = 0;
	boyRotate = 0;
	boyMove = 0;
	glutSwapBuffers(); // Swap the buffers.
	checkError ("display");
}

/*This gets called when nothing is happening (OFTEN)
void idle()
{
	glutPostRedisplay(); // create a display event. Display calls as fast as CPU will allow when put in the idle function
}

/*Called when the window is resized
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	checkError ("reshape");
}

/*Called when a normal key is pressed
void keyboard(unsigned char key, int x, int y)
{
	glm::vec3 x1 = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), center2 - move2));
	glm::vec3 x2 = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 lookatdir = glm::normalize(center - move);
	glm::vec3 lookatdir2 = glm::normalize(center2 - move2);
	switch (key) {
	case 27: // this is an ascii value
		exit(0);
		break;
	case 97: // a, rotate the boy left
		fpcRotate += 1;
		boyRotate += 1;
		break;
	case 99: // c, toggle First Person Camera
		if (fpc)
			fpc = false;
		else
			fpc = true;
		break;
	case 100: // d. rotate the boy right
		fpcRotate -= 1;
		boyRotate -= 1;
		break;
	case 102: // f, forward
		move += lookatdir;
		center += lookatdir;
		break;
	case 115: // s, move the boy backwards
		fpcPos += 0.2f;
		aLimit = -21;
		bLimit = 21;
		boyMove += 0.1f;
		if (sForward)
			angle--;
		if (!sForward)
			angle++;
		if (sForward)
			angle2++;
		if (!sForward)
			angle2--;
		break;
	case 118: // v, backwards
		move -= lookatdir;
		center -= lookatdir;
		break;
	case 119: // w, walk the boy forward
		fpcPos -= 0.2f;
		aLimit = 21;
		bLimit = -21;
		boyMove -= 0.1f;
		if (sForward)
			angle++;
		if (!sForward)
			angle--;
		if (sForward)
			angle2--;
		if (!sForward)
			angle2++;
		break;
	}
}

void keyHold(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		uPressed = true;
	if (key == GLUT_KEY_DOWN)
		dPressed = true;
	if (key == GLUT_KEY_LEFT)
		lPressed = true;
	if (key == GLUT_KEY_RIGHT)
		rPressed = true;
}

void keyRelease(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		uPressed = false;
	if (key == GLUT_KEY_DOWN)
		dPressed = false;
	if (key == GLUT_KEY_LEFT)
		lPressed = false;
	if (key == GLUT_KEY_RIGHT)
		rPressed = false;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (800, 600); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	glewInit();
	dumpInfo ();
	init ();
	glutDisplayFunc(display); 
	glutIdleFunc(idle); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc(keyHold);
	glutSpecialUpFunc(keyRelease);
	glEnable(GL_DEPTH_TEST);

	
	bodyCylinder = new Model(&shader, "models/cylinder.obj");
	headCylinder = new Model(&shader, "models/cylinder.obj");
	rArmCylinder = new Model(&shader, "models/cylinder.obj");
	lArmCylinder = new Model(&shader, "models/cylinder.obj");
	rLegCylinder = new Model(&shader, "models/cylinder.obj");
	lLegCylinder = new Model(&shader, "models/cylinder.obj");
	plane = new Model(&shader, "models/plane.obj");
	sphere = new Model(&shader, "models/dodge-challenger_model.obj", "models/"); // you must specify the material path for this to load
	

	glutMainLoop();

	return 0;
}*/