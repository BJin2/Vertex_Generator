#version 430 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexture;
layout(location = 2) in vec3 vNormal;

out vec2 texCoord;

//all these 2 in camera space
out vec3 N;//normal
out vec3 E;//eye direction

uniform highp mat4 MVP;
uniform highp mat4 M;
uniform highp mat4 V;


void main()
{
	texCoord = vTexture;

	vec3 vertexCamera = vec3(V*M*vec4(vPosition,1));
	E = vec3(0,0,0) - vertexCamera;
	N = vec3(V*M*vec4(vNormal, 0));

	gl_Position = MVP * vec4(vPosition, 1.0f);
}
