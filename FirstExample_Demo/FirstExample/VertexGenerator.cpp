#include "VertexGenerator.hpp"
#include <iostream>

Transform::Transform()
{
	position = glm::vec3(0);
	rotationAxis = glm::vec3(0, 1, 0);
	rotationAngle = 0.0f;
	scale = glm::vec3(1);
}
Transform::Transform(glm::vec3 pos, glm::vec3 axis, float angle, glm::vec3 scl)
{
	position = pos;
	rotationAxis = axis;
	rotationAngle = angle;
	scale = scl;
}

GLfloat * VertexGenerator::CreateShape(int numCorner)
{
	float angle = 360.0f / (float)numCorner;
	GLfloat* tempPos = new GLfloat[numCorner * 2];

	for (int i = 0; i < numCorner * 2; i += 2)
	{
		float curAngle = (i / 2) * angle *-1;
		float curRad = glm::radians(curAngle);
		//*/
		if (curAngle == 180 || curAngle == -180)
			tempPos[i] = 0.0f;
		else
			tempPos[i] = glm::sin(curRad);

		if (curAngle == 90 || curAngle == 270 || curAngle == -90 || curAngle == -270)
			tempPos[i + 1] = 0.0f;
		else
			tempPos[i + 1] = glm::cos(curRad);
		/*/
		tempPos[i] = glm::sin(curAngle);
		tempPos[i + 1] = glm::cos(curAngle);
		//*/
		std::cout << curAngle << std::endl;
		std::cout << " X : " << tempPos[i] << ", Y : " << tempPos[i + 1] << std::endl;
	}

	return tempPos;
}

GLuint * VertexGenerator::CreateCone(int numCorner, TextureID id, int * numIndex)
{
	GLfloat* tempPos = VertexGenerator::CreateShape(numCorner);

	int numVertex = (numCorner * 3) + (numCorner * 3);
	int numberIndex = (numCorner * 3) + (numCorner * 3);
	GLfloat* vertices_plane = new GLfloat[numVertex * 3];
	GLfloat* tex_plane = new GLfloat[numVertex * 2];
	GLfloat* normal_plane = new GLfloat[numVertex * 3];
	GLushort* index_array_plane = new GLushort[numCorner*numCorner * 6];

	int index = 0;
	int index_uv = 0;
	int index_indexArr = 0;
	float difference = 1.0f / (float)numCorner;

	//Bottom
	for (int i = 0; i < numCorner* 2; i+= 2)
	{
		vertices_plane[index] = tempPos[i % (numCorner * 2)];
		vertices_plane[index + 1] = -0.5f;
		vertices_plane[index + 2] = tempPos[(i + 1) % (numCorner * 2)];

		vertices_plane[index + 3] = tempPos[(i + 2) % (numCorner * 2)];
		vertices_plane[index + 4] = -0.5f;
		vertices_plane[index + 5] = tempPos[(i + 3) % (numCorner * 2)];

		vertices_plane[index + 6] = 0.0f;
		vertices_plane[index + 7] = -0.5f;
		vertices_plane[index + 8] = 0.0f;

		normal_plane[index] = 0.0f;
		normal_plane[index + 1] = 0.0f;
		normal_plane[index + 2] = -1.0f;

		//tex_plane[index_uv] = j * difference;
		//tex_plane[index_uv + 1] = 1 - i * difference;

		index += 9;
		//index_uv += 2;
	}
	int tempIndex = index;
	//Vertex
	for (int i = 0; i < numCorner * 2; i+=2)
	{
		vertices_plane[index] = tempPos[i % (numCorner * 2)];
		vertices_plane[index + 1] = -0.5f;
		vertices_plane[index + 2] = tempPos[(i + 1) % (numCorner * 2)];

		vertices_plane[index + 3] = tempPos[(i + 2) % (numCorner * 2)];
		vertices_plane[index + 4] = -0.5f;
		vertices_plane[index + 5] = tempPos[(i + 3) % (numCorner * 2)];

		vertices_plane[index + 6] = 0.0f;
		vertices_plane[index + 7] = 0.5f;
		vertices_plane[index + 8] = 0.0f;

		normal_plane[index] = 0.0f;
		normal_plane[index + 1] = 0.0f;
		normal_plane[index + 2] = 1.0f;

		//tex_plane[index_uv] = j * difference;
		//tex_plane[index_uv + 1] = 1 - i * difference;

		index += 9;
		//index_uv += 2;
	}

	GLuint* VAO = new GLuint();
	glGenVertexArrays(1, VAO);
	glBindVertexArray(*VAO);

	// buffer for vertex
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 3 * sizeof(GLfloat), vertices_plane, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// buffer for texture coordinate
	GLuint UBO;
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_ARRAY_BUFFER, UBO);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 2 * sizeof(GLfloat), tex_plane, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// buffer for normal
	GLuint NBO;
	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 3 * sizeof(GLfloat), normal_plane, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// buffer for index
	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberIndex * sizeof(GLushort), index_array_plane, GL_STATIC_DRAW);
	*numIndex = numberIndex;
	return VAO;
}

GLuint * VertexGenerator::CreateColumn(int numCorner, TextureID id, int * numIndex)
{
	
	GLfloat* tempPos = VertexGenerator::CreateShape(numCorner);
	// will be replaced with proper vertex calculation
#pragma region Temp
	int numVertex = (numCorner + 1)*(numCorner + 1);
	int numberIndex = (numCorner*numCorner * 6);
	GLfloat* vertices_plane = new GLfloat[numVertex * 3];
	GLfloat* tex_plane = new GLfloat[numVertex * 2];
	GLfloat* normal_plane = new GLfloat[numVertex * 3];

	GLushort* index_array_plane = new GLushort[numCorner*numCorner * 6];

	int index = 0;
	int index_uv = 0;
	int index_indexArr = 0;
	float difference = 1.0f / (float)numCorner;


#pragma region EachVertex
	//Calculate vertex position, normal and UV coordinate
	for (int i = 0; i < numCorner + 1; i++)
	{
		for (int j = 0; j < numCorner + 1; j++)
		{
			vertices_plane[index] = -0.5f + (j*difference);
			vertices_plane[index + 1] = -0.5f + (i*difference);
			vertices_plane[index + 2] = 0.0f;

			normal_plane[index] = 0.0f;
			normal_plane[index + 1] = 0.0f;
			normal_plane[index + 2] = 1.0f;

			tex_plane[index_uv] = j * difference;
			tex_plane[index_uv + 1] = 1 - i * difference;

			index += 3;
			index_uv += 2;
		}
	}

#pragma endregion

#pragma region Index_Array
	for (int i = 0; i < numCorner; i++)
	{
		for (int j = 0; j < numCorner; j++)
		{
			//triangle 1
			index_array_plane[index_indexArr] = (i * (numCorner + 1)) + j; // left bottom
			index_array_plane[index_indexArr + 1] = (i*(numCorner + 1)) + (j + 1); // right bottom
			index_array_plane[index_indexArr + 2] = ((i + 1)*(numCorner + 1)) + (j + 1);// right top

			//triangle 2
			index_array_plane[index_indexArr + 3] = ((i + 1)*(numCorner + 1)) + (j + 1);// right top
			index_array_plane[index_indexArr + 4] = ((i + 1)*(numCorner + 1)) + j;// left top
			index_array_plane[index_indexArr + 5] = (i * (numCorner + 1)) + j;// left bottom

			index_indexArr += 6;
		}
	}
#pragma endregion
#pragma endregion

	GLuint* VAO = new GLuint();
	glGenVertexArrays(1, VAO);
	glBindVertexArray(*VAO);

	// buffer for vertex
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 3 * sizeof(GLfloat), vertices_plane, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// buffer for texture coordinate
	GLuint UBO;
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_ARRAY_BUFFER, UBO);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 2 * sizeof(GLfloat), tex_plane, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// buffer for normal
	GLuint NBO;
	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 3 * sizeof(GLfloat), normal_plane, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// buffer for index
	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberIndex * sizeof(GLushort), index_array_plane, GL_STATIC_DRAW);
	*numIndex = numberIndex;
	return VAO;
}
