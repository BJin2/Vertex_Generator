#pragma once
#include "VertexGenerator.hpp"

class DrawableObject
{
// member variables
private : 
	GLuint* VAO;
	

public :
	Transform transform;
	int* num_index;
	TextureID id;

// methods
public :
	DrawableObject(int numCorner, Type type, TextureID id);
	DrawableObject(int numCorner, Type type, TextureID id, Transform t);
	GLuint* getVAO();
};