#pragma once

#include "GL/glew.h"
#include "GL/glut.h"
#include "geometry_common.h"
#include "Shader.h"


class Texture
{

public:
	Texture();
	~Texture();
	void loadTexture(const char* imgFileName, GLuint textureTarget);
	void bindToTextureUnit(int texUnit);
	void setTextureSampler(Shader shader, const char *sampleName, GLuint samplerId);

private:
	GLuint textureId;
	int textureUnit;

};
