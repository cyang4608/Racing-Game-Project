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
Model *car;
Model* wheel1;
float rot;
bool firstPerson = true;
bool alt = true;
//Model *sphere;
glm::mat4 projection; // projection matrix
glm::mat4 view; // where the camera is looking
glm::mat4 model; // where the model (i.e., the myModel) is located wrt the camera
float angle = 0;
enum key_state { NOTPUSHED, PUSHED } keyarr[256];
//bool keyarr[256];
/* report GL errors, if any, to stderr */
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

/* This prints in the console when you start the program*/
void dumpInfo(void)
{
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
	checkError ("dumpInfo");
}

/*This gets called when the OpenGL is asked to display. This is where all the main rendering calls go*/
void display(void)
{

	//glm::rot
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// camera positioned at 20 on the z axis, looking into the screen down the -Z axis.
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	car->render(view * model * glm::translate(0.0f, -2.0f, 0.0f) * glm::scale(1.5f, 2.5f, 1.0f), projection);
	//wheel1->render(view * glm::translate(0.0f, -2.0f, 0.0f) * glm::scale(1.5f, 2.5f, 1.0f) * glm::rotate(90.0f,0.0f,0.0f, 0.0f), projection);
	
	glutSwapBuffers(); // Swap the buffers.
	checkError ("display");
}

/*This gets called when nothing is happening (OFTEN)*/
void idle()
{
	glutPostRedisplay(); // create a display event. Display calls as fast as CPU will allow when put in the idle function
}

/*Called when the window is resized*/
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	checkError ("reshape");
}

/*Called when a normal key is pressed*/
void keyboard(unsigned char key, int x, int y)
{
	//glutIgnoreKeyRepeat(key);
	if (key == 'w') {
		model *= glm::translate(0.0f, 0.0f, -0.4f);
		keyarr['w'] = PUSHED;
	}
	if (key == 'a') {
		//model *= glm::translate(0.0f, 0.0f, -0.4f);
		model *= glm::rotate(2.0f, 0.0f, 1.0f, 0.0f) * glm::translate(0.0f, 0.0f, -0.4f);
		keyarr['a'] = PUSHED;
	}
	if (key == 'd') {
		//model *= glm::translate(0.0f, 0.0f, -0.4f);
		model *= glm::rotate(-2.0f, 0.0f, 1.0f, 0.0f) * glm::translate(0.0f, 0.0f, -0.4f);
		keyarr['d'] = PUSHED;
	}
	if (key == 's') {
		model *= glm::translate(0.0f, 0.0f, 0.4f);
		keyarr['s'] = PUSHED;
	}
	/*
	if (key == 'a' && key == 'w') {
		model *= glm::rotate(3.0f, 0.0f, 4.0f, 0.0f);
	}
	*/
	/*
	switch (key) {
	case 27: // this is an ascii value
		exit(0);
		break;

	case 'a':
		//walk forward
		keyarr[int('a')] = PUSHED;
		model *= glm::rotate(2.0f, 0.0f, 1.0f, 0.0f);
		break;
	case 'w':
		keyarr[int('w')] = PUSHED;
		model *= glm::translate(0.0f, 0.0f, -0.4f);
		break;

	case 's':
		//walk backward
		model *= glm::translate(0.0f, 0.0f, 0.4f);
		break;
		switch (key) {
			case 'a':
				model *= glm::translate(-0.5f, 0.0f, 0.0f);
				break;
			case 'd':
				model *= glm::translate(0.5f, 0.0f, 0.0f);
				break;
		}
	case 'c':
		//change camera angle
		if (firstPerson) {
			!sphere;
			firstPerson = false;
			//glm::lookAt(glm::vec3(model,0.0f,0.0f), glm::vec3(0.0f,model,0.0f), glm::vec3(0.0f,0.0f,model));
		}
		else {
			if (key == GLUT_KEY_LEFT) {
				//turn left
				printf("Left arrow");
				view *= glm::rotate(90.0f, 0.0f, 1.0f,0.0f);
			}else if (key == GLUT_KEY_RIGHT) {
				//turn right
				view *= glm::rotate(90.0f, 0.0f, -1.0f, 0.0f);
			}else if (key == GLUT_KEY_UP) {
				//look up 45 degrees
				view *= glm::rotate(45.0f, 1.0f, 0.0f, 0.0f);
			}else if (key == GLUT_KEY_DOWN) {
				//look down 45 degrees
				view *= glm::rotate(45.0f, -1.0f, 0.0f, 0.0f);
			}
			firstPerson = true;
		}
		break;
	case 'f':
		//move forward in direction camera is looking
		if (!firstPerson) {
			view *= glm::translate(0.0f, 1.0f,0.0f);
		}
		break;
	case 'v':
		//move backwards in direction camera is looking
		if (!firstPerson) {
			view *= glm::translate(0.0f, -1.0f, 0.0f);
		}
		break;
	}
	*/
	glutPostRedisplay();
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
	glutKeyboardUpFunc(keyboard);
	//glutIgnoreKeyRepeat;
	glEnable(GL_DEPTH_TEST);
	car = new Model(&shader, "models/dodge-challenger_model.obj", "models/");
	//wheel1 = new Model(&shader, "models/wheel1.obj", "models/");
	glutMainLoop();

	return 0;
}