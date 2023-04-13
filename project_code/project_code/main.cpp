#include "Solution.h"
#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char* argv[])
{
	// Instruction: Set path to .obj file (with line header 'obj') and corresponding material/image texture file (with line header 'mat') in modelpath.txt

	// Below: included models you can paste into modelpath.txt
	// 
	// Pikachu pillow
	// Object file: obj ./project_code//models/pikachu/source/model_170290017759.obj
	// Texture: mat ./project_code//models/pikachu/source/texture_170290017759.jpg
	// 
	// Fat Pikachu
	// Object file: obj ./project_code//models/fat-pikachu/source/fat pikachu/pikachu gordo.obj
	// Texture: mat ./project_code//models/fat-pikachu/textures/uvs pikachu 3.png
	// 
	// Low Poly Hagrid
	// Object file: obj ./project_code//models/haggord-hagrid-hd-remake-joke/source/Haggord Sketchfab.obj
	// Texture: mat ./project_code//models/haggord-hagrid-hd-remake-joke/textures/Hagrid_Coxinha_tex.png
	
	char* objectFilePath = NULL;
	char* materialFilePath = NULL;


	std::ifstream in("./project_code//models/modelpath.txt", std::ios::in);
	if (!in) {
		printf("WARNING: modelpath.txt not found in /project_code/models, cannot render the desired model\n");
		return 0;

	}

	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 3) == "obj") {
			//int length = sscanf_s(line.c_str(), "obj %s\n", objectFilePath, 100);
			line.erase(0, 4);
			objectFilePath = new char[line.length() + 1];
			strcpy_s(objectFilePath, line.length() + 1, line.c_str());
			printf("OBJ File: %s\n", objectFilePath);
		}
		else if (line.substr(0, 3) == "mat") {
			//int length = sscanf_s(line.c_str(), "mat %s\n", materialFilePath, 100);
			line.erase(0, 4);
			materialFilePath = new char[line.length() + 1];
			strcpy_s(materialFilePath, line.length() + 1, line.c_str());
			printf("TEX File: %s\n", materialFilePath);
		}
	}
	Solution sol;

	//printf("OBJ File: %s\n", objectFilePath);
	//printf("TEX File: %s\n", materialFilePath);
	glutInit(&argc, argv);

	sol.initOpenGL();
	sol.initSolution(objectFilePath, materialFilePath);
	Solution::setSolution(&sol);

	glutMainLoop();
	return 0;
}
