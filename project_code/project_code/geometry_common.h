
/* FILE IS geometry_common.h 

This file contains the strucure of a vertex.



REVISIONS:
1. Created: 2012  Doron Nussbaum
2. October 26, 2015 Doron Nussbaum - Changed the vertex geometry from 4 dimensions to 3 dimensions. 



*/


#ifndef GEOMETRY_COMMON
#define GEOMETRY_COMMON 1


/*******************************************************************/
// INCLUDE FILES
#include <vector>
#include "GL/nuss_math.h"

/*******************************************************************/

// DEFGINES

#define VERTEX_DIMENSIONS 3

/*******************************************************************/

// STRUCTURES

struct Vertex {
	Vertex(){}
	//Vertex(const Vector4f& _pos);
	Vertex(const Vector3f& _pos);
	Vertex(const Vector3f _pos, const Vector4f _col){
		memcpy((void *)&pos, (void *)&_pos, sizeof(pos));
		memcpy((void *)&col, (void *)&_col, sizeof(col));
	}

	Vector3f pos;

	//float pos[VERTEX_DIMENSIONS];
	Vector4f col;
};

typedef struct Vertex VERTEX;



typedef std::vector<Vertex> Vertices;
typedef std::vector<unsigned int>	Indices;

#endif