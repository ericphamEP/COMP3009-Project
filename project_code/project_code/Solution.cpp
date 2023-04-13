//=============================================================================
// solution.c
//
//Author: Doron Nussbaum (C) 2015 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. solution framework for assignments
//
//
// Description:
//--------------
// A simple framework for drawing objecs 
//
//
// License
//--------------
//
// Code can be used for instructional and educational purposes.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty
//=============================================================================


#include "Solution.h"


#define NORMAL_SPEED 3.0
#define MAX_SPEED 3.0

// MENU defines
#define EXIT_PROGRAM 0
#define TOGGLE_MODE 1
#define TOGGLE_SKYBOX 12
#define SQUISH_MIN_UP 2
#define SQUISH_MIN_DOWN 3
#define SQUISH_MAX_UP 4
#define SQUISH_MAX_DOWN 5
#define SPEED_UP 6
#define SPEED_DOWN 7


Solution *Solution::sol = NULL;


Solution::Solution() : numFrames(0)

{
}

Solution::~Solution()
{

}

// Initializing the opengl functions and windows
int Solution::initOpenGL()
{
	//initialize OpenGL
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512,512);
	glutCreateWindow("Petpetpet 3D Generator");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);
	glutDisplayFunc(Solution::renderCB);
	glutReshapeFunc(Solution::winResizeCB);
	glutKeyboardFunc(Solution::keyboardCB);
	glutSpecialFunc(Solution::specialKeyboardCB);
	glutMouseFunc(Solution::mouseCB);
	glutMotionFunc(Solution::mouseMoveCB);
	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERED_OBJECTS);
	createMenu();

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		printf("Error - %s \n", glewGetErrorString(res));
		return (-1);
	}

	return 0;
}

// render callback function
void Solution::renderCB()
{
	sol->render();
}

// keyboard callback function
void Solution::keyboardCB(unsigned char key, int x, int y)
{
	sol->keyboard(key, x, y);
}

// special keyboard callback function
void Solution::specialKeyboardCB(int key, int x, int y)
{
	sol->specialKeyboard(key, x, y);
}

// mouse callback function
void Solution::mouseCB(int button, int state, int x, int y)
{
	sol->mouse(button, state, x, y);
}

// mouse motion callback function
void Solution::mouseMoveCB(int x, int y)
{
	sol->mouseMove(x, y);
}

void Solution::menuFunCB(int num)
{
	sol->menuFun(num);
}

// window resize callback function
void Solution::winResizeCB(int width, int height)
{
	sol->winResize(width, height);
}

// timer  callback function
void Solution::timerCB(int operation)
{
	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERED_OBJECTS);	
	sol->timer(operation);
}

// timer  function
int Solution::timer(int operation)
{
	numFrames++;
	switch (operation) {
	case UPDATE_RENDERED_OBJECTS:
		updateObjects(numFrames);
		break;
	default:
		break;
	}
	return(0);
}


/******************************************************************************/

// initialization
int Solution::initSolution(char* objectFilePath, char* materialFilePath)
{
	int rc;
	Vertices vtx;
	Indices ind;
	pointLight point;

	/*char texSky1[] = "./project_code/cubemap/px.png";
	char texSky2[] = "./project_code/cubemap/nx.png";
	char texSky3[] = "./project_code/cubemap/py.png";
	char texSky4[] = "./project_code/cubemap/ny.png";
	char texSky5[] = "./project_code/cubemap/pz.png";
	char texSky6[] = "./project_code/cubemap/nz.png";*/

	char texSky1[] = "./project_code/cubemap/pad.jpg";
	char texSky2[] = "./project_code/cubemap/pad.jpg";
	char texSky3[] = "./project_code/cubemap/pad.jpg";
	char texSky4[] = "./project_code/cubemap/pad.jpg";
	char texSky5[] = "./project_code/cubemap/pad.jpg";
	char texSky6[] = "./project_code/cubemap/pad.jpg";

	char* texSky[6] = {
		texSky1,
		texSky2,
		texSky3,
		texSky4,
		texSky5,
		texSky6 };

	// create the shader object
	char vtxShader[] = "./project_code/light.vert";
	char fragShader[] = "./project_code/light.frag";

	char vtxSkyShader[] = "./project_code/skybox.vert";
	char fragSkyShader[] = "./project_code/skybox.frag";

	rc = shader.createShader(vtxShader, fragShader);
	if (rc != 0) {
		fprintf(stderr, "Error in generating shader (solution)\n");
		rc = -1;
		//goto err;
	}

	//create the squish object from model
	squish.initGeom(objectFilePath);
	squish.optimizeScale();
	squish.createVAO(shader);
	squish.setAutoMode(true);

	//create the hand object
	hand.initGeom();
	hand.setMaterial(
		Vector3f(0.3, 0.3, 0.3),
		Vector3f(0.75, 0.75, 0.75),
		Vector3f(0.2, 0.2, 0.2),
		Vector3f(0.5, 0.5, 0.5)
	);
	hand.setModelScale(2.5, 2.5, 2.5);
	hand.setModelPosition(40, 0, 0);
	hand.incrementModelRotations(90, 0, 270);
	hand.createVAO(shader);
	handAdjust = 0;

	Surface::createSurface(1, 1, 0, 1, 0, 1, vtx, ind);
	surface.setMaterial(
		Vector3f(1.0, 1.0, 1.0),
		Vector3f(0.01, 0.01, 0.01),
		Vector3f(0.01, 0.01, 0.01),
		Vector3f(0.0, 0.0, 0.0)
	);
	surface.setModelScale(500, 500, 500);
	surface.createVAO(shader, vtx, ind);
	
	// set the camera initial position
	cam.setCamera(Vector3f(0, 20, 100), Vector3f(0, 20, 0), Vector3f(0, 1, 0), 100, 0);

	//create light(s)
	point.ambientIntensity = Vector3f(1.0, 1.0, 1.0);
	point.lightIntensity = Vector3f(1.0, 1.0, 1.0);
	point.worldPos = Vector3f(240, 210, 200);
	point.specularPower = 5;

	light.setPointLight(point);
	light.enablePointLightCompnents(1, 1, 1);

	//load the textures
	squishTexture.loadTexture(materialFilePath, GL_TEXTURE_2D);
	handTexture.loadTexture("./project_code/models/female-hand/textures/038F_05SET_04SHOT_DIFFUSE.png", GL_TEXTURE_2D);
	surfaceTexture.loadTexture(texSky4, GL_TEXTURE_2D);

	skybox.init(vtxSkyShader, fragSkyShader);
	skybox.loadTextureImages(texSky);

	//set the factor
	factor = 1;
	skyboxOn = true;

	return 0;
}

void Solution::setSolution(Solution * _sol)
{
	Solution::sol = _sol;
}

// render function
void Solution::render()
{
	Matrix4f viewMat, projMat;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (skyboxOn) {
		skybox.render(cam);
	}
	
	shader.useProgram(1);

	// set the view model transformation
	viewMat = cam.getViewMatrix(NULL);	// get the camera view transformation
	// move matrix to shader
	shader.copyMatrixToShader(viewMat, "view");

	light.loadPointLight(shader);

	Vector3f tempPos = cam.getPosition();
	shader.copyFloatVectorToShader((float*)&tempPos, 1, 3, "gEyeWorldPos");

	// set the projection matrix
	projMat = cam.getProjectionMatrix(NULL);
	// move matrix to shader
	shader.copyMatrixToShader(projMat, "projection");
	
	if (skyboxOn) {
		// surface rendering
		surfaceTexture.bindToTextureUnit(GL_TEXTURE1);
		surfaceTexture.setTextureSampler(shader, "texSampler", GL_TEXTURE1);
		surface.render(shader);
	}

	// squish object rendering
	squishTexture.bindToTextureUnit(GL_TEXTURE1);
	squishTexture.setTextureSampler(shader, "texSampler", GL_TEXTURE1);
	squish.render(shader);

	// hand rendering
	handTexture.bindToTextureUnit(GL_TEXTURE1);
	handTexture.setTextureSampler(shader, "texSampler", GL_TEXTURE1);
	hand.render(shader);
	

	glutSwapBuffers();
}

// keyboard handling function. 
// Note: 033 is an "octal" number and is Escape key, so you could call "exit" on that
void Solution::keyboard(unsigned char key, int x, int y)
{
	static int nc = 0;

	nc++;
	switch (key) {
	case 033:
	case 'Q':
	case 'q':
		exit(1);
		break;
	case 'w':
		nc++;
		cam.moveForward(NORMAL_SPEED*factor);
		break;
	case 's':
		cam.moveBackward(NORMAL_SPEED*factor);
		break;
	case 'a':
		cam.moveLeft((float) .2*factor);
		break;
	case 'd':
		cam.moveRight((float) .2*factor);
		break;
	case 'x':
		cam.moveUp(NORMAL_SPEED * factor);
		break;
	case 'z':
		cam.moveDown(NORMAL_SPEED * factor);
		break;
	case 'h':
		handAdjust += 0.5;
		break;
	case 'H':
		handAdjust -= 0.5;
		break;
	//controls for scale factor
	case 'j':
		squish.incrementScaleMagnitude(-0.005, 0, 0);
		break;
	case 'J':
		squish.incrementScaleMagnitude(0.005, 0, 0);
		break;
	case 'k':
		squish.incrementScaleMagnitude(0, -0.005, 0);
		break;
	case 'K':
		squish.incrementScaleMagnitude(0, 0.005, 0);
		break;
	case 'l':
		squish.incrementScaleMagnitude(0, 0, -0.005);
		break;
	case 'L':
		squish.incrementScaleMagnitude(0, 0, 0.005);
		break;
	case 'i':
		squish.incrementScaleFactor(-0.5);
		break;
	case 'I':
		squish.incrementScaleFactor(0.5);
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		factor = key - '0';
		break;
	}
}

// special keyboard handling function
void Solution::specialKeyboard(int key, int x, int y)
{
	switch (key) {
	case 033:
	case 'Q':
	case 'q':
		exit(1);
		break;
	case GLUT_KEY_LEFT:
		cam.roll((float) .2*factor);
		break;
	case GLUT_KEY_UP:
		cam.pitch((float) .2*factor);
		break;
	case GLUT_KEY_RIGHT:
		cam.roll((float)-.2*factor);
		break;
	case GLUT_KEY_DOWN:
		cam.pitch((float)-.2*factor);
		break;
	}
}

// mouse handling function
void Solution::mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			currX = x;
			currY = y;

			squish.startSquish();
			break;
		case 3:
			cam.moveForward(NORMAL_SPEED * factor);
			break;
		case 4:
			cam.moveBackward(NORMAL_SPEED * factor);
			break;
		}
	}
}

// mouse motion handling function
void Solution::mouseMove(int x, int y)
{
	// handle horizontal movement
	int deltaX = currX - x;
	cam.moveRight((float).002 * factor * deltaX);
	currX = x;

	// handle vertical movement
	int deltaY = currY - y;
	cam.moveDown((float).2 * factor * deltaY);
	currY = y;

}

void Solution::createMenu(void) {

	// create a submenu
	int submenu_id = glutCreateMenu(menuFunCB);
	glutAddMenuEntry("Increase squish speed by 0.5", SPEED_UP);
	glutAddMenuEntry("Lower squish speed by 0.5", SPEED_DOWN);
	glutAddMenuEntry("Increase squish minimum by 0.1", SQUISH_MIN_UP);
	glutAddMenuEntry("Lower squish minimum by 0.1", SQUISH_MIN_DOWN);
	glutAddMenuEntry("Increase squish maximum by 0.1", SQUISH_MAX_UP);
	glutAddMenuEntry("Lower squish maximum by 0.1", SQUISH_MAX_DOWN);

	// create the main menu
	int menu_id = glutCreateMenu(menuFunCB);
	glutAddSubMenu("Adjust Squishing", submenu_id);
	glutAddMenuEntry("Toggle Auto-Squish Mode", TOGGLE_MODE);
	glutAddMenuEntry("Toggle Skybox", TOGGLE_SKYBOX);
	glutAddMenuEntry("Quit", EXIT_PROGRAM);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Solution::menuFun(int num)
{
	int winId;
	switch (num) {
	case EXIT_PROGRAM:
		winId = glutGetWindow();
		glutDestroyWindow(winId);
		exit(0);
		break;
	case TOGGLE_MODE:
		squish.toggleAutoMode();
		break;
	case TOGGLE_SKYBOX:
		skyboxOn = !skyboxOn;
		break;
	case SPEED_UP:
		squish.incrementScaleFactor(0.5);
		break;
	case SPEED_DOWN:
		squish.incrementScaleFactor(-0.5);
		break;
	case SQUISH_MIN_UP:
		squish.incrementMinSquishFactor(0.1);
		break;
	case SQUISH_MIN_DOWN:
		squish.incrementMinSquishFactor(-0.1);
		break;
	case SQUISH_MAX_UP:
		squish.incrementMaxSquishFactor(0.1);
		break;
	case SQUISH_MAX_DOWN:
		squish.incrementMaxSquishFactor(-0.1);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

// window resize handling function.  
void Solution::winResize(int width, int height)
{
	glViewport(0, 0, width, height);
}

// update state of the objects
int Solution::updateObjects(int numFrames)
{
	squish.updateSquish();
	hand.setHeightPosition(squish.getTopPosition() + handAdjust);
	glutPostRedisplay();
	return 0;
}
