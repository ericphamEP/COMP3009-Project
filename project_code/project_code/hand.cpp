#include "Hand.h"


void Hand::initGeom()
{
    char filepath[] = "./project_code/models/female-hand/source/038F_05SET_04SHOT/038F_05SET_04SHOT.OBJ";
    GraphicsObject::initGeom(filepath);
}

void Hand::setHeightPosition(float height)
{
    this->setWorldPosition(Vector3f(worldPosition.x, height, worldPosition.z));
}

int Hand::render(Shader shader)
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

    modelMat = worldMat * modelMat;
    //computeModelMat();
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
