#version 330

in vec4 vtxPos;
in mat4 scaleMat;
attribute vec4 vtxColour;

out vec4 vColour;

void main(void){
	gl_Position = vec4(scaleMat*vtxPos);
	vColour = vtxColour;
}