#include "Texture.h"
#include "GL/SOIL.h"


Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::loadTexture(const char* imgFileName, GLuint textureTarget) {
	int width, height; 
	unsigned char* image = NULL;
	
	//generate textures
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	//load image
	image = SOIL_load_image(imgFileName, &width, &height, 0, SOIL_LOAD_RGB);

	//connect image to texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	//image stored with shader -> can delete image
	SOIL_free_image_data(image);
	image = NULL;

	//set repeat behaviour
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//set sampling behaviour
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bindToTextureUnit(int texUnit){
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::setTextureSampler(Shader shader, const char *sampleName, GLuint samplerId){
	GLuint location = glGetUniformLocation(shader.getProgId(), sampleName);
	glUniform1i(location, samplerId - GL_TEXTURE0);
}
