// main.cpp : Defines the entry point for the console application.
//

#include "Solution.h"



int main(int argc, char* argv[])
{

	//char objectFilePath[] = "./project_code//models/pikachu/source/model_170290017759.obj";
	//char materialFilePath[] = "./project_code/models/pikachu/textures/texture_170290017759.jpeg";

	char objectFilePath[] = "./project_code//models/fat-pikachu/source/fat pikachu/pikachu gordo.obj";
	char materialFilePath[] = "./project_code//models/fat-pikachu/textures/uvs pikachu 3.png";

	Solution sol;

	glutInit(&argc, argv);

	sol.initOpenGL();
	sol.initSolution(objectFilePath, materialFilePath);
	Solution::setSolution(&sol);
	

	glutMainLoop();
	return 0;
}

