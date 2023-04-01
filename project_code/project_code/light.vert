#version 330 core

struct fragData{
	vec3 normal;
	vec3 worldPos; 
	vec4 colour;
} ;

uniform mat4 view; 
uniform mat4 model; 
uniform mat4 projection;

in vec4 vtxPos;
in vec4 vtxCol;
in vec3 vtxNormal;

out fragData frag;

void main(){

	// transform the vertex position
	frag.worldPos = vec3(model * vtxPos);

	// transform the normal
	frag.normal = mat3(transpose(inverse(model))) * vtxNormal;

	// get the colour
	frag.colour = vtxCol;
	
	// set the output to the fragment shader
	gl_Position = projection * view * model * vtxPos;
}