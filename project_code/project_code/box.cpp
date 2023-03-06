#include "Box.h"




void Box::initGeom() 
{
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
            Vertex(
                Vector4f(vtx[i][0], vtx[i][1], vtx[i][2], vtx[i][3]),
                Vector4f(col[i][0], col[i][1], col[i][2], col[i][3])
            ));
    }

   // using a for loop push the indices information of the triagnle list into the 
   //  m_vertices structure 

    // add code
    for (int i = 0; i < 36; i++) {
        m_indices.push_back(indices[i]);
    }

}





/**************************************************************************************/

// Render the Cube

int Box::render()
{
    int i;
    int vtxIndex;
    Vector4f p;
    Vector4f c;

    Matrix4f trMat;	// world matrix
    
    // compute the transaformation and store it in trMat
    trMat = worldMat * modelMat;
 
 
    glBegin(GL_TRIANGLES);
    for (i = 0; i < m_indices.size(); ++i) {
        // get the vertex index which will simplify the coding
        vtxIndex = m_indices[i];

        // set the vertex colour.  Use the vtxIndex to access the correct vertex
        c = m_vertices[vtxIndex].col;
 
        // compute the vertex transformation and store it in p
        p = trMat * m_vertices[vtxIndex].pos;

        // add the vertext to the triangle list
        glColor3f(c.x, c.y, c.z);
        glVertex3f(p.x, p.y, p.z);

    }
    glEnd();

    return(0);
}



