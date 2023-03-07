

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


#define NORMAL_SPEED 0.5
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
	glutCreateWindow("Drawing Basic Objects");
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
//	int rc;
	Vertices vtx;
	Indices ind;

	// create one triangle
	t.setInitialPosition(0, 0, -5);
	t.setScale(9, 9, 9);

	// create one cube
	c.setInitialPosition(-20, 0, -5);
	c.setScale(5, 5, 5);

	squish.initGeom(objectFilePath);
	squish.setModelScale(12, 12, 12);


	// set the camera initial position
	cam.setCamera(Vector3f(0, 0, 100), Vector3f(0, 0,0), Vector3f(0, 1, 0));

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
	
	// OpenGL 
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);		// ensure that faces are displayed from every view point



	// set the view model transformation
	glMatrixMode(GL_MODELVIEW);
	viewMat = cam.getViewMatrix(NULL);	// get the camera view transformation

	// pass it to opengl before draw
	viewMat = Matrix4f::transpose(viewMat);
	//viewMat = Matrix4f::identity();
	glLoadMatrixf((GLfloat *)viewMat.data());


	// set the projection matrix
	projMat = cam.getProjectionMatrix(NULL);

	glMatrixMode(GL_PROJECTION);
	// pass it to opengl - Note that OpenGL accepts the matrix in column major
	projMat = Matrix4f::transpose(projMat);
	glLoadMatrixf((GLfloat *)projMat.data());


	// render the objects
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// triangle in fill mode
	t.render();

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// cube in wireframe mode
	c.render();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	squish.render();

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
	glutPostRedisplay();
	return 0;
}
