#pragma once
#ifndef SHADER_HEADER
#define SHADER_HEADER
#include "GL/glew.h"
#include "GL/glut.h"
#include "geometry_common.h"
#include "GL/nuss_math.h"

class Shader
{
public:
	Shader() {};
	~Shader() {
		glDeleteProgram(this->id);
	};

	int readCode(char*, char**, int*); //filename, file output, length
	int createShaders(char *vtxShader, char *fragShader); //vertex shader filename, fragment shader filename

	GLuint getShaderId();
	GLuint vbo;
	GLuint vma;
	GLuint ebo;

private:
	GLuint id; //the shader program id

	//void linkProgram(GLuint, GLuint, GLuint);
};

#endif

