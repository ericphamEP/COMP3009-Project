#pragma once
#ifndef SOLUTION_HEADER
#define SOLUTION_HEADER

//=============================================================================
// solution.h
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

#include "GL/glew.h"
#include "GL/glut.h"

#include "Hand.h"
#include "Squish.h"
#include "SkyBox.h"
#include "surface.h"

#include "camera.h"
#include "Light.h"
#include "Texture.h"

#define UPDATE_RENDERED_OBJECTS 1000
#define FRAME_TIME 30

class Solution
{
public:
	Solution();
	~Solution();
	int initOpenGL();

	static void renderCB();
	static void keyboardCB(unsigned char key, int x, int y);
	static void specialKeyboardCB(int key, int x, int y);
	static void mouseCB(int button, int state, int x, int y);
	static void mouseMoveCB(int x, int y);
	static void menuFunCB(int num);
	static void winResizeCB(int width, int height);
	static void timerCB(int operation);

	static void setSolution(Solution * _sol);
	int initSolution(char*, char*);
	
	void render();
	void keyboard(unsigned char key, int x, int y);
	void specialKeyboard(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void menuFun(int num);
	void createMenu(void);
	void winResize(int width, int height);
	int timer(int operation);
	int updateObjects(int numFrames);

private:
	Shader shader;
	Hand hand;
	Squish squish;
	SkyBox skybox;
	Surface surface;
	float handAdjust;
	int currX;
	int currY;
	char* objectFilePath;
	int factor;		// speeds up actions
	bool skyboxOn;
	int numFrames;

	static Solution* sol;
	Camera cam;
	Light light;

	Texture squishTexture, handTexture, surfaceTexture;
	
};

#endif