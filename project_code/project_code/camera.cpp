
//=============================================================================
// camera.cpp 
//
// Author: Doron Nussbaum (C) 2012 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. demonstarte the usage of a camera
//
//
// Description:
//--------------
// A simple application that demonstrates how to crete and use a camera 
//
//
// License
//--------------
//
// Code can be used for instructional and educational purposes and for assignments in the gaming courses at 
// the School of Compuer Science at Carleton University.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty

// Revsions:
// 1. Created - 10/2012 Doron Nussbaum
// 2. October 26, 2015 Doron Nussbaum - modifed geometry of the camera from 4D to 3D coordinates.


//=============================================================================

#include "camera.h"

/*
Purpose: camera constructor
Descripton: Setup camera attributes.
Return: n/a
*/
Camera::Camera(void): position(0, 0, 100), lookAtVector(0, 0, -1), upVector(0.0,1.0,0.0)
, radius(1), angle(0), speed(0), nearPlane(0.1), farPlane(1000), fieldOfView(60), aspectRatio(1.0)
{
	viewMat = Matrix4f::cameraMatrix(position, lookAtVector, upVector);
	projMat = Matrix4f::symmetricPerspectiveProjectionMatrix(fieldOfView, aspectRatio, nearPlane, farPlane);
}

Camera::~Camera(void)
{
}

/*
Purpose: Roll transformation
Descripton: Change camera orientation (roll transformation)

Return:
1 - if failed
0 - if successful
*/
int Camera::roll(float angleDeg)
{
	// get rotation matrix around the lookAtVector. Pay attention to the roll vector
	rotMat = Matrix4f::rotateVector(-lookAtVector, angleDeg, true);
	
	// rotate the upVector
	upVector = (rotMat * upVector).to3D();

	// update the view matrix
	viewMat = Matrix4f::cameraMatrix(position, position + lookAtVector, upVector);

	return 0;
}

/*
Purpose: Pitch transformation
Descripton: Change camera orientation (pitch transformation)

Return:
1 - if failed
0 - if successful
*/
int Camera::pitch(float angleDeg)
{
	// get rotation axis
	Vector3f rotVector = Vector3f::cross(upVector, lookAtVector);

	// get the rotation matrix around the x-axis
	rotMat = Matrix4f::rotateVector(rotVector, angleDeg, true);

	// rotate the upVector and the lookAtVector
	upVector = (rotMat * upVector).to3D();
	lookAtVector = (rotMat * lookAtVector).to3D();

	// update the view matrix
	viewMat = Matrix4f::cameraMatrix(position, position + lookAtVector, upVector);

	return 0;
}

/*
Purpose: Yaw transformation
Descripton: Change camera orientation (yaw transformation)

Return:
1 - if failed
0 - if successful
*/
int Camera::yaw(float angleDeg)
{
	// get the rotation matrix around the upVector 
	rotMat = Matrix4f::rotateVector(upVector, angleDeg, true);

	// rotate the lookAtVector
	lookAtVector = (rotMat * lookAtVector).to3D();

	// update the view matrix
	viewMat = Matrix4f::cameraMatrix(position, position + lookAtVector, upVector);

	return 0;
}

/*
Descripton: Obtains the current position of the camera
Return: Vector3f - camera position
*/
Vector3f Camera::getPosition(void)
{
	Vector3f v = position;	// DN 26/10/2015
	return (v);
}

/*
Purpose: 
Descripton: obtains the lookAt point of the camera
Return: Vector3f - camera lookAt point
*/
Vector3f Camera::getLookAtPoint(void)	// DN 26/10/2015
{
	return (position + lookAtVector);
}

/*
Descripton: Obtains the camera's up vector
Return: Vector3f - Camera upVector
*/
Vector3f Camera::getUpVector(void)		// DN 26/10/2015
{
	return (upVector);
}

/*
Descripton: changes the camera's position relative to its current position
Return:
Vector3f - position
*/
Vector3f Camera::changePositionDelta(float dx, float dy, float dz)
{
	// update the absolute position
	return changeAbsPosition(position.x + dx, position.y + dy, position.z + dz);
}

/*
Descripton: changes the camera's position relative to its current position
Return:
Vector3f - position
*/
Vector3f Camera::changePositionDelta(Vector3f *dv)
{
	// update absolute position
	return changePositionDelta(dv->x, dv->y, dv->z);
}

/*
Descripton: changes the camera's position to a new position
Return:
Vector3f - position
*/
Vector3f Camera::changeAbsPosition(float x, float y, float z)
{
	Vector3f lookAtPoint = getLookAtPoint();

	// set the position to the given position
	position.x = x;
	position.y = y;
	position.z = z;

	lookAtVector = lookAtPoint - position;

	// update the view matrix, keep look at point the same
	viewMat = Matrix4f::cameraMatrix(position, lookAtPoint, upVector);

	return (position);
}

/*
Descripton: changes the camera's position to a new position around a circle
Return:
Vector3f - position
*/

Vector3f Camera::computePosition()
{
	float x = radius * sin(angle);
	float z = radius * cos(angle);

	return changeAbsPosition(x, position.y, z);
}

/*
Descripton: changes the camera's position to a new position
Return:
Vector3f - position
*/

Vector3f Camera::changeAbsPosition(Vector3f* v)
{
	// set the position to the given position
	return changeAbsPosition(v->x, v->y, v->z);
}

/*
Purpose: changes the camera's position along angle
Descripton: move the camera forward by the numUnits along the circle

Return:
Vector3f - position
*/
Vector3f Camera::moveForward(float numUnits)
{
	radius -= numUnits;
	if (radius < 1) {
		radius = 1;
	}
	// update the abs position
	return computePosition();
}

/*
Purpose: changes the camera's position along angle
Descripton: move the camera backward by the numUnits along the circle

Return:
Vector3f - position
*/
Vector3f Camera::moveBackward(float numUnits)
{
	return(moveForward(-numUnits));
}

/*
Descripton: Update the orientation of the lookat vector and the up vector
Return:
0 - success
*/
int Camera::updateOrientation(Vector3f rotVector, float angleRad)
{
	Vector3f xaxis(0.0,0.0,0.0);
	Vector4f u;

	// create rotation matrix around the rotation vector
	rotMat = Matrix4f::rotateVector(rotVector, angleRad, 0);

	// rotate the camera 
	// rotate the up vector 
	u = rotMat*upVector;
	upVector = u.to3D();

	// rotate the lookAt vector
	u = rotMat*lookAtVector;
	lookAtVector = u.to3D();	// DN 26/10/2015

	// update the upVector
	// find the x-axis
	xaxis = Vector3f::cross(upVector, lookAtVector);

	// find the upVector
	upVector = Vector3f::cross(lookAtVector, xaxis);

	return 0;
}

/*
Descripton: obtains the view transformation matrix
Return:
Matrix4f - transformation matrix
*/
Matrix4f Camera::getViewMatrix(Matrix4f *viewMatrix)
{
	Vector3f lookAtPoint;
	Matrix4f m;

	lookAtPoint = position+lookAtVector;
	m = Matrix4f::cameraMatrix(position, lookAtPoint, upVector);
	if (viewMatrix != NULL) *viewMatrix = m;

	return(m);
}

/*
Descripton: set camera parameters
Return: void
*/
void Camera::setCamera(Vector3f position, Vector3f lookAtPoint, Vector3f upVector, float radius, float angle)
{
	// set the position
	this->radius = radius;
	this->angle = angle;
	this->position.y = position.y;

	// update the view matrix
	this->computePosition();

	// set the lookAtVector
	this->lookAtVector = Vector3f(0, lookAtPoint.y, 0) - position;

	// set the upVector
	this->upVector = upVector;

	// normalize the vectors
	this->upVector.normalize();
}

/*
Descripton: update camera speed
Return: 0 - success
*/
int Camera::updateSpeed(float speed)
{
	this->speed += speed;
	return 0;
}

/*
Descripton: get camera speed
Return: float - speed
*/
float Camera::getSpeed(void)
{
	return(speed);
}

/*
Descripton: change camera look-at vector
Return: 0 - success
*/
int Camera::changeLookAtVector(float x, float y, float z)
{
	// update the look at vector
	lookAtVector.x = x;
	lookAtVector.y = y;
	lookAtVector.z = z;

	// update the view matrix
	viewMat = Matrix4f::cameraMatrix(position, position + lookAtVector, upVector);

	return 0;
}

/*
Descripton: Moving the camera sideways to the right by numUnits
Return: Vector3f - position
*/
Vector3f Camera::moveRight(float numDegrees)
{
	angle += numDegrees;
	if (angle >= 360 || angle < 0) {
		angle = fmod(angle, 360);
	}
	// update the abs position
	return computePosition();
}

/*
Descripton: Moving the camera sideways to the left by numUnits
Return: Vector3f - position
*/
Vector3f Camera::moveLeft(float numDegrees)
{
	Vector3f pos = moveRight(-numDegrees);
	return(pos);
}

/*
Descripton: Moving the camera sideways to the right by numUnits
Return: Vector3f - position
*/
Vector3f Camera::moveUp(float numUnits)
{
	position.y += numUnits;
	// update the abs position
	return computePosition();
}

/*
Descripton: Moving the camera sideways to the left by numUnits
Return: Vector3f - position
*/
Vector3f Camera::moveDown(float numUnits)
{
	Vector3f pos = moveUp(-numUnits);
	return(pos);
}

/*
Descripton: zoom in small amount
Return: 0 - success
*/
int Camera::zoomIn(void)
{
	zoomIn(1);
	return 0;
}

/*
Descripton: zoom in by changing the field of view
Return: 0 - success
*/
int Camera::zoomIn(float zoom)
{
	fieldOfView -= zoom;
	if (fieldOfView <10) fieldOfView = 10;
	projMat = Matrix4f::symmetricPerspectiveProjectionMatrix(fieldOfView, aspectRatio, nearPlane, farPlane);
	return 0;
}

/*
Descripton: zoom out small amount
Return: 0 - success
*/
int Camera::zoomOut(void)
{
	zoomOut(1);
	return 0;
}

/*
Descripton: zoom in by changing the field of view
Return: 0 - success
*/
int Camera::zoomOut(float zoom)
{
	fieldOfView += zoom;
	if (fieldOfView > 150) fieldOfView = 150;
	projMat = Matrix4f::symmetricPerspectiveProjectionMatrix(fieldOfView, aspectRatio, nearPlane, farPlane);
	return 0;
}

/*
Descripton: set perspective view
Return: 0 - success
*/
int Camera::setPerspectiveView(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	this->fieldOfView = fieldOfView;
	this->aspectRatio = aspectRatio;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	projMat = Matrix4f::symmetricPerspectiveProjectionMatrix(fieldOfView, aspectRatio, nearPlane, farPlane);

	return 0;
}

/*
Descripton:obtains the projection transformation matrix
Return:
Matrix4f - transformation matrix
*/
Matrix4f Camera::getProjectionMatrix(Matrix4f *projMatrix)
{
	Matrix4f m;

	m = Matrix4f::symmetricPerspectiveProjectionMatrix(fieldOfView, aspectRatio, nearPlane, farPlane);
	if (projMatrix != NULL) *projMatrix = m;

	return(m);
}
