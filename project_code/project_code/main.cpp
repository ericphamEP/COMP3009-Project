#include "Solution.h"


int main(int argc, char* argv[])
{
	// Instruction: Set objectFilePath to path to .obj file and materialFilePath to corresponding material file (image texture)

	//char objectFilePath[] = "./project_code//models/pikachu/source/model_170290017759.obj";
	//char materialFilePath[] = "./project_code//models/pikachu/source/texture_170290017759.jpg";

	//char objectFilePath[] = "./project_code//models/fat-pikachu/source/fat pikachu/pikachu gordo.obj";
	//char materialFilePath[] = "./project_code//models/fat-pikachu/textures/uvs pikachu 3.png";

	char objectFilePath[] = "./project_code//models/haggord-hagrid-hd-remake-joke/source/Haggord Sketchfab.obj";
	char materialFilePath[] = "./project_code//models/haggord-hagrid-hd-remake-joke/textures/Hagrid_Coxinha_tex.png";

	Solution sol;

	glutInit(&argc, argv);

	sol.initOpenGL();
	sol.initSolution(objectFilePath, materialFilePath);
	Solution::setSolution(&sol);

	glutMainLoop();
	return 0;
}
