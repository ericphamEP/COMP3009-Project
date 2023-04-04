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

in vec3 vtxPos;
in vec4 vtxCol;
in vec3 vtxNormal;
in vec2 vtxCoord;

out fragData frag;

void main(){

	// transform the vertex position
	frag.worldPos = vec3(model * vec4(vtxPos, 1.0));

	// transform the normal
	frag.normal = vtxNormal;

	// get the colour
	frag.colour = vtxCol;

	//get the texture coordinates
	frag.texCoords = vtxCoord;
	
	// set the output to the fragment shader
	gl_Position = projection * view * model * vec4(vtxPos, 1.0);
}