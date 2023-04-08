#include "Triangle.h"
#include "GL/glew.h"
#include "GL/glut.h"





/*************************************************************************/


Triangle::Triangle()
{

	// initialize the geometry
	initGeom();

}



/*************************************************************************/



Triangle::~Triangle()
{
}




/*********************************************************************************/


int Triangle::render()
{
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix
	Matrix4f modelMat;	// final model matrix

	Vector4f p;

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

	//render triangle
	glColor3f(1.0, 0.0, 0.0);

	// send the data to the GPU
	//glBegin(GL_LINE_STRIP);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; ++i) {
		glColor4fv((GLfloat *)&vtx[i].col);
		p = modelMat * Vector4f(vtx[i].pos.x, vtx[i].pos.y, vtx[i].pos.z,1);
		glVertex3fv((GLfloat *)&p);
	}
	glEnd();

	return 0;
}


/*************************************************************/
// sets the initial orientation

void Triangle::setInitialRotations(float rollAngle, float pitchAngle, float yawAngle)
{
	this->rollAngle = rollAngle;
	this->pitchAngle = pitchAngle;
	this->yawAngle = yawAngle;

}


/*************************************************************************/

// set the initial position

void Triangle::setInitialPosition(float x, float y, float z)
{
	this->position = Vector3f(x, y, z);
}

/*************************************************************/
// increment the courrent rotation by the given amounts

void Triangle::incrementRotations(float rollAngle, float pitchAngle, float yawAngle)
{
	this->rollAngle += rollAngle;
	this->pitchAngle += pitchAngle;
	this->yawAngle += yawAngle;

}

/*************************************************************************/

// increment position by delta

void Triangle::incrementPosition(float deltaX, float deltaY, float deltaZ)
{
	this->position += Vector3f(deltaX, deltaY, deltaZ);
}



/*************************************************************************/

// set the initial position

void Triangle::setScale(float scaleX, float scaleY, float scaleZ)
{
	this->scale = Vector3f(scaleX, scaleY, scaleZ);
}

/*************************************************************************/

// set the initial position

void Triangle::initGeom()
{
	vtx[0].pos = Vector3f(-0.5, -0.5, 0);
	vtx[1].pos = Vector3f(0.5, -0.5, 0);
	vtx[2].pos = Vector3f(0, 0.366, 0);

	vtx[0].col = Vector4f(1, 0, 0, 1);
	vtx[1].col = Vector4f(0, 1, 0, 1);
	vtx[2].col = Vector4f(0, 0, 1, 1);

	

}