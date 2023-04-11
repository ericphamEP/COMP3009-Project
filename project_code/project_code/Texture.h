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

	int loadTextureImage(char* imageFileName, GLuint texTarget);
	int loadTextureImages(char** texFileName);		// loads a cube texture images
	int loadColourTexture(void);					// loads a cube colour textures
	void bindToTextureUnit(GLuint textureType, int textureUnit);
	GLuint setTextureSampler(Shader shader, char* sampleName, GLuint textureUnit);

	GLuint getTexId();

private:
	GLuint textureId;
	int textureUnit;
	GLuint texTarget;	// target type;

};
