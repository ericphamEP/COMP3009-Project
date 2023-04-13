#include "Solution.h"
#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char* argv[])
{
	// Instruction: Set objectFilePath to path to .obj file and materialFilePath to corresponding material file (image texture)

	//char objectFilePath[] = "./project_code//models/pikachu/source/model_170290017759.obj";
	//char materialFilePath[] = "./project_code//models/pikachu/source/texture_170290017759.jpg";

	// obj "./project_code//models/fat-pikachu/source/fat pikachu/pikachu gordo.obj"
	// mat ./project_code//models/fat-pikachu/textures/uvs pikachu 3.png

	//char objectFilePath[] = ;
	//char materialFilePath[] = ;

	char objectFile[] = "./project_code//models/haggord-hagrid-hd-remake-joke/source/Haggord Sketchfab.obj";
	char materialFile[] = "./project_code//models/haggord-hagrid-hd-remake-joke/textures/Hagrid_Coxinha_tex.png";
	
	char* objectFilePath = objectFile;
	char* materialFilePath = materialFile;


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
