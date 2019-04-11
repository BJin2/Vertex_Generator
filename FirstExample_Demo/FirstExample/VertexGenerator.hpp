#pragma once
#include "vgl.h"
#include "glm\glm.hpp"

struct Transform
{
	glm::vec3	position;
	glm::vec3	rotationAxis;
	float		rotationAngle;
	glm::vec3	scale;

	Transform();
	Transform(glm::vec3 pos, glm::vec3 axis, float angle, glm::vec3 scl);
};

enum Type
{
	Column,
	Cone,
	Plane,
	Star
};

enum TextureID
{
	Brick
};

namespace VertexGenerator
{
	GLfloat* CreateShape(int numCorner);
	GLuint* CreateColumn(int numCorner, TextureID id, int* numIndex);
	GLuint* CreateCone(int numCorner, TextureID id, int* numIndex);
	//GLuint* CreatePlane(int numCorner, TextureID id, int* numIndex);
	//GLuint* CreateStar(int numCorner, TextureID id, int* numIndex);
};