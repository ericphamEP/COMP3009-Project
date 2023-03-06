#ifndef MODEL_HEADER
#define MODEL_HEADER 1


#include <vector>

#include "GL/nuss_math.h"


struct Vertex {
	Vertex() {
		 pos = col = Vector4f(0,0,0,1);
	}
	Vertex(const Vector4f& _pos);
	Vertex(const Vector4f _pos, const Vector4f _col){
		pos = _pos;
		col = _col;
	}

	Vector4f pos;
	Vector4f col;
};

typedef struct Vertex Vertex;

typedef std::vector<Vertex> Vertices;
typedef std::vector<unsigned int>	Indices;


#if 0
class Model {
public:
	Model();
	virtual ~Model() {};
	virtual void render();
protected:
	virtual void Create();
	Vertices    m_vertices;
	Indices		m_indices;

};
#endif
#endif