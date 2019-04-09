#pragma once
#include "VertexGenerator.hpp"

class DrawableObject
{
// member variables
private : 
	GLuint* VAO;
	TextureID id;

public :
	Transform transform;
	int* num_index;

// methods
public :
	DrawableObject(int numCorner, Type type, TextureID id);
	GLuint* getVAO();
};