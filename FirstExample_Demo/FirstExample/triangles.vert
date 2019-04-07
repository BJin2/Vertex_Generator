#version 430 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexture;
layout(location = 2) in vec3 vNormal;

out vec2 texCoord;

//all these 3 in camera space
out vec3 N;//normal
out vec3 L;//light direction
out vec3 E;//eye direction

uniform highp mat4 MVP;
uniform highp mat4 M;
uniform highp mat4 V;
uniform vec3 lightPosition;

void main()
{
	texCoord = vTexture;

	vec3 vertexCamera = vec3(V*M*vec4(vPosition,1));
	E = vec3(0,0,0) - vertexCamera;
	N = vec3(V*M*vec4(vNormal, 0));
	vec3 LPC = (V * vec4(lightPosition, 1)).xyz;
	L = LPC + E;

	gl_Position = MVP * vec4(vPosition, 1.0f);
}
