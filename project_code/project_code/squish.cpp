#include "squish.h"
#include <iostream>
#include <fstream>
#include <string>


void Squish::initGeom(char* filepath)
{
    m_vertices.reserve(1000000);
    m_indices_tri.reserve(1000000);
    m_indices_quad.reserve(1000000);
    m_indices_pent.reserve(1000000);

    std::ifstream in(filepath, std::ios::in);
    if (!in) {
        printf("WARNING: Invalid filepath\n");
        return;

    }
    std::string line;
    while (std::getline(in, line)) {
        // vertices
        if (line.substr(0, 2) == "v ") {
            Vertex vertex;
            int matches = sscanf_s(line.c_str(), "v %f %f %f\n", &vertex.pos.x, &vertex.pos.y, &vertex.pos.z);
            if (matches != 3) {
                printf("WARNING: Cannot parse vertices.\n");
            }
            
            m_vertices.push_back(vertex);
        } else if (line.substr(0, 2) == "vt") { //check for texture co-ordinate

            //todo

        } else if (line.substr(0, 2) == "vn") { //check for vertex nornmal

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
                for (int i = 0; i < 4; i++) {
                    m_indices_quad.push_back(v[i] - 1);
                }
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

}





/**************************************************************************************/

// Render the Cube

int Squish::render()
{
    int i;
    int vtxIndex;
    Vector4f p;
    Vector4f c;

    Matrix4f trMat;	// world matrix

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
