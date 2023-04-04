#include "Hand.h"


void Hand::initGeom()
{
    char filepath[] = "./project_code/models/female-hand/source/038F_05SET_04SHOT/038F_05SET_04SHOT.OBJ";
    GraphicsObject::initGeom(filepath);
}

/*void Hand::initGeom()
{
    bottomPosition = NULL;
    float vtx[8][4] = { {-1, -1, -1, 1},{1, -1, -1, 1},
                       {1, -1, 1, 1}, {-1, -1, 1, 1},
                       {-1, 1, -1, 1}, {1, 1, -1, 1},
                       {1, 1, 1, 1}, {-1, 1, 1, 1}
    };

    float col[8][4] = { {1, 0, 0, 1},{0, 1, 0, 1},
                        {0, 0, 1, 1}, {1, 1, 0, 1},
                        {1, 0, 1, 1}, {0, 1, 1, 1},
                        {0.5, 0.5, 0, 1}, {0.5, 0, 0.5, 1}
    };


    // note that is an implicit memory allocation with respect to the  initialization
    // complete the faces assignment.  Note the first face (front face was added as an
    // example
    int indices[] = {
        // front face
        0, 1, 4,
        1, 5, 4,

        // top face
        4, 6, 5,
        6, 7, 4,

        // back face
        7, 6, 3,
        6, 3, 2,

        // bottom face
        0, 3, 1,
        1, 2, 3,

        // left face
        0, 4, 7,
        0, 3, 7,

        // right face
        5, 1, 2,
        2, 6, 5

    };
    // using a for loop push the vertex information into the m_vertices structure 
    // by invoking the  m_vertices.push_back() function.
    // note that you will have to assemble the data for each vertex (i.e., pos and col)


    // add code
    for (int i = 0; i < 8; i++) {
        m_vertices.push_back(
            VERTEX(
                Vector3f(vtx[i][0], vtx[i][1], vtx[i][2]),
                Vector4f(col[i][0], col[i][1], col[i][2], col[i][3])
            ));

        if (bottomPosition == NULL || bottomPosition > vtx[i][1]) {
            bottomPosition = vtx[i][1];
        }
    }

    // using a for loop push the indices information of the triagnle list into the 
    //  m_vertices structure 

     // add code
    for (int i = 0; i < 36; i++) {
        m_indices_tri.push_back(indices[i]);
    }

    // set position to 'floor'
    position = Vector3f(0, -bottomPosition, 0);

}*/


void Hand::setHeightPosition(float height)
{
    this->setWorldPosition(Vector3f(worldPosition.x, height, worldPosition.z));
}


/**************************************************************************************/

// Render the Cube

int Hand::render()
{
    int i;
    int vtxIndex;
    Vector4f p;
    Vector4f c;

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

    // compute the transaformation and store it in trMat
    transMat = worldMat * modelMat;


    glBegin(GL_TRIANGLES);
    for (i = 0; i < m_indices_tri.size(); ++i) {
        // get the vertex index which will simplify the coding
        vtxIndex = m_indices_tri.at(i);

        // set the vertex colour.  Use the vtxIndex to access the correct vertex
        //c = m_vertices[vtxIndex].col;

        // compute the vertex transformation and store it in p
        //printf("triii %d\n", vtxIndex);
        p = transMat * m_vertices.at(vtxIndex).pos;

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
        p = transMat * m_vertices.at(vtxIndex).pos;

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
        p = transMat * m_vertices.at(vtxIndex).pos;

        // add the vertex to the triangle list
        //glColor3f(c.x, c.y, c.z);
        glVertex3f(p.x, p.y, p.z);
        glEnd();
    }

    return(0);
}

int Hand::render(Shader shader)
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
