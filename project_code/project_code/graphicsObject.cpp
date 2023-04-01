

//=============================================================================
// graphicsObject.c
//
//Author: Doron Nussbaum (C) 2015 All Rights Reserved.
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



#include <iostream>
#include <fstream>
#include <string>
#include "GraphicsObject.h"

/***************************************************************************/

GraphicsObject::GraphicsObject() :
	rollAngle(0),
	pitchAngle(0),
	yawAngle(0),
	position(Vector3f(0, 0, 0)),
	scale(1, 1, 1),
	worldRollAngle(0),
	worldPitchAngle(0),
	worldYawAngle(0),
	worldPosition(Vector3f(0, 0, 0)),
	worldScale(1, 1, 1),
	modelMat(Matrix4f::identity()),
	worldMat(Matrix4f::identity()),
	vtxVBO(-1), 
	vao(-1), 
	indVBO(-1),
	numIndices(0)
{
	m_children.resize(0);
}

/***************************************************************************/



GraphicsObject::~GraphicsObject()
{
}


/***************************************************************************/



int GraphicsObject::createVAO(Shader shader)
{
	return 0;
}


/***************************************************************************/


int GraphicsObject::createVAO(Shader shader, Vertices vtx, Indices ind)
{
	int rc = 0;
	Vertex v;

	GLint location;		// location of the attributes in the shader;

	//create vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//create vertex buffer object
	glGenBuffers(1, &vtxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vtxVBO);
	glBufferData(GL_ARRAY_BUFFER, vtx.size() * sizeof(Vertex), vtx.data(), GL_STATIC_DRAW);

	//set the vertex position
	location = glGetAttribLocation(shader.getProgId(), "vtxPos");
	if (location == -1) {
		rc = -1;
		goto err;
	}
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));

	//set the vertex color
	location = glGetAttribLocation(shader.getProgId(), "vtxCol");
	if (location == -1) {
		//rc = -2;
		//goto err;
	}
	else {
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	}

	//set the vertex normal
	location = glGetAttribLocation(shader.getProgId(), "vtxNormal");
	if (location == -1) {
		rc = -3;
		//DN	goto err;
	}
	else {
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	}

	//set the vertex tex coordinates
	location = glGetAttribLocation(shader.getProgId(), "vtxCoord");
	if (location == -1) {
		rc = -3;
		//DN	goto err;
	}
	else {
		glEnableVertexAttribArray(location);
		//int relAddress = (char*)v.texCoord - (char*)&v;

		//glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)relAddress);
		glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

		//glEnableVertexAttribArray(location);
		//glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	}

	//create index buffer
	glGenBuffers(1, &indVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(GLuint), ind.data(), GL_STATIC_DRAW);
	// store the number of indices
	numIndices = ind.size();

	//end creation
	glBindVertexArray(0);

err:
	return(rc);
}


/*********************************************************************************/


int GraphicsObject::render()
{
#if 0
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix
	Matrix4f modelMat;	// final model matrix

	// set the transformation matrix - the model transfomration
	modelMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	modelMat = scaleMat * modelMat;

	// set the rotation  - this is model space to model space transformation 
	rotMat = Matrix4f::rotateRollPitchYaw(rollAngle,pitchAngle,yawAngle,1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;


	// set the translation - this is model space to world space transformation
	transMat = Matrix4f::translation(position);
	modelMat = transMat * modelMat;


	// draw using indices
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);


#endif
	return 0;
}

/*********************************************************************************/


int GraphicsObject::render(Matrix4f worldMat)
{
#if 0
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix
	Matrix4f modelMat;	// final model matrix

	// set the transformation matrix - the model transfomration
	modelMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	modelMat = scaleMat * modelMat;

	// set the rotation  - this is model space to model space transformation 
	rotMat = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;


	// set the translation - this is model space to world space transformation
	transMat = Matrix4f::translation(position);
	modelMat = transMat * modelMat;


	// draw using indices
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);


#endif
	return 0;
}

/*********************************************************************************/
//rendering with a shader

int GraphicsObject::render(Shader shader)
{
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix
	Matrix4f modelMat;	// final model matrix

	// set the transformation matrix - the model transfomration
	modelMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	modelMat = scaleMat * modelMat;

	// set the rotation  - this is model space to model space transformation 
	rotMat = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;


	// set the translation - this is model space to world space transformation
	transMat = Matrix4f::translation(position);
	modelMat = transMat * modelMat;

	// move matrix to shader
	shader.copyMatrixToShader(modelMat, "model");



	// bind the vao
	glBindVertexArray(vao);

	// draw using indices
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);

	// unbind the vao
	glBindVertexArray(0);

	return 0;
}

/*************************************************************/
// sets the initial orientation

void GraphicsObject::setModelRotations(float rollAngle, float pitchAngle, float yawAngle)
{
	this->rollAngle = rollAngle;
	this->pitchAngle = pitchAngle;
	this->yawAngle = yawAngle;

	computeModelMat();
}

/*************************************************************************/

// set the initial position

void GraphicsObject::setModelPosition(Vector3f position)
{
	this->position = position;
	computeModelMat();
}

/*************************************************************/
// sets the initial orientation

void GraphicsObject::setWorldRotations(float rollAngle, float pitchAngle, float yawAngle)
{
	this->worldRollAngle = rollAngle;
	this->worldPitchAngle = pitchAngle;
	this->worldYawAngle = yawAngle;

	computeWorldMat();
}

/*************************************************************************/

// set the initial position

void GraphicsObject::setWorldPosition(Vector3f position)
{
	this->worldPosition= position;
	computeWorldMat();
}



/*************************************************************/
// increment the courrent rotation by the given amounts

void GraphicsObject::incrementWorldRotations(float rollAngle, float pitchAngle, float yawAngle)
{
	this->worldRollAngle += rollAngle;
	this->worldPitchAngle += pitchAngle;
	this->worldYawAngle += yawAngle;

	computeWorldMat();
}


/*************************************************************************/

// set the initial position

void GraphicsObject::setModelPosition(float x, float y, float z)
{
	this->position = Vector3f(x, y, z);
	computeModelMat();
}

/*************************************************************/
// increment the courrent rotation by the given amounts

void GraphicsObject::incrementModelRotations(float rollAngle, float pitchAngle, float yawAngle)
{
	this->rollAngle += rollAngle;
	this->pitchAngle += pitchAngle;
	this->yawAngle += yawAngle;

	computeModelMat();
}

/*************************************************************************/

// increment positin by delta position

void GraphicsObject::incrementModelPosition(Vector3f deltaPosition)
{
	this->position += deltaPosition;
	computeModelMat();
}

/*************************************************************************/

// increment position by delta

void GraphicsObject::incrementModelPosition(float deltaX, float deltaY, float deltaZ)
{
	this->position += Vector3f(deltaX, deltaY, deltaZ);
	computeModelMat();
}


/*************************************************************************/

// set the initial position

void GraphicsObject::setModelScale(Vector3f scale)
{
	this->scale = scale;
	computeModelMat();
}

/*************************************************************************/

// set the initial position

void GraphicsObject::setModelScale(float scaleX, float scaleY, float scaleZ)
{
	this->scale = Vector3f(scaleX, scaleY, scaleZ);
	computeModelMat();
}


/*************************************************************************/

// Computer the model transformation matrix

void GraphicsObject::computeModelMat()
{
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix

	// set the transformation matrix - the model transfomration
	modelMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	modelMat = scaleMat * modelMat;

	// set the rotation  - this is model space to model space transformation 
	rotMat = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;


	// set the translation - this is model space to world space transformation
	transMat = Matrix4f::translation(position);
	modelMat = transMat * modelMat;
}


/*************************************************************************/

// set the world transformation matrix

void GraphicsObject::computeWorldMat()
{
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix

	// set the transformation matrix - the model transfomration
	worldMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix4f::scale(worldScale.x, worldScale.y, worldScale.z);
	worldMat = scaleMat * worldMat;

	// set the rotation  - this is model space to model space transformation 
	rotMat = Matrix4f::rotateRollPitchYaw(worldRollAngle, worldPitchAngle, worldYawAngle, 1);
	// note that we always multiply the new matrix on the left
	worldMat = rotMat * worldMat;


	// set the translation - this is model space to world space transformation
	transMat = Matrix4f::translation(worldPosition);
	worldMat = transMat * worldMat;
}





/*********************************************************************************/
// adds a child to the list of chilren

void GraphicsObject::addChild(GraphicsObject *obj)
{
	m_children.push_back(obj);
}



void GraphicsObject::initGeom(char* filepath)
{
	topPosition = NULL;
	bottomPosition = NULL;

	m_vertices.reserve(1000000);
	m_indices_tri.reserve(1000000);
	m_indices_quad.reserve(1000000);
	m_indices_pent.reserve(1000000);

	std::vector<Vector2f> textureCoordinates; // simple implementation: put all vtx coords in here then connect them during f part
	textureCoordinates.reserve(1000000);

	int count = 0;

	std::ifstream in(filepath, std::ios::in);
	if (!in) {
		printf("WARNING: Invalid filepath\n");
		return;

	}
	std::string line;
	while (std::getline(in, line)) {
		// vertices
		if (line.substr(0, 2) == "v ") {
			VERTEX vertex;
			int matches = sscanf_s(line.c_str(), "v %f %f %f\n", &vertex.pos.x, &vertex.pos.y, &vertex.pos.z);
			if (matches != 3) {
				printf("WARNING: Cannot parse vertices.\n");
			}

			m_vertices.push_back(vertex);

			if (topPosition == NULL || topPosition < vertex.pos.y) {
				topPosition = vertex.pos.y;
			}
			if (bottomPosition == NULL || bottomPosition > vertex.pos.y) {
				bottomPosition = vertex.pos.y;
			}
		}
		else if (line.substr(0, 2) == "vt") { //check for texture co-ordinate
			Vector2f tempCoords;
			int matches = sscanf_s(line.c_str(), "vt %f %f\n", &tempCoords.x, &tempCoords.y);
			if (matches != 2) {
				printf("WARNING: Cannot parse texture coordinates.\n");
			}
			
			textureCoordinates.push_back(tempCoords);
		}
		else if (line.substr(0, 2) == "vn") { //check for vertex nornmal

			//todo

		}
		// faces
		else if (line.substr(0, 2) == "f ") {
			unsigned int v[5], vt[5], vn[5];
			int matches = sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &v[0], &vt[0], &vn[0], &v[1], &vt[1], &vn[1], &v[2], &vt[2], &vn[2], &v[3], &vt[3], &vn[3], &v[4], &vt[4], &vn[4]);
			if (matches == 9) { // 3 vertex face - triangle
				for (int i = 0; i < 3; i++) {
					m_indices_tri.push_back(v[i] - 1);
				}
			}
			else if (matches == 12) { // 4 vertex face - quad
				/*for (int i = 0; i < 4; i++) {
					m_indices_quad.push_back(v[i] - 1);
				}*/
				//split quads into 2 triangles
				//triangle 1
				m_indices_tri.push_back(v[0] - 1);
				m_indices_tri.push_back(v[1] - 1);
				m_indices_tri.push_back(v[2] - 1);
				//triangle 2
				m_indices_tri.push_back(v[0] - 1);
				m_indices_tri.push_back(v[2] - 1);
				m_indices_tri.push_back(v[3] - 1);
			}
			else if (matches == 15) { // 5 vertex face - pent
				for (int i = 0; i < 4; i++) {
					m_indices_pent.push_back(v[i] - 1);
				}
			}
			else {
				printf("WARNING: Object file cannot be imported. Try a differnt file.\n");
				return;
			}

		}

	}

	printf("\nThere are %d triangles, %d quads and %d pents.\n", (int)m_indices_tri.size(), (int)m_indices_quad.size(), (int)m_indices_pent.size());
	printf("Texture coordinate count: %d\n", count);
	// set y position to 'floor'
	position = Vector3f(0, -bottomPosition, 0);
	topPosition -= bottomPosition;
}