#version 330 core

struct fragData{
	vec3 normal;
	vec3 worldPos; 
	vec4 colour;
	vec2 texCoords;
} ;

uniform mat4 view; 
uniform mat4 model; 
uniform mat4 projection;

in vec4 vtxPos;
in vec4 vtxCol;
in vec3 vtxNormal;
in vec2 vtxCoords;

out fragData frag;

void main(){

	// transform the vertex position
	frag.worldPos = vec3(model * vtxPos);

	// transform the normal
	frag.normal = vtxNormal;

	// get the colour
	frag.colour = vtxCol;

	//get the texture coordinates
	frag.texCoords = vtxCoords;
	
	// set the output to the fragment shader
	//gl_Position = projection * view * model * vtxPos;
	gl_Position = projection * view * vtxPos;
}