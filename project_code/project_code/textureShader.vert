#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 vtxPos;
in vec2 vtxCoord; //vertex texture coords
in vec4 vtxCol;

out Data{
	vec2 texCoord;
	vec4 color;
} Out;

void main(){
	//transform the vertex position
	vec4 pos = vec4(vtxPos, 1.0);
	gl_Position = projection * view * model * pos;
	
	// set the colour
	Out.color = vtxCol;
	Out.texCoord = vtxCoord;
}