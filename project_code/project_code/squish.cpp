#include "squish.h"

void Squish::initGeom(char* filepath)
{

    FILE* fp = NULL;
    // check for error in file name
    errno_t err = fopen_s(&fp, filepath, "r");	// open file and check for errors
    if (err != 0) {
        printf("WARNING: Invalid filepath\n");
        return;
    }

    while (1) {

        char header[128];
        // first word of the line
        int res = fscanf_s(fp, "%s", &header, sizeof(header));
        if (res == EOF) {
            break;
        }

        printf("%s %d\n", header, sizeof(header));

        // parse header
        if (strcmp(header, "v") == 0) { // vertex
            Vertex vertex;
            int matches = fscanf_s(fp, "%f %f %f\n", &vertex.pos.x, &vertex.pos.y, &vertex.pos.z);
            if (matches != 3) {
                printf("WARNING: Cannot parse vertices.\n");
            }
            printf("%f %f %f\n", vertex.pos.x, vertex.pos.y, vertex.pos.z);
            m_vertices.push_back(vertex);
        }
        else if (strcmp(header, "f") == 0) { // face
            unsigned int v[4], vt[4], vn[4];
            int matches = fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &v[0], &vt[0], &vn[0], &v[1], &vt[1], &vn[1], &v[2], &vt[2], &vn[2], &v[3], &vt[3], &vn[3]);
            if (matches == 9) {
                for (int i = 0; i < 3; i++) {
                    m_indices_tri.push_back(v[i]-1);
                }
            }
            else if (matches == 16) {
                for (int i = 0; i < 4; i++) {
                    m_indices_quad.push_back(v[i]-1);
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
        vtxIndex = m_indices_tri[i];

        // set the vertex colour.  Use the vtxIndex to access the correct vertex
        //c = m_vertices[vtxIndex].col;

        // compute the vertex transformation and store it in p
        p = trMat * m_vertices[vtxIndex].pos;

        // add the vertex to the triangle list
        glColor3f(c.x, c.y, c.z);
        glVertex3f(p.x, p.y, p.z);

    }
    glEnd();

    glBegin(GL_QUADS);
    for (i = 0; i < m_indices_quad.size(); ++i) {
        // get the vertex index which will simplify the coding
        vtxIndex = m_indices_quad[i];

        // set the vertex colour.  Use the vtxIndex to access the correct vertex
        //c = m_vertices[vtxIndex].col;

        // compute the vertex transformation and store it in p
        p = trMat * m_vertices[vtxIndex].pos;

        // add the vertex to the triangle list
        //glColor3f(c.x, c.y, c.z);
        glVertex3f(p.x, p.y, p.z);

    }
    glEnd();

    return(0);
}



