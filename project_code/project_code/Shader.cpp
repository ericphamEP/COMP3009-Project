#include "Shader.h"

int Shader::readCode(char* fileName, char** shaderCode, int* codeLength)
{
	int length = 0;
	FILE* fp = NULL;
	int rc = 0;
	// check for error in file name
	fopen_s(&fp, fileName, "r");	// open file and check for errors
	if (fp == NULL) {
		rc = -1;
		goto err;
	}

	// find the length of code
	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	rewind(fp);		// could use fseek(fp, 0L, SEEK_SET)
	if (length <= 0) {
		rc = -2;
		goto err;
	}

	if (length > 0) {
		// allocated space for code and check for errors
		*shaderCode = (char*)malloc(length + 1);	// add a space for the '\0'
		if (*shaderCode == NULL) return(-2);
		memset((void*)*shaderCode, 0, length + 1);
		fread((void*)*shaderCode, sizeof(char), length, fp);
		(*shaderCode)[length] = 0;
	}

	if (codeLength != NULL) *codeLength = length;

err:
	if (fp != NULL) fclose(fp);

	return(rc);
}

int Shader::createShaders(char *vertexShaderFileName, char *fragShaderFileName) {
	int rc = 0;
	char* shaderCode[1];
	int codeLength = 0;

	GLuint vtxShader = -1;
	GLuint fragShader = -1;
	GLuint shaderId = -1;


	id = -1;

	// create a vertex shader
	vtxShader = glCreateShader(GL_VERTEX_SHADER);

	shaderCode[0] = NULL;

	// read and compile the vertex shader
	rc = readCode(vertexShaderFileName, &shaderCode[0], &codeLength);

	// check for error reading the code
	if (rc != 0) {
		rc = -1;
		goto err;
	}

	// transfer the shader source to OpenGL
	glShaderSource(vtxShader, 1, shaderCode, 0);

	// compile the shader
	glCompileShader(vtxShader);

	// check for errors
	glGetShaderiv(vtxShader, GL_COMPILE_STATUS, &rc);
	if (rc != GL_TRUE) {
		char errorLog[2048];
		glGetShaderInfoLog(vtxShader, sizeof(errorLog) - 1, NULL, errorLog);
		fprintf(stderr, "Error when creating the vertex Shader - %s \n", errorLog);
	}


	// free the allocated shader code

	// create a fragment shader 
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);


	// read the fragment shader code
	rc = readCode(fragShaderFileName, &shaderCode[0], &codeLength);

	// transfer the shader code to OpenGL
	glShaderSource(fragShader, 1, shaderCode, 0);

	// compile the code
	glCompileShader(fragShader);

	// check for errors
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &rc);
	if (rc != GL_TRUE) {
		char errorLog[2048];
		glGetShaderInfoLog(fragShader, sizeof(errorLog) - 1, NULL, errorLog);
		fprintf(stderr, "Error when creating the fragment Shader - %s \n", errorLog);
	}

	// free the shader code

	// create a shader program
	shaderId = glCreateProgram();

	// attach the shaders to the program
	glAttachShader(shaderId, vtxShader);
	glAttachShader(shaderId, fragShader);

	// link the program
	glLinkProgram(shaderId);

	// check for errors
	glGetProgramiv(shaderId, GL_LINK_STATUS, &rc);
	if (rc != GL_TRUE) {
		char errorLog[2048];
		glGetProgramInfoLog(shaderId, sizeof(errorLog) - 1, NULL, errorLog);
		fprintf(stderr, "Shader program(id = % d) linking error : '%s'\n", shaderId, errorLog);
	}

	// set the output shader program
	id = shaderId;


	rc = 0;
err:
	if (shaderCode[0] != NULL) free(shaderCode[0]);

	// release the vertex shader
	if (vtxShader != -1) {
		glDeleteShader(vtxShader);
		if (shaderId != -1) glDetachShader(shaderId, vtxShader);
	}

	// release the fragment shader
	if (fragShader != -1) {
		glDeleteShader(fragShader);
		if (shaderId != -1) glDetachShader(shaderId, fragShader);
	}
	return(rc);
}

GLuint Shader::getShaderId() {
	return id;
}