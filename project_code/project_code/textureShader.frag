#version 330

uniform sampler2D texSampler;

in Data{
	vec2 texCoord;
	vec4 color;
}In;

out vec4 color;

void main() {
	vec2 textureCoordinates = vec2(In.texCoord.x, 1.0-In.texCoord.y);
	color = texture2D(texSampler, textureCoordinates);
}