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

		normal_plane[index + 3] = 0.0f;
		normal_plane[index + 4] = 0.0f;
		normal_plane[index + 5] = -1.0f;

		normal_plane[index + 6] = 0.0f;
		normal_plane[index + 7] = 0.0f;
		normal_plane[index + 8] = -1.0f;
		index += 9;
	}

	//Vertex
	for (int i = (numCorner * 2) - 2; i >= 0; i -= 2)
	{
		int temp_i = i - 2 >= 0 ? i - 2 : (numCorner * 2) - 2;
		int temp_i2 = i - 1 >= 0 ? i - 1 : (numCorner * 2) - 1;

		vertices_plane[index] = tempPos[i];
		vertices_plane[index + 1] = -0.5f;
		vertices_plane[index + 2] = tempPos[i+1];

		vertices_plane[index + 3] = tempPos[temp_i];
		vertices_plane[index + 4] = -0.5f;
		vertices_plane[index + 5] = tempPos[temp_i2];

		vertices_plane[index + 6] = 0.0f;
		vertices_plane[index + 7] = 0.5f;
		vertices_plane[index + 8] = 0.0f;

		normal_plane[index] = 0.0f;
		normal_plane[index + 1] = 0.0f;
		normal_plane[index + 2] = -1.0f;

		normal_plane[index + 3] = 0.0f;
		normal_plane[index + 4] = 0.0f;
		normal_plane[index + 5] = -1.0f;

		normal_plane[index + 6] = 0.0f;
		normal_plane[index + 7] = 0.0f;
		normal_plane[index + 8] = -1.0f;

		index += 9;
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

	int numVertex = ((numCorner * 3) * 2) + (numCorner * 6);
	int numberIndex = numVertex;

	GLfloat* vert = new GLfloat[numVertex * 3];
	GLfloat* normal = new GLfloat[numVertex * 3];
	GLfloat* uv = new GLfloat[numVertex * 2];

	GLushort* index_array = new GLushort[numVertex];

	int index_vert = 0;
	int index_uv = 0;

	//* Bottom plane   3vertices per triangle, numCorner triangles on top plane
	for (int i = 0; i < numCorner*2; i+=2)
	{
////////Vertex
		vert[index_vert] = tempPos[i];
		vert[index_vert + 1] = -0.5f;
		vert[index_vert+2] = tempPos[(i + 1) % (numCorner*2)];

		vert[index_vert+3] = tempPos[(i + 2) % (numCorner * 2)];
		vert[index_vert + 4] = -0.5f;
		vert[index_vert+5] = tempPos[(i + 3) % (numCorner * 2)];
		
		// center
		vert[index_vert + 6] = 0.0f;
		vert[index_vert + 7] = -0.5f;
		vert[index_vert + 8] = 0.0f;

////////Normal
		normal[index_vert] = 0.0f;
		normal[index_vert+1] = -1.0f;
		normal[index_vert+2] = 0.0f;

		normal[index_vert+3] = 0.0f;
		normal[index_vert+4] = -1.0f;
		normal[index_vert+5] = 0.0f;

		normal[index_vert+6] = 0.0f;
		normal[index_vert+7] = -1.0f;
		normal[index_vert+8] = 0.0f;

////////UV
		uv[index_uv] = (tempPos[i]+1)/2.f;
		uv[index_uv + 1] = (tempPos[(i + 1) % (numCorner * 2)]+1)/2.f;

		uv[index_uv + 2] = (tempPos[(i + 2) % (numCorner * 2)]+1)/2.f;
		uv[index_uv + 3] = (tempPos[(i + 3) % (numCorner * 2)]+1)/2.f;

		uv[index_uv + 4] = 0.5f;
		uv[index_uv + 5] = 0.5f;

		index_vert += 9;
		index_uv += 6;
	}//*/

	//*Bottom plane
	for (int i = (numCorner * 2) - 2; i >= 0; i -= 2)
	{
		////////Vertex
		vert[index_vert] = tempPos[i];
		vert[index_vert+1] = 0.5f;
		vert[index_vert+2] = tempPos[i+1];

		int temp_i = i - 2 >= 0 ? i - 2 : (numCorner * 2) - 2;
		int temp_i2 = i - 1 >= 0 ? i - 1 : (numCorner * 2) - 1;
		vert[index_vert+3] = tempPos[temp_i];
		vert[index_vert+4] = 0.5f;
		vert[index_vert+5] = tempPos[temp_i2];

		vert[index_vert+6] = 0.0f;
		vert[index_vert+7] = 0.5f;
		vert[index_vert+8] = 0.0f;

////////Normal
		normal[index_vert] = 0.0f;
		normal[index_vert+1] = 1.0f;
		normal[index_vert+2] = 0.0f;

		normal[index_vert+3] = 0.0f;
		normal[index_vert+4] = 1.0f;
		normal[index_vert+5] = 0.0f;

		normal[index_vert+6] = 0.0f;
		normal[index_vert+7] = 1.0f;
		normal[index_vert+8] = 0.0f;

		//*UV
		uv[index_uv] = (tempPos[i] + 1) / 2.f;
		uv[index_uv+1] = (tempPos[(i + 1)] + 1) / 2.f;

		uv[index_uv + 2] = (tempPos[temp_i] + 1) / 2.f;
		uv[index_uv + 3] = (tempPos[temp_i2] + 1) / 2.f;

		uv[index_uv + 4] = 0.5f;
		uv[index_uv + 5] = 0.5f;
		//*/
		index_vert += 9;
		index_uv += 6;
	}//*/

	// Side plane
	for (int i = 0; i < numCorner * 2; i += 2)
	{

	}

	// Index
	for (int i = 0; i < numVertex; i++)
	{
		index_array[i] = i;
	}

	GLuint* VAO = new GLuint();
	glGenVertexArrays(1, VAO);
	glBindVertexArray(*VAO);

	// buffer for vertex
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 3 * sizeof(GLfloat), vert, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// buffer for texture coordinate
	GLuint UBO;
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_ARRAY_BUFFER, UBO);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 2 * sizeof(GLfloat), uv, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// buffer for normal
	GLuint NBO;
	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 3 * sizeof(GLfloat), normal, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// buffer for index
	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberIndex * sizeof(GLushort), index_array, GL_STATIC_DRAW);
	*numIndex = numberIndex;
	return VAO;
}
