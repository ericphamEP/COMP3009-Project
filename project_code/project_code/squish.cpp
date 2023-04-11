#include "squish.h"


void Squish::initGeom(char* filepath)
{
    paused = true;
    minSquishFactor = 0.5;
    maxSquishFactor = 1.0;
    setScaleMagnitude(0.035, 0.05, 0.035);
    setScaleFactor(2.5);
    GraphicsObject::initGeom(filepath);
}

void Squish::optimizeScale()
{
    float targetHeight = 45;
    float currHeight = topPosition-bottomPosition;
    //printf("%f\n", currHeight);
    float scale = targetHeight / currHeight;
    //printf("%f", scale);

    this->setScale(scale, scale, scale);
}

void Squish::setScale(float scaleX, float scaleY, float scaleZ)
{
    this->scale = Vector3f(scaleX, scaleY, scaleZ);
    this->initScale = Vector3f(scaleX, scaleY, scaleZ);
}

void Squish::updateSquish()
{
    if (!autoMode && paused) {
        return;
    }
    if (squishDown == true) {
        scale.y -= scale.y * scaleMagnitude.y * scaleFactor;
        scale.x += scale.x * scaleMagnitude.x * scaleFactor;
        scale.z += scale.z * scaleMagnitude.z * scaleFactor;

        if (scale.y <= (minSquishFactor * initScale.y)) {
            squishDown = false;
        }
    } else {
        scale.y += scale.y * scaleMagnitude.y * scaleFactor;
        scale.x -= scale.x * scaleMagnitude.x * scaleFactor;
        scale.z -= scale.z * scaleMagnitude.z * scaleFactor;

        if (scale.y >= (maxSquishFactor * initScale.y)) {
            scale = initScale;
            setScale(initScale.x, initScale.y, initScale.z);
            squishDown = true;
            if (!autoMode) {
                paused = true;
            }
        }
    }

    position.y = -bottomPosition * scale.y;
}

float Squish::getTopPosition()
{
    return position.y + (scale.y * (topPosition - bottomPosition));
}

int Squish::render(Shader shader)
{
    Matrix4f rotMat;  // rotation matrix;
    Matrix4f scaleMat; // scaling matrix;
    Matrix4f transMat;	// translation matrix
    Matrix4f modelMat;	// final model matrix

    // set the transformation matrix - the model transfomration
    modelMat = Matrix4f::identity();

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
    //modelMat = worldMat * modelMat;

    // move matrix to shader
    shader.copyMatrixToShader(modelMat, "model");

    // load the object materials
    loadMaterials(shader);

    // bind the vao
    glBindVertexArray(vao);

    // draw using indices
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);

    // unbind the vao
    glBindVertexArray(0);

    return 0;
}

void Squish::setScaleMagnitude(float x, float y, float z) {
    if (x > 0) { scaleMagnitude.x = x; }
    if (y > 0) { scaleMagnitude.y = y; }
    if (z > 0) { scaleMagnitude.z = z; }
    //printf("new scale magnitude: (%.3f, %.3f, %.3f)\n", scaleMagnitude.x, scaleMagnitude.y, scaleMagnitude.z);
}

void Squish::incrementScaleMagnitude(float x, float y, float z) {
    setScaleMagnitude(scaleMagnitude.x + x, scaleMagnitude.y + y, scaleMagnitude.z + z);
}

void Squish::setScaleFactor(float f) {
    if (f > 0) {
        scaleFactor = f;
    }
    //printf("new scale factor: %.2f\n", scaleFactor);
}

void Squish::incrementScaleFactor(float f) {
    setScaleFactor(scaleFactor + f);
}

void Squish::incrementMinSquishFactor(float f) {
    minSquishFactor += f;
    if (minSquishFactor < 0.2) {
        minSquishFactor = 0.2;
    } else if (minSquishFactor > 0.9) {
        minSquishFactor = 0.9;
    }
}

void Squish::incrementMaxSquishFactor(float f) {
    maxSquishFactor += f;
    if (maxSquishFactor < 1.0) {
        maxSquishFactor = 1.0;
    }
    else if (maxSquishFactor > 5.0) {
        maxSquishFactor = 5.0;
    }
}

void Squish::setAutoMode(bool m) {
    this->autoMode = m;
}

void Squish::toggleAutoMode() {
    if (autoMode) {
        setAutoMode(false);
    }
    else {
        setAutoMode(true);
        paused = false;
    }
}

void Squish::startSquish() {
    if (!autoMode) {
        this->paused = false;
    }
}