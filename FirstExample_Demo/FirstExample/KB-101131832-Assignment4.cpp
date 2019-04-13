
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

int curTime;
int prevTime;
int deltaTime;

DrawableObject* lightObj;
DrawableObject** objects;
int numObj;

GLuint* textures;
unsigned char** images;
const char* paths[4];
const char* path1 = "bonusTexture.png";
const char* path2 = "background.png";
const char* path3 = "background2.png";
const char* path4 = "rubiksTexture.png";

/*/
float transformInfo[] = 
{
	-0.53001, -4.8, -8.6597, -0.6532817, -0.2705976, 0.2705975, 0.6532817, 3.914451, 0.6985559, 3.914451, -0.53, 0.7358999, -8.52, -0.6532817, -0.2705976, 0.2705975, 0.6532817, 3.914451, 0.6985559, 3.914451, -0.53, 3.4959, -8.52, -0.7071068, 0, 0, 0.7071068, 2.794224, 0.6985559, 2.794224, 9.14, 10.121, -8.86, 0, 0, 0, 1, 1.17, 2.89575, 1.17, -5.539, 10.121, 8.86, 0, 0, 0, 1, 1.17, 2.89575, 1.17, -9.579, 10.1227, -8.859999, 0, 0, 0, 1, 1.17, 2.89575, 1.17, -9.579, 10.1227, 8.860001, 0, 0, 0, 1, 1.17, 2.89575, 1.17, 5.100001, 10.1227, 8.860001, 0, 0, 0, 1, 1.17, 2.89575, 1.17, 5.100001, 10.1227, -8.859999, 0, 0, 0, 1, 1.17, 2.89575, 1.17, -5.539, 10.121, -8.86, 0, 0, 0, 1, 1.17, 2.89575, 1.17, 9.14, 10.121, 8.86, 0, 0, 0, 1, 1.17, 2.89575, 1.17, 10.98, 31.78, 0, 0, 0, 0, 1, 3.0697, 14.38922, 3.0697, 10.98, 25.63, 0, 0, 0, 0, 1, 6.050072, 4.519829, 6.050072, 10.98, 41.52, 0, 0, 0, 0, 1, 0.1786573, 8.594935, 0.1786573, -4.41, 14.54, -0.28, 0.3265056, -0.6272114, 0.3265056, 0.6272114, 1, 1, 1, -4.41, 14.54, 5.06, 0.3265056, -0.6272114, 0.3265056, 0.6272114, 1, 1, 1, -4.41, 14.54, -5.37, 0.3265056, -0.6272114, 0.3265056, 0.6272114, 1, 1, 1, -1.74, 10.31, -9.5, -0.7071058, 0, 0, 0.7071078, 1.429193, 0.9110675, 1.429193, -6.96, 13.81, -5.35, 0, 0, 0, 1, 0.22611, 2.675648, 0.22611, -6.96, 13.81, 5.01, 0, 0, 0, 1, 0.22611, 2.675648, 0.22611, -6.96, 13.81, -0.24, 0, 0, 0, 1, 0.22611, 2.675648, 0.22611, 5.059299, 0.56, 8.92, 0, 0, 0, 1, 1, 16.24078, 1, -5.6289, 0.5600001, 8.919999, 0, 0, 0, 1, 1, 16.24078, 1, 9.0204, 0.5600001, 8.919999, 0, 0, 0, 1, 1, 16.24078, 1, 5.059299, 0.56, -8.83, 0, 0, 0, 1, 1, 16.24078, 1, -9.59, 0.56, -8.83, 0, 0, 0, 1, 1, 16.24078, 1, -5.6289, 0.5600001, -8.83, 0, 0, 0, 1, 1, 16.24078, 1, 9.0204, 0.5600001, -8.83, 0, 0, 0, 1, 1, 16.24078, 1, -9.59, 0.56, 8.919999, 0, 0, 0, 1, 1, 16.24078, 1, 10.98, 13.6, 0, 0, 0, 0, 1, 3.0697, 14.38922, 3.0697, 10.98, 19.87, 0, 0, 0, 0, 1, 1.848481, 8.664756, 1.848481, -1.69, 10.28, -8.76, 0.7071068, 0, 0, 0.7071068, 2.337756, 0.7013267, 2.337756, -5.21, 10.95, 4.97, 0.5000001, 0.5000001, -0.5, 0.5, 1.84752, 3.960634, 1.84752, -1.69, 10.28, 8.48, 0.7071068, 0, 0, 0.7071068, 2.337756, 0.7013267, 2.337756, -5.21, 10.95, -0.32, 0.5000001, 0.5000001, -0.5, 0.5, 1.84752, 3.960634, 1.84752, -5.21, 10.95, -5.38, 0.5000001, 0.5000001, -0.5, 0.5, 1.84752, 3.960634, 1.84752, -8.599999, 0.5600001, 8.910399, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, 12.35, 21.29, 2.41, -0.560986, -0.09229583, 0.4304586, 0.7010574, 1.321108, 0.5853169, 1.321108, 11.45, 0, 0, 0, 0.3826834, 0, 0.9238796, 9.237936, 14.9909, 9.237936, 0, 0, 0, 0, 0.3826834, 0, 0.9238796, 11.77842, 15.13939, 11.77842, 13.71, 21.29, -0.07, -0.2705992, 0.270597, 0.6532808, 0.6532822, 1.321108, 0.5853169, 1.321108, 8.03, 0.5600001, 8.910399, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, -8.599999, 0.5600001, -8.8396, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, 12.4, 21.29, -2.31, -0.7010574, -0.4304593, 0.09229597, 0.5609856, 1.321108, 0.5853169, 1.321108, 9.53, 21.29, 2.28, -0.7010574, -0.4304593, 0.09229597, 0.5609856, 1.321108, 0.5853169, 1.321108, 8.25, 21.29, -0.07, -0.2705992, 0.270597, 0.6532808, 0.6532822, 1.321108, 0.5853169, 1.321108, 6.0493, 0.5600001, -8.8396, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, -6.6193, 0.5600001, 8.910399, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, 6.0493, 0.5600001, 8.910399, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, 9.59, 21.29, -2.32, -0.560986, -0.09229583, 0.4304586, 0.7010574, 1.321108, 0.5853169, 1.321108, 8.03, 0.5600001, -8.8396, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, -6.6193, 0.5600001, -8.8396, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, -1.5678, 11.089, -0.19926, 0.7071068, 0, 0, 0.7071068, 7.806748, 17.05573, 7.038763, 6.824501, 9.7096, 8.86, 0.5000001, -0.5000001, 0.5, 0.5, 1.335555, 4.039973, 1.9305, -7.8545, 9.7096, -8.86, 0.5000001, -0.5000001, 0.5, 0.5, 1.335555, 4.039973, 1.9305, -7.8545, 9.7096, 8.86, 0.5000001, -0.5000001, 0.5, 0.5, 1.335555, 4.039973, 1.9305, 6.824501, 9.7096, -8.86, 0.5000001, -0.5000001, 0.5, 0.5, 1.335555, 4.039973, 1.9305, 3.27, 9.98, 0, 0.5, -0.5, 0.5, 0.5, 9.765539, 10.00353, 4.854319, 12.934, 9.8714, -0.12087, 0.5, -0.5, 0.5, 0.5, 7.403177, 10.09622, 4.751974
};
/*/
float transformInfo[] = 
{
	-0.53001, -4.8, -8.6597, 314.9999, 270, 90, 3.914451, 0.6985559, 3.914451, -0.53, 0.7358999, -8.52, 314.9999, 270, 90, 3.914451, 0.6985559, 3.914451, -0.53, 3.4959, -8.52, 270, 0, 0, 2.794224, 0.6985559, 2.794224, 9.14, 10.121, -8.86, 0, 0, 0, 1.17, 2.89575, 1.17, -5.539, 10.121, 8.86, 0, 0, 0, 1.17, 2.89575, 1.17, -9.579, 10.1227, -8.859999, 0, 0, 0, 1.17, 2.89575, 1.17, -9.579, 10.1227, 8.860001, 0, 0, 0, 1.17, 2.89575, 1.17, 5.100001, 10.1227, 8.860001, 0, 0, 0, 1.17, 2.89575, 1.17, 5.100001, 10.1227, -8.859999, 0, 0, 0, 1.17, 2.89575, 1.17, -5.539, 10.121, -8.86, 0, 0, 0, 1.17, 2.89575, 1.17, 9.14, 10.121, 8.86, 0, 0, 0, 1.17, 2.89575, 1.17, 10.98, 31.78, 0, 0, 0, 0, 3.0697, 14.38922, 3.0697, 10.98, 25.63, 0, 0, 0, 0, 6.050072, 4.519829, 6.050072, 10.98, 41.52, 0, 0, 0, 0, 0.1786573, 8.594935, 0.1786573, -4.41, 14.54, -0.28, 55, 270, 0, 1, 1, 1, -4.41, 14.54, 5.06, 55, 270, 0, 1, 1, 1, -4.41, 14.54, -5.37, 55, 270, 0, 1, 1, 1, -1.74, 10.31, -9.5, 270, 0, 0, 1.429193, 0.9110675, 1.429193, -6.96, 13.81, -5.35, 0, 0, 0, 0.22611, 2.675648, 0.22611, -6.96, 13.81, 5.01, 0, 0, 0, 0.22611, 2.675648, 0.22611, -6.96, 13.81, -0.24, 0, 0, 0, 0.22611, 2.675648, 0.22611, 5.059299, 0.56, 8.92, 0, 0, 0, 1, 16.24078, 1, -5.6289, 0.5600001, 8.919999, 0, 0, 0, 1, 16.24078, 1, 9.0204, 0.5600001, 8.919999, 0, 0, 0, 1, 16.24078, 1, 5.059299, 0.56, -8.83, 0, 0, 0, 1, 16.24078, 1, -9.59, 0.56, -8.83, 0, 0, 0, 1, 16.24078, 1, -5.6289, 0.5600001, -8.83, 0, 0, 0, 1, 16.24078, 1, 9.0204, 0.5600001, -8.83, 0, 0, 0, 1, 16.24078, 1, -9.59, 0.56, 8.919999, 0, 0, 0, 1, 16.24078, 1, 10.98, 13.6, 0, 0, 0, 0, 3.0697, 14.38922, 3.0697, 10.98, 19.87, 0, 0, 0, 0, 1.848481, 8.664756, 1.848481, -1.69, 10.28, -8.76, 90, 0, 0, 2.337756, 0.7013267, 2.337756, -5.21, 10.95, 4.97, 90, 90.00001, 0, 1.84752, 3.960634, 1.84752, -1.69, 10.28, 8.48, 90, 0, 0, 2.337756, 0.7013267, 2.337756, -5.21, 10.95, -0.32, 90, 90.00001, 0, 1.84752, 3.960634, 1.84752, -5.21, 10.95, -5.38, 90, 90.00001, 0, 1.84752, 3.960634, 1.84752, -8.599999, 0.5600001, 8.910399, 0, 45, 0, 1.4006, 16.24078, 1.4006, 12.35, 21.29, 2.41, 314.9999, 299.9999, 90, 1.321108, 0.5853169, 1.321108, 11.45, 0, 0, 0, 45, 0, 9.237936, 14.9909, 9.237936, 0, 0, 0, 0, 45, 0, 11.77842, 15.13939, 11.77842, 13.71, 21.29, -0.07, 315, -0.0001738682, 89.99995, 1.321108, 0.5853169, 1.321108, 8.03, 0.5600001, 8.910399, 0, 45, 0, 1.4006, 16.24078, 1.4006, -8.599999, 0.5600001, -8.8396, 0, 45, 0, 1.4006, 16.24078, 1.4006, 12.4, 21.29, -2.31, 315, 240, 90, 1.321108, 0.5853169, 1.321108, 9.53, 21.29, 2.28, 315, 240, 90, 1.321108, 0.5853169, 1.321108, 8.25, 21.29, -0.07, 315, -0.0001738682, 89.99995, 1.321108, 0.5853169, 1.321108, 6.0493, 0.5600001, -8.8396, 0, 45, 0, 1.4006, 16.24078, 1.4006, -6.6193, 0.5600001, 8.910399, 0, 45, 0, 1.4006, 16.24078, 1.4006, 6.0493, 0.5600001, 8.910399, 0, 45, 0, 1.4006, 16.24078, 1.4006, 9.59, 21.29, -2.32, 314.9999, 299.9999, 90, 1.321108, 0.5853169, 1.321108, 8.03, 0.5600001, -8.8396, 0, 45, 0, 1.4006, 16.24078, 1.4006, -6.6193, 0.5600001, -8.8396, 0, 45, 0, 1.4006, 16.24078, 1.4006, -1.5678, 11.089, -0.19926, 90, 0, 0, 7.806748, 17.05573, 7.038763, 6.824501, 9.7096, 8.86, 90, 270, 0, 1.335555, 4.039973, 1.9305, -7.8545, 9.7096, -8.86, 90, 270, 0, 1.335555, 4.039973, 1.9305, -7.8545, 9.7096, 8.86, 90, 270, 0, 1.335555, 4.039973, 1.9305, 6.824501, 9.7096, -8.86, 90, 270, 0, 1.335555, 4.039973, 1.9305, 3.27, 9.98, 0, 90, 270, 0, 9.765539, 10.00353, 4.854319, 12.934, 9.8714, -0.12087, 90, 270, 0, 7.403177, 10.09622, 4.751974
};
//*/




int objectInfo[] = 
{
	4, 0, 2, 4, 0, 2, 8, 0, 2, 8, 1, 1, 8, 1, 1, 8, 1, 1, 8, 1, 1, 8, 1, 1, 8, 1, 1, 8, 1, 1, 8, 1, 1, 6, 1, 1, 6, 1, 1, 6, 1, 1, 5, 1, 3, 5, 1, 3, 5, 1, 3, 4, 1, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 8, 0, 0, 8, 0, 0, 8, 0, 0, 8, 0, 0, 8, 0, 0, 8, 0, 0, 8, 0, 0, 8, 0, 0, 6, 0, 0, 6, 0, 0, 5, 0, 3, 5, 0, 3, 5, 0, 3, 5, 0, 3, 5, 0, 3, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 3, 0, 1, 3, 0, 1, 3, 0, 1, 3, 0, 1, 3, 0, 1, 3, 0, 1, 3, 0, 1
};

GLuint MatrixID;
GLuint ModelMatrixID;
GLuint ViewMatrixID;
GLuint LightPosID;
glm::mat4 MVP;
glm::mat4 View;
glm::mat4 Projection;
glm::vec3 CamPos;
glm::vec3 LightPos;

void init(void)
{
	paths[0] = path1;
	paths[1] = path2;
	paths[2] = path3;
	paths[3] = path4;


	numObj = (sizeof(objectInfo) / sizeof(int))/3;
	std::cout << numObj << std::endl;
	objects = new DrawableObject*[numObj];

	//Specifying the name of vertex and fragment shaders.
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	//Loading and compiling shaders
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);	//My Pipeline is set up

	LightPos = glm::vec3(0, 0, 3.f);
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

	for (int i = 0; i < numObj; i++)
	{
		/*/
		glm::vec3 pos = glm::vec3(transformInfo[i * 10], transformInfo[(i * 10) + 1], (transformInfo[(i * 10) + 2]*-1));
		glm::vec3 rot = glm::vec3(transformInfo[(i * 10) + 3], transformInfo[(i * 10) + 4], transformInfo[(i * 10) + 5]);
		float ang = transformInfo[(i * 10) + 6];
		glm::vec3 scl = glm::vec3(transformInfo[(i * 10) + 7], transformInfo[(i * 10) + 8], transformInfo[(i * 10) + 9]);
		/*/
		glm::vec3 pos = glm::vec3(transformInfo[i * 9], transformInfo[(i * 9) + 1], (transformInfo[(i * 9) + 2]*-1));
		glm::vec3 rot = glm::vec3(transformInfo[(i * 9) + 3], transformInfo[(i * 9) + 4], transformInfo[(i * 9) + 5]);
		glm::vec3 scl = glm::vec3(transformInfo[(i * 9) + 6], transformInfo[(i * 9) + 7], transformInfo[(i * 9) + 8]);
		//*/
		Transform temp = Transform(pos, rot, 0, scl);
		int numC = objectInfo[i * 3];
		Type t = (Type)objectInfo[(i * 3) + 1];
		TextureID id = (TextureID)objectInfo[(i * 3) + 2];

		objects[i] = new DrawableObject(numC, t, id);
		objects[i]->transform = temp;
	}

#pragma region Texture
	int* width;
	int* height;
	
	images = new unsigned char*[TextureID::Count];
	textures = new GLuint[TextureID::Count];
	width = new int[TextureID::Count];
	height = new int[TextureID::Count];

	for (int i = 0; i < TextureID::Count; i++)
	{
		images[i] = SOIL_load_image(paths[i], &width[i], &height[i], 0, SOIL_LOAD_RGB);

		glGenTextures(1, &textures[i]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[i], height[i], 0, GL_RGB, GL_UNSIGNED_BYTE, images[i]);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glUniform1i(glGetUniformLocation(program, "texture0"), 0);
	}
#pragma endregion

	lightObj = new DrawableObject(4, Type::Column, TextureID::Brick);
	lightObj->transform.scale = glm::vec3(0.2f);
	lightObj->transform.position = LightPos;

}

void transformObject(glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 translation)
{
	glm::mat4 Model;
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, rotationAngle, rotationAxis);
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
void customTransformObject(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation)
{
	glm::mat4 Model;
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	Model = glm::rotate(Model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	Model = glm::rotate(Model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	Model = glm::scale(Model, scale);

	MVP = Projection * View * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, glm::value_ptr(Model));
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, glm::value_ptr(View));
}
void customTransformObject(Transform transform)
{
	customTransformObject(transform.scale, transform.rotationAxis, transform.position);
}



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
	for (int i = 0; i < numObj; i++)
	{
		glBindVertexArray(*objects[i]->getVAO());
		glBindTexture(GL_TEXTURE_2D, textures[objects[i]->id]);
		customTransformObject(objects[i]->transform);
		glDrawElements(GL_TRIANGLES, *objects[i]->num_index, GL_UNSIGNED_SHORT, 0);
	}

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
		CamPos.z -= (deltaTime / 1000.0f) * 25.f;
		//printf("In\n");
		break;
	case 's':
		CamPos.z += (deltaTime / 1000.0f) * 25.f;
		//printf("Out\n");
		break;
	case 'a':
		CamPos.x -= (deltaTime / 1000.0f) * 25.f;
		//printf("Left\n");
		break;
	case 'd':
		CamPos.x += (deltaTime / 1000.0f) * 25.f;
		//printf("Right\n");
		break;
	case 'r':
		CamPos.y += (deltaTime / 1000.0f) * 25.f;
		//printf("Up\n");
		break;
	case 'f':
		CamPos.y -= (deltaTime / 1000.0f) * 25.f;
		//printf("Down\n");
		break;
	case 'i':
		LightPos.y += (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("In\n");
		break;
	case 'j':
		LightPos.x -= (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("Out\n");
		break;
	case 'k':
		LightPos.y -= (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("Left\n");
		break;
	case 'l':
		LightPos.x += (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("Right\n");
		break;
	case 'u':
		LightPos.z += (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("Right\n");
		break;
	case 'o':
		LightPos.z -= (deltaTime / 1000.0f) * 5.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	init();

	glutDisplayFunc(display);

	glutKeyboardFunc(KeyDown);

	glutTimerFunc(15, Timer, 0);
	//glutIdleFunc(idle);
	glutMainLoop();
}
