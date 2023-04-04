

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


#define NORMAL_SPEED 2.0
#define MAX_SPEED 2.0




Solution *Solution::sol = NULL;

/****************************************************************************/

Solution::Solution() : numFrames(0)

{
}

/*************************************************************************/


Solution::~Solution()
{

}

/******************************************************************************/


// initializing the opengl functions and windows
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
	glCullFace(GL_BACK);
	glutDisplayFunc(Solution::renderCB);
	glutReshapeFunc(Solution::winResizeCB);
	glutKeyboardFunc(Solution::keyboardCB);
	glutSpecialFunc(Solution::specialKeyboardCB);
	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERRED_OBJECTS);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		printf("Error - %s \n", glewGetErrorString(res));
		return (-1);
	}


	return 0;
}

/************************************************************/

// render callback function.  This is a static funcion


void Solution::renderCB()
{

	sol->render();
	
}


/************************************************************/

// keyboard callback function.  This is a static funcion


void Solution::keyboardCB(unsigned char key, int x, int y)
{
	sol->keyboard(key, x, y);
}


/************************************************************/

// special keyboard callback function.  This is a static funcion



void Solution::specialKeyboardCB(int key, int x, int y)
{
	sol->specialKeyboard(key, x, y);
}


/************************************************************/

// window resize callback function.  This is a static funcion



void Solution::winResizeCB(int width, int height)
{
	sol->winResize(width, height);
}

/************************************************************/

// timer  callback function.  This is a static funcion


void Solution::timerCB(int operation)
{

	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERRED_OBJECTS);	
	sol->timer(operation);

}


/************************************************************/

// timrt  function.  


int Solution::timer(int operation)
{
	numFrames++;
	switch (operation) {
	case UPDATE_RENDERRED_OBJECTS:
		updateObjects(numFrames);
		break;
	default:
		break;
	}
	return(0);
}




/******************************************************************************/
// initialization of the solution
int Solution::initSolution(char* objectFilePath)
{
	int rc;
	Vertices vtx;
	Indices ind;
	pointLight point;

	// create the shader object
	//rc = shader.createShaderProgram("light_add.vert", "light_add_to_continue.frag");
	char vtxShader[] = "./project_code/light.vert";
	char fragShader[] = "./project_code/light.frag";

	rc = shader.createShader(vtxShader, fragShader);
	if (rc != 0) {
		fprintf(stderr, "Error in generating shader (solution)\n");
		rc = -1;
		//goto err;
	}

	// create one triangle
	t.setInitialPosition(0, 0, -5);
	t.setScale(9, 9, 9);

	// create one cube
	c.setInitialPosition(-20, 0, -5);
	c.setScale(5, 5, 5);

	//create the squish object from model
	squish.initGeom(objectFilePath);
	squish.optimizeScale();
	squish.createVAO(shader);

	//create the hand object
	hand.initGeom();
	hand.setModelScale(2.5, 2.5, 2.5);
	hand.setModelPosition(45, 0, 0);
	hand.incrementModelRotations(90, 0, 270);
	hand.createVAO(shader);
	
	// set the camera initial position
	cam.setCamera(Vector3f(0, 0, 100), Vector3f(0, 0,0), Vector3f(0, 1, 0));

	//create light(s)
	point.ambientIntensity = Vector3f(1.0, 1.0, 1.0);
	point.lightIntensity = Vector3f(1.0, 1.0, 1.0);
	point.worldPos = Vector3f(240, 210, 200);
	point.specularPower = 5;

	light.setPointLight(point);
	light.enablePointLightCompnents(1, 1, 1);

	//load the textures
	squishTexture.loadTexture("./project_code/models/pikachu/textures/texture_170290017759.jpeg", GL_TEXTURE_2D);
	handTexture.loadTexture("./project_code/models/female-hand/textures/038F_05SET_04SHOT_DIFFUSE.png", GL_TEXTURE_2D);

	//set the factor
	factor = 1;

	return 0;
}




/**********************************************************************/

void Solution::setSolution(Solution * _sol)
{
	Solution::sol = _sol;
}

/************************************************************/

// render function.  


void Solution::render()
{

	Matrix4f viewMat, projMat;
	
	shader.useProgram(1);

	// OpenGL 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_CULL_FACE);		// ensure that faces are displayed from every view point

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


/************************************************************/

// keyboard handling function. 
// This one is the keyboard func (clearly) which moves the camera using WASD
// Note: 033 is an "octal" number and is the same thing as Escape, so you could call "exit" on that

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
		cam.yaw((float) .2*factor);
		break;
	case 'd':
		cam.yaw((float)-.2*factor);
		break;
	case 'g':
		cam.moveRight(NORMAL_SPEED*factor);
		break;
	case 'G':
		cam.moveLeft(NORMAL_SPEED*factor);
		break;
	case 'z':
		cam.zoomIn();
		break;
	case 'Z':
		cam.zoomOut();
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



/************************************************************/

// special keyboard handling  function.  



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


/************************************************************/

// window resize handling function.  



void Solution::winResize(int width, int height)
{

	glViewport(0, 0, width, height);

}

/***********************************************************/
// update the state of the objects

int Solution::updateObjects(int numFrames)
{
	// recall that this will be carried out in the model space
	//testSphere.incrementRotations(0.5, 0, 0);
	t.incrementRotations(0, 0, 0.5);
	c.incrementRotations(0.5, 0, 0.5);
	squish.updateSquish(3);
	hand.setHeightPosition(squish.getTopPosition());
	glutPostRedisplay();
	return 0;
}
