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

Shader shaderWhite; // loads our vertex and fragment shaders
Shader shaderGreen;
Shader shaderBlack;
Shader shaderYellow;
Shader shaderRed;
Shader shaderBlue;
Shader shaderBrown;
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
Model* bleachers;
Model* startingLine;
Model* field;
Model* tree;
Model* tree2;
Model* tree3;
Model* tree4;
Model* tree5;
Model* tree6;
Model* racebanner;
Model* line;
Model* line2;
Model* line3;
Model* line4;
Model* line5;
Model* line6;
Model* line7;
Model* line8;
Model* line9;
Model* line10;
Model* line11;
Model* line12;
Model* line13;
Model* line14;
Model* building;
Model* tube;
Model* arrow;
Model* billboard;
Model* ring;
Model* billboard2;
Model* text;
Model* text2;
Model* pressbox;
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
float turning = 0.0;
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
	shaderWhite.InitializeFromFile("shaders/phong.vert", "shaders/phong.frag");
	shaderWhite.AddAttribute("vertexPosition");
	shaderWhite.AddAttribute("vertexNormal");

	//green shading
	shaderGreen.InitializeFromFile("shaders/phong.vert", "shaders/green.frag");
	shaderGreen.AddAttribute("vertexPosition");
	shaderGreen.AddAttribute("vertexNormal");

	//black shading
	shaderBlack.InitializeFromFile("shaders/phong.vert", "shaders/black.frag");
	shaderBlack.AddAttribute("vertexPosition");
	shaderBlack.AddAttribute("vertexNormal");

	//yellow shading
	shaderYellow.InitializeFromFile("shaders/phong.vert", "shaders/yellow.frag");
	shaderYellow.AddAttribute("vertexPosition");
	shaderYellow.AddAttribute("vertexNormal");
	
	//red
	shaderRed.InitializeFromFile("shaders/phong.vert", "shaders/red.frag");
	shaderRed.AddAttribute("vertexPosition");
	shaderRed.AddAttribute("vertexNormal");
	checkError("initShader");

	shaderBlue.InitializeFromFile("shaders/phong.vert", "shaders/blue.frag");
	shaderBlue.AddAttribute("vertexPosition");
	shaderBlue.AddAttribute("vertexNormal");
	checkError("initShader");

	shaderBrown.InitializeFromFile("shaders/phong.vert", "shaders/brown.frag");
	shaderBrown.AddAttribute("vertexPosition");
	shaderBrown.AddAttribute("vertexNormal");
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
	view = glm::lookAt(glm::vec3(move - (glm::rotate(rotation, 0.0f, 1.0f, 0.0f) * lookatdirection * cameradistance) + glm::vec4(0.0f, cameraheight, 0.0f, 0.0f)), glm::vec3(move), glm::vec3(up));
	carTrans = glm::translate(glm::vec3(move)) * glm::rotate(rotation + turning, 0.0f, 1.0f, 0.0f);
	car->render(view * carTrans * glm::translate(0.0f, -2.0f, 00.0f) * glm::scale(1.5f, 2.5f, 1.0f), projection);

	startingLine->render(view * model2 * glm::translate(0.0f, -4.0f, -6.0f) * glm::scale(5.0f, 10.0f, 1.0f), projection);
	bleachers->render(view * model2 * glm::translate(13.0f, -4.0f, 6.0f) * glm::rotate(90.0f,0.0f,1.0f,0.0f), projection);
	pressbox->render(view * model2 * glm::translate(-33.0f, -4.0f, 6.0f) * glm::scale(2.8f, 2.8f, 2.8f), projection);
	tree->render(view * model2 * glm::translate(-20.0f, -4.0f, 40.0f) *glm::scale(1.5f,1.5f,1.5f), projection);
	tree2->render(view * model2 * glm::translate(-35.0f, -4.0f, 40.0f) * glm::scale(1.5f, 1.5f, 1.5f), projection);
	tree3->render(view * model2 * glm::translate(-20.0f, -4.0f, 60.0f) * glm::scale(1.5f, 1.5f, 1.5f), projection);
	tree4->render(view * model2 * glm::translate(-35.0f, -4.0f, 60.0f) * glm::scale(1.5f, 1.5f, 1.5f), projection);
	tree5->render(view * model2 * glm::translate(-50.0f, -4.0f, 40.0f) * glm::scale(1.5f, 1.5f, 1.5f), projection);
	tree6->render(view * model2 * glm::translate(-50.0f, -4.0f, 60.0f) * glm::scale(1.5f, 1.5f, 1.5f), projection);
	field->render(view * model2 * glm::translate(0.0f, -5.0f, -7.0f) * glm::scale(300.0f, 1.0f, 200.0f), projection);

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

	racebanner->render(view * model2 * glm::translate(5.5f, 0.0f, -5.0f) * glm::rotate(90.0f,0.0f,1.0f,0.0f)* glm::scale(1.2f, 1.2f, 1.2f), projection);
	line->render(view * model2 * glm::translate(0.0f, -3.9f, -16.0f) * glm::rotate(90.0f,0.0f,1.0f,0.0f) * glm::scale(2.0f,2.0f,2.0f), projection);
	line2->render(view * model2 * glm::translate(-40.0f, -3.9f, -55.0f) * glm::rotate(180.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line3->render(view * model2 * glm::translate(-200.0f, -3.9f, -55.0f) * glm::rotate(180.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line4->render(view * model2 * glm::translate(-100.0f, -3.9f, -65.0f) * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line5->render(view * model2 * glm::translate(-140.0f, -3.9f, -65.0f) * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line6->render(view * model2 * glm::translate(-200.0f, -3.9f, 90.0f) * glm::rotate(0.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line7->render(view * model2 * glm::translate(-140.0f, -3.9f, 90.0f) * glm::rotate(0.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line8->render(view * model2 * glm::translate(-235.0f, -3.9f, 70.0f) * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line9->render(view * model2 * glm::translate(-235.0f, -3.9f, -10.0f) * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line10->render(view * model2 * glm::translate(-132.0f, -3.9f, -100.0f) * glm::rotate(0.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line11->render(view * model2 * glm::translate(0.0f, -3.9f, 36.0f) * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line12->render(view * model2 * glm::translate(-40.0f, -3.9f, 50.0f) * glm::rotate(0.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line13->render(view * model2 * glm::translate(-90.0f, -3.9f, 80.0f) * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);
	line14->render(view * model2 * glm::translate(-180.0f, -3.9f, -55.0f) * glm::rotate(0.0f, 0.0f, 1.0f, 0.0f) * glm::scale(2.0f, 2.0f, 2.0f), projection);

	building->render(view * model2 * glm::translate(-130.0f, -4.0f, -6.0f) * glm::scale(5.0f,5.0f,5.0f), projection);
	tube->render(view * model2 * glm::translate(-235.0f, -4.0f, 20.0f) * glm::rotate(90.0f, 0.0f, 1.0f, 0.0f) * glm::scale(8.0f, 8.0f, 8.0f), projection);
	arrow->render(view * model2 * glm::translate(0.0f, 0.0f,-65.0f) * glm::rotate(90.0f,0.0f,1.0f,0.0f) *glm::rotate(-90.0f, 1.0f,0.0f,0.0f), projection);
	billboard->render(view * model2 * glm::translate(-125.0f, -4.0f, -55.0f) * glm::scale(5.0f, 5.0f, 5.0f), projection);
	ring->render(view * model2 * glm::translate(-160.0f, -4.0f, 97.0f) * glm::scale(3.0f, 3.0f, 3.0f), projection);
	billboard2->render(view * model2 * glm::translate(-65.0f, -4.0f, 87.0f) * glm::rotate(180.0f, 0.0f,1.0f,0.0f) * glm::scale(5.0f, 5.0f, 5.0f), projection);
	text->render(view * model2 * glm::translate(-125.0f, 2.0f, -55.0f) * glm::scale(5.0f, 5.0f, 5.0f), projection);
	text2->render(view * model2 * glm::translate(-65.0f, 2.0f, 87.0f) * glm::rotate(180.0f, 0.0f, 1.0f, 0.0f) * glm::scale(5.0f, 5.0f, 5.0f), projection);

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

	glm::vec4 lookatdir = glm::rotate(rotation, 0.0f, 1.0f, 0.0f) * lookatdirection;

	//esc to quit application
	if (key == 27)
	{
		exit(0);
	}
	if (key == 't') 
		thirdPerson = true;
	if (key == 'b')
		thirdPerson = false;
	if (key == 'w') {
		turning = 0;
		move += lookatdir;
		keyarr['w'] = PUSHED;
	}
	if (key == 'a') {

		turning = 10;
		move += lookatdir;
		rotation += 5.0f;
		keyarr['a'] = PUSHED;
	}
	if (key == 'd') {


		turning = -10;
		rotation -= 5.0f;
		move += lookatdir;
		keyarr['d'] = PUSHED;
	}
	if (key == 's') {

		turning = 0;
		move -= lookatdir;
		keyarr['s'] = PUSHED;
	}

}

void keyUp(unsigned char key, int x, int y) {
	if (key == 'a')
		keyarr['a'] = NOTPUSHED;
	if (key == 'w')
		keyarr['w'] = NOTPUSHED;
	if (key == 's')
		keyarr['s'] = NOTPUSHED;
	if (key == 'd')
		keyarr['d'] = NOTPUSHED;

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
	car = new Model(&shaderWhite, "models/dodge-challenger_model.obj", "models/");
	startingLine = new Model(&shaderGreen, "models/plane.obj", "models/");
	platform1 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform2 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform3 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform4 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform5 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform6 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform7 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform8 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform9 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform10 = new Model(&shaderBlack, "models/plane.obj", "models/");
	platform11 = new Model(&shaderBlack, "models/plane.obj", "models/");
	bleachers = new Model(&shaderBrown, "models/bleachers.obj", "models/");
	pressbox = new Model(&shaderBrown, "models/pressbox.obj", "models/");
	field = new Model(&shaderGreen, "models/plane.obj", "models/");
	tree = new Model(&shaderGreen, "models/tree.obj", "models/");
	tree2 = new Model(&shaderGreen, "models/tree.obj", "models/");
	tree3 = new Model(&shaderGreen, "models/tree.obj", "models/");
	tree4 = new Model(&shaderGreen, "models/tree.obj", "models/");
	tree5 = new Model(&shaderGreen, "models/tree.obj", "models/");
	tree6 = new Model(&shaderGreen, "models/tree.obj", "models/");
	racebanner = new Model(&shaderWhite, "models/racebanner.obj", "models/");
	line = new Model(&shaderYellow, "models/line.obj", "models/");
	line2 = new Model(&shaderYellow, "models/line.obj", "models/");
	line3 = new Model(&shaderYellow, "models/line.obj", "models/");
	line4 = new Model(&shaderYellow, "models/line.obj", "models/");
	line5 = new Model(&shaderYellow, "models/line.obj", "models/");
	line6 = new Model(&shaderYellow, "models/line.obj", "models/");
	line7 = new Model(&shaderYellow, "models/line.obj", "models/");
	line8 = new Model(&shaderYellow, "models/line.obj", "models/");
	line9 = new Model(&shaderYellow, "models/line.obj", "models/");
	line10 = new Model(&shaderYellow, "models/line.obj", "models/");
	line11 = new Model(&shaderYellow, "models/line.obj", "models/");
	line12 = new Model(&shaderYellow, "models/line.obj", "models/");
	line13 = new Model(&shaderYellow, "models/line.obj", "models/");
	line14 = new Model(&shaderYellow, "models/line.obj", "models/");
	building = new Model(&shaderBlue, "models/building.obj", "models/");
	tube = new Model(&shaderRed, "models/tube.obj", "models/");
	arrow = new Model(&shaderRed, "models/arrow.obj", "models/");
	billboard = new Model(&shaderYellow, "models/billboard.obj", "models/");
	ring = new Model(&shaderYellow, "models/ring.obj", "models/");
	billboard2 = new Model(&shaderYellow, "models/billboard.obj", "models/");
	text = new Model(&shaderBlack, "models/text.obj", "models/");
	text2 = new Model(&shaderBlack, "models/text2.obj", "models/");
	//wheel1 = new Model(&shader, "models/wheel1.obj", "models/");
	glutMainLoop();

	return 0;
}
