#pragma once
#ifndef GRPHICS_IOBJECT_HEADER
#define GRPHICS_IOBJECT_HEADER

//=============================================================================
// graphicsObject.h
//
//Author: Doron Nussbaum (C) 2023 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. generic class for graphics objects. 
//
//
// Description:
//--------------
//  sub classes of objects can be inherited.  The class does the main funcionality of setting and rendering objects.

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
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/glut.h"
#endif

#include "geometry_common.h"
#include <vector>
#include "GL/nuss_math.h"
#include "Shader.h"


// STRUCTURES
typedef struct materials {
	Vector3f ambientMaterial;
	Vector3f diffuseMaterial;
	Vector3f specularMaterial;
	Vector3f interalRadiation;
} MATERIALS;


class GraphicsObject
{
public:
	GraphicsObject();
	virtual ~GraphicsObject();

	int createVAO(Shader shader);

	virtual int render();
	virtual int render(Matrix4f worldMat);
	virtual int render(Shader shader);
	virtual void update() {};

protected:
	float rollAngle;	// rotation around the z-axis
	float pitchAngle;	// rotation around the x-axis
	float yawAngle;		// rotation around the y-axis
	Vector3f position;	// object position in space
	Vector3f scale;		// scaling of the object

	float worldRollAngle;	// rotation around the z-axis
	float worldPitchAngle;	// rotation around the x-axis
	float worldYawAngle;		// rotation around the y-axis
	Vector3f worldPosition;	// object position in space
	Vector3f worldScale;		// scaling of the object
	std::vector<GraphicsObject*> m_children;

	Matrix4f modelMat;
	Matrix4f worldMat;

	float       topPosition;
	float       bottomPosition;
	Vertices    m_vertices;
	Indices		m_indices_tri;
	Indices		m_indices_quad;
	Indices		m_indices_pent;

	GLuint vtxVBO;  // the vertex buffer object which holds the vertices data
	GLuint vao;  // the vertex array object which holds all the data required for renderring.
	GLuint indVBO;	// index buffer for drawing the geometry

	int numIndices;
	MATERIALS materials;

	virtual int loadMaterials(Shader shader);
	void computeModelMat();

public:
	void setModelRotations(float rollAngle, float pitchAngle, float yawAngle);
	void setModelPosition(Vector3f position);
	void setModelPosition(float x, float y, float z);
	void incrementModelRotations(float rollAngle, float pitchAngle, float yawAngle);
	void incrementModelPosition(Vector3f position);
	void incrementModelPosition(float deltaX, float deltaY, float deltaZ);
	void setModelScale(Vector3f position);
	void setModelScale(float x, float y, float z);

	void setWorldRotations(float rollAngle, float pitchAngle, float yawAngle);
	void setWorldPosition(Vector3f position);
	void incrementWorldRotations(float rollAngle, float pitchAngle, float yawAngle);
	void addChild(GraphicsObject *obj);
	void initGeom(char* filepath);

private:
	void computeWorldMat();

};

#endif