#version 330

uniform sampler2D texSampler;

in Data{
	vec2 texCoord;
	vec4 color;
}In;

out vec4 color;

void main() {
	color = texture2D(texSampler1, In.texCoord);
}