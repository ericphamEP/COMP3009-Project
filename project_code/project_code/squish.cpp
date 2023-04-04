#include "squish.h"


void Squish::initGeom(char* filepath)
{
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


void Squish::updateSquish(float factor)
{
    if (squishDown == true) {
        scale.y -= scale.y * 0.05 * factor;
        scale.x += scale.x * 0.035 * factor;
        scale.z += scale.z * 0.035 * factor;

        if (scale.y < (0.5 * initScale.y)) {
            squishDown = false;
        }
    } else {
        scale.y += scale.y * 0.05 * factor;
        scale.x -= scale.x * 0.035 * factor;
        scale.z -= scale.z * 0.035 * factor;

        if (scale.y >= initScale.y) {
            scale = initScale;
            setScale(initScale.x, initScale.y, initScale.z);
            squishDown = true;
        }
    }

    position.y = -bottomPosition * scale.y;
}


float Squish::getTopPosition()
{

    return position.y + (scale.y * (topPosition - bottomPosition));
}




/**************************************************************************************/

// Render the Cube

int Squish::render()
{
    int i;
    int vtxIndex;
    Vector4f p;
    Vector4f c;

    Matrix4f scaleMat; // scaling matrix;
    Matrix4f transMat;	// translation matrix
    Matrix4f modelMat;	// final model matrix
    Matrix4f trMat;	// world matrix

    modelMat = Matrix4f::identity();

    // set the translation - this is model space to world space transformation
    transMat = Matrix4f::translation(position);
    modelMat = transMat * modelMat;

    // set the scaling - this is model space to model space transformation
    scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
    modelMat = scaleMat * modelMat;

    // compute the transaformation and store it in trMat
    trMat = worldMat * modelMat;


    glBegin(GL_TRIANGLES);
    for (i = 0; i < m_indices_tri.size(); ++i) {
        // get the vertex index which will simplify the coding
        vtxIndex = m_indices_tri.at(i);

        // set the vertex colour.  Use the vtxIndex to access the correct vertex
        //c = m_vertices[vtxIndex].col;

        // compute the vertex transformation and store it in p
        //printf("triii %d\n", vtxIndex);
        p = trMat * m_vertices.at(vtxIndex).pos;

        // add the vertex to the triangle list
        //glColor3f(c.x, c.y, c.z);
        glVertex3f(p.x, p.y, p.z);

    }
    glEnd();

    glBegin(GL_QUADS);
    for (i = 0; i < m_indices_quad.size(); ++i) {
        // get the vertex index which will simplify the coding
        vtxIndex = m_indices_quad.at(i);

        // set the vertex colour.  Use the vtxIndex to access the correct vertex
        //c = m_vertices[vtxIndex].col;

        // compute the vertex transformation and store it in p
        //printf("quadd %d\n", vtxIndex);
        p = trMat * m_vertices.at(vtxIndex).pos;

        // add the vertex to the triangle list
        //glColor3f(c.x, c.y, c.z);
        glVertex3f(p.x, p.y, p.z);

    }
    glEnd();

    
    for (i = 0; i < m_indices_pent.size(); ++i) {
        glBegin(GL_POLYGON);
        // get the vertex index which will simplify the coding
        vtxIndex = m_indices_pent.at(i);

        // set the vertex colour.  Use the vtxIndex to access the correct vertex
        //c = m_vertices[vtxIndex].col;

        // compute the vertex transformation and store it in p
        //printf("quadd %d\n", vtxIndex);
        p = trMat * m_vertices.at(vtxIndex).pos;

        // add the vertex to the triangle list
        //glColor3f(c.x, c.y, c.z);
        glVertex3f(p.x, p.y, p.z);
        glEnd();
    }

    return(0);
}

int Squish::render(Shader shader)
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