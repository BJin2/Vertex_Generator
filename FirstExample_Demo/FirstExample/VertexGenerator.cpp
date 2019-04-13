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

		if (curAngle == 180 || curAngle == -180)
			tempPos[i] = 0.0f;
		else
			tempPos[i] = glm::sin(curRad);

		if (curAngle == 90 || curAngle == 270 || curAngle == -90 || curAngle == -270)
			tempPos[i + 1] = 0.0f;
		else
			tempPos[i + 1] = glm::cos(curRad);
	}

	return tempPos;
}

GLuint * VertexGenerator::CreateCone(int numCorner, int * numIndex)
{
	GLfloat* tempPos = VertexGenerator::CreateShape(numCorner);

	int numVertex = ((numCorner * 3) * 2) + (numCorner * 6);

	GLfloat* vert = new GLfloat[numVertex * 3];
	GLfloat* normal = new GLfloat[numVertex * 3];
	GLfloat* uv = new GLfloat[numVertex * 2];

	GLushort* index_array = new GLushort[numVertex];

	int index_vert = 0;
	int index_uv = 0;

	//Bottom
	for (int i = 0; i < numCorner * 2; i += 2)
	{
		vert[index_vert] = tempPos[i];
		vert[index_vert + 1] = -0.5f;
		vert[index_vert + 2] = tempPos[(i + 1) % (numCorner * 2)];

		vert[index_vert + 3] = tempPos[(i + 2) % (numCorner * 2)];
		vert[index_vert + 4] = -0.5f;
		vert[index_vert + 5] = tempPos[(i + 3) % (numCorner * 2)];

		vert[index_vert + 6] = 0.0f;
		vert[index_vert + 7] = -0.5f;
		vert[index_vert + 8] = 0.0f;

		normal[index_vert] = 0.0f;
		normal[index_vert + 1] = -1.0f;
		normal[index_vert + 2] = 0.0f;

		normal[index_vert + 3] = 0.0f;
		normal[index_vert + 4] = -1.0f;
		normal[index_vert + 5] = 0.0f;

		normal[index_vert + 6] = 0.0f;
		normal[index_vert + 7] = -1.0f;
		normal[index_vert + 8] = 0.0f;

		uv[index_uv] = (tempPos[i] + 1) / 2.f;
		uv[index_uv + 1] = (tempPos[(i + 1) % (numCorner * 2)] + 1) / 2.f;

		uv[index_uv + 2] = (tempPos[(i + 2) % (numCorner * 2)] + 1) / 2.f;
		uv[index_uv + 3] = (tempPos[(i + 3) % (numCorner * 2)] + 1) / 2.f;

		uv[index_uv + 4] = 0.5f;
		uv[index_uv + 5] = 0.5f;

		index_vert += 9;
		index_uv += 6;
	}
		//Top
	for (int i = (numCorner * 2) - 2; i >= 0; i -= 2)
	{
		int temp_i = i - 2 >= 0 ? i - 2 : (numCorner * 2) - 2;
		int temp_i2 = i - 1 >= 0 ? i - 1 : (numCorner * 2) - 1;

		vert[index_vert] = tempPos[i];
		vert[index_vert + 1] = -0.5f;
		vert[index_vert + 2] = tempPos[i+1];
		glm::vec3 a = glm::vec3(vert[index_vert], vert[index_vert + 1], vert[index_vert + 2]);

		vert[index_vert + 3] = tempPos[temp_i];
		vert[index_vert + 4] = -0.5f;
		vert[index_vert + 5] = tempPos[temp_i2];
		glm::vec3 b = glm::vec3(vert[index_vert + 3], vert[index_vert + 4], vert[index_vert + 5]);

		vert[index_vert + 6] = 0.0f;
		vert[index_vert + 7] = 0.5f;
		vert[index_vert + 8] = 0.0f;
		glm::vec3 c = glm::vec3(vert[index_vert + 6], vert[index_vert + 7], vert[index_vert + 8]);

		glm::vec3 normalPerVertex = glm::cross((a - c), (b - c));
		glm::normalize(normalPerVertex);

		normal[index_vert] = normalPerVertex.x;
		normal[index_vert + 1] = normalPerVertex.y;
		normal[index_vert + 2] = normalPerVertex.z;

		normal[index_vert + 3] = normalPerVertex.x;
		normal[index_vert + 4] = normalPerVertex.y;
		normal[index_vert + 5] = normalPerVertex.z;

		normal[index_vert + 6] = normalPerVertex.x;
		normal[index_vert + 7] = normalPerVertex.y;
		normal[index_vert + 8] = normalPerVertex.z;

		uv[index_uv] = (tempPos[i] + 1) / 2.f;
		uv[index_uv + 1] = (tempPos[(i + 1) % (numCorner * 2)] + 1) / 2.f;

		uv[index_uv + 2] = (tempPos[(i + 2) % (numCorner * 2)] + 1) / 2.f;
		uv[index_uv + 3] = (tempPos[(i + 3) % (numCorner * 2)] + 1) / 2.f;

		uv[index_uv + 4] = 0.5f;
		uv[index_uv + 5] = 0.5f;

		index_vert += 9;
		index_uv += 6;
	}

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numVertex * sizeof(GLushort), index_array, GL_STATIC_DRAW);
	*numIndex = numVertex;

	return VAO;
	
}

GLuint * VertexGenerator::CreateColumn(int numCorner, int * numIndex)
{
	
	GLfloat* tempPos = VertexGenerator::CreateShape(numCorner);

	int numVertex = ((numCorner * 3) * 2) + (numCorner * 6);

	GLfloat* vert = new GLfloat[numVertex * 3];
	GLfloat* normal = new GLfloat[numVertex * 3];
	GLfloat* uv = new GLfloat[numVertex * 2];

	GLushort* index_array = new GLushort[numVertex];

	int index_vert = 0;
	int index_uv = 0;



#pragma region Bottom
	for (int i = 0; i < numCorner*2; i+=2)
	{
#pragma region Vertex
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
#pragma endregion

#pragma region Normal
		normal[index_vert] = 0.0f;
		normal[index_vert+1] = -1.0f;
		normal[index_vert+2] = 0.0f;

		normal[index_vert+3] = 0.0f;
		normal[index_vert+4] = -1.0f;
		normal[index_vert+5] = 0.0f;

		normal[index_vert+6] = 0.0f;
		normal[index_vert+7] = -1.0f;
		normal[index_vert+8] = 0.0f;
#pragma endregion

#pragma region UV
		uv[index_uv] = (tempPos[i]+1)/2.f;
		uv[index_uv + 1] = (tempPos[(i + 1) % (numCorner * 2)]+1)/2.f;

		uv[index_uv + 2] = (tempPos[(i + 2) % (numCorner * 2)]+1)/2.f;
		uv[index_uv + 3] = (tempPos[(i + 3) % (numCorner * 2)]+1)/2.f;

		uv[index_uv + 4] = 0.5f;
		uv[index_uv + 5] = 0.5f;
#pragma endregion

#pragma region IndexIncrement
		index_vert += 9;
		index_uv += 6;
#pragma endregion
	}
#pragma endregion

#pragma region Top
	for (int i = (numCorner * 2) - 2; i >= 0; i -= 2)
	{
#pragma region Vertex
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
#pragma endregion

#pragma region Normal
		normal[index_vert] = 0.0f;
		normal[index_vert+1] = 1.0f;
		normal[index_vert+2] = 0.0f;

		normal[index_vert+3] = 0.0f;
		normal[index_vert+4] = 1.0f;
		normal[index_vert+5] = 0.0f;

		normal[index_vert+6] = 0.0f;
		normal[index_vert+7] = 1.0f;
		normal[index_vert+8] = 0.0f;
#pragma endregion

#pragma region UV
		uv[index_uv] = (tempPos[i] + 1) / 2.f;
		uv[index_uv+1] = (tempPos[(i + 1)] + 1) / 2.f;

		uv[index_uv + 2] = (tempPos[temp_i] + 1) / 2.f;
		uv[index_uv + 3] = (tempPos[temp_i2] + 1) / 2.f;

		uv[index_uv + 4] = 0.5f;
		uv[index_uv + 5] = 0.5f;
#pragma endregion

#pragma region IndexIncrement
		index_vert += 9;
		index_uv += 6;
#pragma endregion
	}
#pragma endregion
	
#pragma region Side

	for (int i = (numCorner * 2) - 2; i >= 0; i -= 2)
	{
#pragma region Vertex

		int temp_i = i - 2 >= 0 ? i - 2 : (numCorner * 2) - 2;
		int temp_i2 = i - 1 >= 0 ? i - 1 : (numCorner * 2) - 1;

		//First triangle
		//Left bottom
		vert[index_vert] = tempPos[i];
		vert[index_vert + 1] = -0.5f;
		vert[index_vert + 2] = tempPos[i + 1];
		glm::vec3 a = glm::vec3(vert[index_vert], vert[index_vert + 1], vert[index_vert + 2]);

		//right bottom
		vert[index_vert + 3] = tempPos[temp_i];
		vert[index_vert + 4] = -0.5f;
		vert[index_vert + 5] = tempPos[temp_i2];
		glm::vec3 b = glm::vec3(vert[index_vert+3], vert[index_vert + 4], vert[index_vert + 5]);

		//right top
		vert[index_vert + 6] = tempPos[temp_i];
		vert[index_vert + 7] = 0.5f;
		vert[index_vert + 8] = tempPos[temp_i2];
		glm::vec3 c = glm::vec3(vert[index_vert+6], vert[index_vert + 7], vert[index_vert + 8]);

		
		//Second triangle
		//right top
		vert[index_vert + 9] = tempPos[temp_i];
		vert[index_vert + 10] = 0.5f;
		vert[index_vert + 11] = tempPos[temp_i2];

		//left top
		vert[index_vert + 12] = tempPos[i];
		vert[index_vert + 13] = 0.5f;
		vert[index_vert + 14] = tempPos[i + 1];

		//left bottom
		vert[index_vert + 15] = tempPos[i];
		vert[index_vert + 16] = -0.5f;
		vert[index_vert + 17] = tempPos[i + 1];

#pragma endregion

#pragma region Normal
		glm::vec3 normalPerVertex = glm::cross((c - b), (a - b));
		glm::normalize(normalPerVertex);
		for (int j = 0; j < 18; j += 3)
		{
			normal[index_vert+j] = normalPerVertex.x;
			normal[index_vert + j+1] = normalPerVertex.y;
			normal[index_vert + j+2] = normalPerVertex.z;
		}
#pragma endregion
		index_vert += 18;
	}

#pragma region UV
	float increment = 1.f / (float)numCorner;
	for (int i = 0; i < numCorner; i++)
	{
		uv[index_uv] = i * increment;
		uv[index_uv + 1] = 1;

		uv[index_uv + 2] = (i + 1) * increment;
		uv[index_uv + 3] = 1;

		uv[index_uv + 4] = (i + 1) * increment;
		uv[index_uv + 5] = 0;

		uv[index_uv + 6] = (i + 1) * increment;
		uv[index_uv + 7] = 0;

		uv[index_uv + 8] = i * increment;
		uv[index_uv + 9] = 0;

		uv[index_uv + 10] = i * increment;
		uv[index_uv + 11] = 1;
		index_uv += 12;
	}
#pragma endregion
#pragma endregion


#pragma region Index
	for (int i = 0; i < numVertex; i++)
	{
		index_array[i] = i;
	}
#pragma endregion

	

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numVertex * sizeof(GLushort), index_array, GL_STATIC_DRAW);
	*numIndex = numVertex;
	return VAO;
}
