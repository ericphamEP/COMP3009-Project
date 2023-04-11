#pragma once

//=============================================================================
// skybox.h
//
//Author: Doron Nussbaum (C) 2014 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. demonstarte the usage of a skybox
//
//
// Description:
//--------------
// A simple application that demonstrates how to crete and use a skybox 
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



// setting the different callback functions of OpenGL
#include "GL/glew.h"
#include "GL/glut.h"

#include "graphicsObject.h"
#include "camera.h"
#include "Shader.h"
#include "Texture.h"



class SkyBox

{
public:
	SkyBox(void);
	~SkyBox(void);
	int loadTextureImages(char ** texFileName);
	int loadColourTexture(void);
	int init(char* vsFileName, char *fsFileName);
	void incrementRotations(float rollAngle, float pitchAngle, float yawAngle);

	void render(Camera cam);
	GLuint getTexHandle(void);



private:
	Texture tex;
	//GLuint texHandle;  // this is the texture handle
	//GLuint shaderProg;	// shader for drawing the skybox
	Shader skyboxShader;			// shader class object
	GLuint vao;			// vao;
	GLuint vboCube;		// consider removing to a static global in the cpp file
	GLuint iboCube;		// consider removing to a static global in the cpp file
	GLuint texCube;		// consider removing to a static global in the cpp file

	float rollAngle;	// rotation around the z-axis
	float pitchAngle;	// rotation around the x-axis
	float yawAngle;		// rotation around the y-axis

	int createCube(void);

};

