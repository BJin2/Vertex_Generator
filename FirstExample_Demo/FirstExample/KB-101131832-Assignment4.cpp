
/****************************************************************************
// KB-101131832-Assignment4.cpp by Beomjin Kim (C) 2019 All Rights Reserved.
//
// Assignment 4 submission.
//
// Description:
// Additional include and lib directories are relative path.
// Click run.
// Enter number of planes.
// Enter texture id.
// See the result.
//
//*****************************************************************************/

using namespace std;

#include <iostream>
#include "stdlib.h"
#include "time.h"
#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SOIL.h"
#include "DrawableObject.hpp"


enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers = 2 };
enum Attrib_IDs { vPosition = 0 };
enum TextureIDs { DiagonalLines_Debug = 1, DiagonalLines, Cubes };

int curTime;
int prevTime;
int deltaTime;

DrawableObject* temp;
DrawableObject* corn;
GLuint* textures;

GLuint MatrixID;
GLuint ModelMatrixID;
GLuint ViewMatrixID;
GLuint LightPosID;
glm::mat4 MVP;
glm::mat4 View;
glm::mat4 Projection;
glm::vec3 CamPos;
glm::vec3 LightPos;

GLuint NumVerticesPlane = 7;
TextureIDs textureID = TextureIDs::Cubes;

void init(void)
{

	//Specifying the name of vertex and fragment shaders.
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	//Loading and compiling shaders
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);	//My Pipeline is set up

	LightPos = glm::vec3(0, 0, 1.f);
	CamPos = glm::vec3(0, 0, 3.f);
	MatrixID = glGetUniformLocation(program, "MVP");
	ModelMatrixID = glGetUniformLocation(program, "M");
	ViewMatrixID = glGetUniformLocation(program, "V");
	LightPosID = glGetUniformLocation(program, "lightPosition");
	glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
	Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	View = glm::lookAt(
		CamPos,
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
	curTime = glutGet(GLUT_ELAPSED_TIME);
	prevTime = curTime;
	deltaTime = 0;



#pragma region Texture
	int width, height;
	unsigned char* image;

	switch (textureID)
	{
	case TextureIDs::DiagonalLines:
		image = SOIL_load_image("background.png", &width, &height, 0, SOIL_LOAD_RGB);
		break;
	case TextureIDs::DiagonalLines_Debug:
		image = SOIL_load_image("background2.png", &width, &height, 0, SOIL_LOAD_RGB);
		break;
	case TextureIDs::Cubes:
		image = SOIL_load_image("bonusTexture.png", &width, &height, 0, SOIL_LOAD_RGB);
		break;
	default:
		image = SOIL_load_image("bonusTexture.png", &width, &height, 0, SOIL_LOAD_RGB);
		break;
	}


#pragma endregion


#pragma region Plane
	/*/
	int numVertex = (NumVerticesPlane + 1)*(NumVerticesPlane + 1);
	GLfloat* vertices_plane = new GLfloat[numVertex * 3];
	GLfloat* tex_plane = new GLfloat[numVertex * 2];
	GLfloat* normal_plane = new GLfloat[numVertex * 3];

	GLushort* index_array_plane = new GLushort[NumVerticesPlane*NumVerticesPlane * 6];

	int index = 0;
	int index_uv = 0;
	int index_indexArr = 0;
	float difference = 1.0f / (float)NumVerticesPlane;
	std::cout <<"Total number of vertices : "<< numVertex << endl;
	std::cout << "difference : " << difference << endl;

#pragma region EachVertex
	//Calculate vertex position, normal and UV coordinate
	for (int i = 0; i < NumVerticesPlane + 1; i++)
	{
		for (int j = 0; j < NumVerticesPlane + 1; j++)
		{
			vertices_plane[index] = -0.5f + (j*difference);
			vertices_plane[index+1] = -0.5f + (i*difference);
			vertices_plane[index+2] = 0.0f;

			normal_plane[index] = 0.0f;
			normal_plane[index+1] = 0.0f;
			normal_plane[index+2] = 1.0f;

			tex_plane[index_uv] = j * difference;
			tex_plane[index_uv + 1] = 1- i * difference;

			index += 3;
			index_uv += 2;
		}
	}

#pragma endregion

#pragma region Index_Array
	for (int i = 0; i < NumVerticesPlane; i++)
	{
		for (int j = 0; j < NumVerticesPlane; j++)
		{
			//triangle 1
			index_array_plane[index_indexArr] = (i * (NumVerticesPlane+1)) + j; // left bottom
			index_array_plane[index_indexArr + 1] = (i*(NumVerticesPlane + 1)) + (j + 1); // right bottom
			index_array_plane[index_indexArr + 2] = ((i + 1)*(NumVerticesPlane + 1)) + (j + 1);// right top

			//triangle 2
			index_array_plane[index_indexArr + 3] = ((i + 1)*(NumVerticesPlane + 1)) + (j + 1);// right top
			index_array_plane[index_indexArr + 4] = ((i + 1)*(NumVerticesPlane + 1)) + j;// left top
			index_array_plane[index_indexArr + 5] = (i * (NumVerticesPlane + 1)) + j;// left bottom

			index_indexArr += 6;
		}
	}
#pragma endregion

#pragma region Printing_UV_Vertex_Index
	if (textureID == TextureIDs::DiagonalLines_Debug)
	{
		std::cout << "----------------------" << endl;
		std::cout << "-----------UV---------" << endl;
		std::cout << "----------------------" << endl;
		for (int i = 0; i < numVertex * 2; i += 2)
		{
			std::cout << tex_plane[i] << ", " << tex_plane[i + 1] << endl;
		}

		std::cout << "----------------------" << endl;
		std::cout << "--------VERTEX--------" << endl;
		std::cout << "----------------------" << endl;
		for (int i = 0; i < numVertex * 3; i += 3)
		{
			std::cout << vertices_plane[i] << ", " << vertices_plane[i + 1] << ", " << vertices_plane[i + 2] << endl;
		}
		std::cout << "----------------------" << endl;
		std::cout << "---------INDEX--------" << endl;
		std::cout << "----------------------" << endl;
		for (int i = 0; i < NumVerticesPlane*NumVerticesPlane * 6; i += 6)
		{
			std::cout << index_array_plane[i] << ", " << index_array_plane[i + 1] << ", " << index_array_plane[i + 2] << endl;
			std::cout << index_array_plane[i + 3] << ", " << index_array_plane[i + 4] << ", " << index_array_plane[i + 5] << endl << endl;
		}
	}
#pragma endregion

	// Generate VAO
	glGenVertexArrays(1, &gVAO_Plane);
	glBindVertexArray(gVAO_Plane);

	// buffer for vertex
	GLuint posVBO_Plane;
	glGenBuffers(1, &posVBO_Plane);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO_Plane);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 3 * sizeof(GLfloat), vertices_plane, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// buffer for texture coordinate
	GLuint texVBO_Plane;
	glGenBuffers(1, &texVBO_Plane);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO_Plane);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 2 * sizeof(GLfloat), tex_plane, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// buffer for normal
	GLuint norVBO_Plane;
	glGenBuffers(1, &norVBO_Plane);
	glBindBuffer(GL_ARRAY_BUFFER, norVBO_Plane);
	glBufferData(GL_ARRAY_BUFFER, numVertex * 3 * sizeof(GLfloat), normal_plane, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	//texture
	glGenTextures(1, &texture_plane);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_plane);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);


	// buffer for index
	GLuint IBO_Plane;
	glGenBuffers(1, &IBO_Plane);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_Plane);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (NumVerticesPlane*NumVerticesPlane * 6) * sizeof(GLushort), index_array_plane, GL_STATIC_DRAW);
	//*/
#pragma endregion



#pragma region Plane
	//temp = new DrawableObject(NumVerticesPlane, Type::Column, TextureID::Brick);
	//
	//textures = new GLuint[10];
	////texture
	//glGenTextures(1, &textures[0]);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glUniform1i(glGetUniformLocation(program, "texture0"), 0);
#pragma endregion

#pragma region Corn
	corn = new DrawableObject(NumVerticesPlane, Type::Cone, TextureID::Brick);

	textures = new GLuint[10];
	//texture
	glGenTextures(1, &textures[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);
#pragma endregion


}

void transformObject(glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 translation)
{
	glm::mat4 Model;
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, glm::radians(rotationAngle), rotationAxis);
	Model = glm::scale(Model, scale);

	MVP = Projection * View * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, glm::value_ptr(Model));
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, glm::value_ptr(View));
}
void transformObject(Transform transform)
{
	transformObject(transform.scale, transform.rotationAxis, transform.rotationAngle, transform.position);
}
//---------------------------------------------------------------------
//
// display
//

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.4f, 0.75f, 1.0f);

	//Calculate deltaTime
	curTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = curTime - prevTime;

	//Update camera position
	View = glm::lookAt(
		CamPos,
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	// will be in loop
	glBindVertexArray(*corn->getVAO());
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	transformObject(corn->transform);
	glDrawElements(GL_TRIANGLES, *corn->num_index, GL_UNSIGNED_SHORT, 0);


	prevTime = curTime;
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

//---------------------------------------------------------------------
//
// main
//
void Timer(int id)
{
	glutPostRedisplay();
	glutTimerFunc(15, Timer, 0);
}
void KeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		CamPos.z -= (deltaTime / 1000.0f) * 5.f;
		//printf("In\n");
		break;
	case 's':
		CamPos.z += (deltaTime / 1000.0f) * 5.f;
		//printf("Out\n");
		break;
	case 'a':
		CamPos.x -= (deltaTime / 1000.0f) * 5.f;
		//printf("Left\n");
		break;
	case 'd':
		CamPos.x += (deltaTime / 1000.0f) * 5.f;
		//printf("Right\n");
		break;
	case 'r':
		CamPos.y += (deltaTime / 1000.0f) * 5.f;
		//printf("Up\n");
		break;
	case 'f':
		CamPos.y -= (deltaTime / 1000.0f) * 5.f;
		//printf("Down\n");
		break;
	case 'i':
		LightPos.y += (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		//printf("In\n");
		break;
	case 'j':
		LightPos.x -= (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		//printf("Out\n");
		break;
	case 'k':
		LightPos.y -= (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		//printf("Left\n");
		break;
	case 'l':
		LightPos.x += (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		//printf("Right\n");
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Kim Beomjin 101131832");

	glewInit();	//Initializes the glew and prepares the drawing pipeline.

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	//*/
	cout << "Enter number of plane(Smaller than 255) : ";
	cin >> NumVerticesPlane;

	cout << endl << endl << "---- Texture id list ----" << endl;
	cout << "1. Diagonal Lines(Debug)" << endl << "2. Diagonal Lines" << endl << "3. Cubes" << endl;
	cout << "Enter number of texture id you want to use : ";

	int temp = 0;
	cin >> temp;
	textureID = (TextureIDs)temp;
	//*/

	init();

	glutDisplayFunc(display);

	glutKeyboardFunc(KeyDown);

	glutTimerFunc(15, Timer, 0);
	//glutIdleFunc(idle);
	glutMainLoop();
}
