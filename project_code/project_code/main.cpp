// main.cpp : Defines the entry point for the console application.
//

#include "Solution.h"



int main(int argc, char* argv[])
{

	char objectFilePath[] = "H:\\Downloads\\School\\Year5\\comp3009\\project\\models\\pikachu\\source\\pikaku\\model_170290017759.obj";

	Solution sol;

	glutInit(&argc, argv);

	sol.initOpenGL();
	sol.initSolution(objectFilePath);
	Solution::setSolution(&sol);
	

	glutMainLoop();
	return 0;
}

