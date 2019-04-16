
/****************************************************************************
// CastleCrasher-Project.cpp by Beomjin Kim and Heaseo Chung (C) 2019 All Rights Reserved.
//
// Final project submission.
//
// Description:
// Additional include and lib directories are relative path.
// Click run.
// WASD to move the camera.
// Mouse to rotate the camera.
// IJKL to move the first light up down left right
// UO to move the first light back and forward.
// The second light position is fixed.
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
DrawableObject* lightObj2;
DrawableObject** objects;
int numObj;

GLuint* textures;
unsigned char** images;
const char* paths[4];
const char* path1 = "brick_2.jpg";
const char* path2 = "roof.jpg";
const char* path3 = "door.jpg";
const char* path4 = "etc.jpg";

/*/quaternion
float transformInfo[] =
{
	-0.53001, -4.8, -8.6597, -0.6532817, -0.2705976, 0.2705975, 0.6532817, 3.914451, 0.6985559, 3.914451, -0.53, 0.7358999, -8.52, -0.6532817, -0.2705976, 0.2705975, 0.6532817, 3.914451, 0.6985559, 3.914451, -0.53, 3.4959, -8.52, -0.7071068, 0, 0, 0.7071068, 2.794224, 0.6985559, 2.794224, 9.14, 10.121, -8.86, 0, 0, 0, 1, 1.17, 2.89575, 1.17, -5.539, 10.121, 8.86, 0, 0, 0, 1, 1.17, 2.89575, 1.17, -9.579, 10.1227, -8.859999, 0, 0, 0, 1, 1.17, 2.89575, 1.17, -9.579, 10.1227, 8.860001, 0, 0, 0, 1, 1.17, 2.89575, 1.17, 5.100001, 10.1227, 8.860001, 0, 0, 0, 1, 1.17, 2.89575, 1.17, 5.100001, 10.1227, -8.859999, 0, 0, 0, 1, 1.17, 2.89575, 1.17, -5.539, 10.121, -8.86, 0, 0, 0, 1, 1.17, 2.89575, 1.17, 9.14, 10.121, 8.86, 0, 0, 0, 1, 1.17, 2.89575, 1.17, 10.98, 31.78, 0, 0, 0, 0, 1, 3.0697, 14.38922, 3.0697, 10.98, 25.63, 0, 0, 0, 0, 1, 6.050072, 4.519829, 6.050072, 10.98, 41.52, 0, 0, 0, 0, 1, 0.1786573, 8.594935, 0.1786573, -4.41, 14.54, -0.28, 0.3265056, -0.6272114, 0.3265056, 0.6272114, 1, 1, 1, -4.41, 14.54, 5.06, 0.3265056, -0.6272114, 0.3265056, 0.6272114, 1, 1, 1, -4.41, 14.54, -5.37, 0.3265056, -0.6272114, 0.3265056, 0.6272114, 1, 1, 1, -1.74, 10.31, -9.5, -0.7071058, 0, 0, 0.7071078, 1.429193, 0.9110675, 1.429193, -6.96, 13.81, -5.35, 0, 0, 0, 1, 0.22611, 2.675648, 0.22611, -6.96, 13.81, 5.01, 0, 0, 0, 1, 0.22611, 2.675648, 0.22611, -6.96, 13.81, -0.24, 0, 0, 0, 1, 0.22611, 2.675648, 0.22611, 5.059299, 0.56, 8.92, 0, 0, 0, 1, 1, 16.24078, 1, -5.6289, 0.5600001, 8.919999, 0, 0, 0, 1, 1, 16.24078, 1, 9.0204, 0.5600001, 8.919999, 0, 0, 0, 1, 1, 16.24078, 1, 5.059299, 0.56, -8.83, 0, 0, 0, 1, 1, 16.24078, 1, -9.59, 0.56, -8.83, 0, 0, 0, 1, 1, 16.24078, 1, -5.6289, 0.5600001, -8.83, 0, 0, 0, 1, 1, 16.24078, 1, 9.0204, 0.5600001, -8.83, 0, 0, 0, 1, 1, 16.24078, 1, -9.59, 0.56, 8.919999, 0, 0, 0, 1, 1, 16.24078, 1, 10.98, 13.6, 0, 0, 0, 0, 1, 3.0697, 14.38922, 3.0697, 10.98, 19.87, 0, 0, 0, 0, 1, 1.848481, 8.664756, 1.848481, -1.69, 10.28, -8.76, 0.7071068, 0, 0, 0.7071068, 2.337756, 0.7013267, 2.337756, -5.21, 10.95, 4.97, 0.5000001, 0.5000001, -0.5, 0.5, 1.84752, 3.960634, 1.84752, -1.69, 10.28, 8.48, 0.7071068, 0, 0, 0.7071068, 2.337756, 0.7013267, 2.337756, -5.21, 10.95, -0.32, 0.5000001, 0.5000001, -0.5, 0.5, 1.84752, 3.960634, 1.84752, -5.21, 10.95, -5.38, 0.5000001, 0.5000001, -0.5, 0.5, 1.84752, 3.960634, 1.84752, -8.599999, 0.5600001, 8.910399, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, 12.35, 21.29, 2.41, -0.560986, -0.09229583, 0.4304586, 0.7010574, 1.321108, 0.5853169, 1.321108, 11.45, 0, 0, 0, 0.3826834, 0, 0.9238796, 9.237936, 14.9909, 9.237936, 0, 0, 0, 0, 0.3826834, 0, 0.9238796, 11.77842, 15.13939, 11.77842, 13.71, 21.29, -0.07, -0.2705992, 0.270597, 0.6532808, 0.6532822, 1.321108, 0.5853169, 1.321108, 8.03, 0.5600001, 8.910399, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, -8.599999, 0.5600001, -8.8396, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, 12.4, 21.29, -2.31, -0.7010574, -0.4304593, 0.09229597, 0.5609856, 1.321108, 0.5853169, 1.321108, 9.53, 21.29, 2.28, -0.7010574, -0.4304593, 0.09229597, 0.5609856, 1.321108, 0.5853169, 1.321108, 8.25, 21.29, -0.07, -0.2705992, 0.270597, 0.6532808, 0.6532822, 1.321108, 0.5853169, 1.321108, 6.0493, 0.5600001, -8.8396, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, -6.6193, 0.5600001, 8.910399, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, 6.0493, 0.5600001, 8.910399, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, 9.59, 21.29, -2.32, -0.560986, -0.09229583, 0.4304586, 0.7010574, 1.321108, 0.5853169, 1.321108, 8.03, 0.5600001, -8.8396, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, -6.6193, 0.5600001, -8.8396, 0, 0.3826834, 0, 0.9238796, 1.4006, 16.24078, 1.4006, -1.5678, 11.089, -0.19926, 0.7071068, 0, 0, 0.7071068, 7.806748, 17.05573, 7.038763, 6.824501, 9.7096, 8.86, 0.5000001, -0.5000001, 0.5, 0.5, 1.335555, 4.039973, 1.9305, -7.8545, 9.7096, -8.86, 0.5000001, -0.5000001, 0.5, 0.5, 1.335555, 4.039973, 1.9305, -7.8545, 9.7096, 8.86, 0.5000001, -0.5000001, 0.5, 0.5, 1.335555, 4.039973, 1.9305, 6.824501, 9.7096, -8.86, 0.5000001, -0.5000001, 0.5, 0.5, 1.335555, 4.039973, 1.9305, 3.27, 9.98, 0, 0.5, -0.5, 0.5, 0.5, 9.765539, 10.00353, 4.854319, 12.934, 9.8714, -0.12087, 0.5, -0.5, 0.5, 0.5, 7.403177, 10.09622, 4.751974
};
/*/ //euler
float transformInfo[] = 
{
-9.570581, 1.327792, 0.6883607, 314.9999, 180.0002, 90, 2.301542, 0.4107231, 2.301543, -17.55508, 12.69894, -1.592895, 55, 180.0002, 2.138652E-06, 0.58796, 0.58796, 0.5879602, -14.41538, 12.69894, -1.592904, 55, 180.0002, 2.138652E-06, 0.58796, 0.58796, 0.5879602, -14.57998, 28.5621, 7.455801, 0, 270.0002, 0, 0.1050434, 5.053478, 0.1050434, -11.43443, 12.26973, -3.092211, 0, 270.0002, 0, 0.1329436, 1.573174, 0.1329436, -14.4389, 12.26973, -3.092202, 0, 270.0002, 0, 0.1329436, 1.573174, 0.1329436, -19.5659, 10.19423, 0.006362438, 90, 270.0002, 0, 1.374507, 0.4123523, 1.374508, -17.50217, 10.58816, -2.063263, 90, 0.0001738682, 0, 1.086268, 2.328697, 1.086269, -14.39186, 10.58816, -2.063272, 90, 0.0001738682, 0, 1.086268, 2.328697, 1.086269, -11.41678, 10.58816, -2.063281, 90, 0.0001738682, 0, 1.086268, 2.328697, 1.086269, -14.53883, 16.66767, 5.85067, 315, 270, 89.99995, 0.7767593, 0.3441433, 0.7767593, -14.53882, 16.66767, 9.060932, 315, 270, 89.99995, 0.7767593, 0.3441433, 0.7767593, -15.92053, 16.66767, 6.603263, 315, 150.0002, 89.99999, 0.7767589, 0.3441431, 0.776759, -15.99696, 16.66767, 8.261311, 314.9999, 210.0001, 90, 0.7767588, 0.3441429, 0.7767589, -13.22179, 16.66767, 8.2907, 315, 150.0002, 89.99999, 0.7767589, 0.3441431, 0.776759, -14.57998, 15.83277, 7.455801, 0, 270.0002, 0, 1.086833, 5.09453, 1.086833, -14.57998, 19.21941, 7.455801, 0, 270.0002, 0, 3.5572, 2.657479, 3.5572, -14.57998, 4.15, 7.732142, 0, 315.0002, 0, 5.431538, 8.814049, 5.431538, -14.57999, 10.01784, 2.922629, 90, 180.0002, 0, 5.741751, 5.881674, 2.854146, -19.78931, 9.858856, 5.012549, 90, 180.0002, 0, 0.7852538, 2.375345, 1.135058, -19.78932, 10.10174, 3.998612, 0, 270.0002, 0, 0.6879132, 1.702585, 0.6879132, -19.78931, 10.10074, 6.373971, 0, 270.0002, 0, 0.6879132, 1.702585, 0.6879132, -19.78934, 9.858856, -3.618116, 90, 180.0002, 0, 0.7852538, 2.375345, 1.135058, -19.78934, 10.10174, -4.632053, 0, 270.0002, 0, 0.6879132, 1.702585, 0.6879132, -19.78934, 10.10074, -2.256695, 0, 270.0002, 0, 0.6879132, 1.702585, 0.6879132, -19.81895, 4.479258, 4.556762, 0, 315.0002, 0, 0.8234969, 9.548929, 0.8234969, -19.82459, 4.479258, 3.974681, 0, 270.0002, 0, 0.58796, 9.548929, 0.58796, -19.82459, 4.479258, 6.303649, 0, 270.0002, 0, 0.58796, 9.548929, 0.58796, -19.81894, 4.479258, 5.721334, 0, 315.0002, 0, 0.8234969, 9.548929, 0.8234969, -19.81897, 4.479258, -4.05644, 0, 315.0002, 0, 0.8234969, 9.548929, 0.8234969, -19.82462, 4.479258, -4.638521, 0, 270.0002, 0, 0.58796, 9.548929, 0.58796, -19.82461, 4.479258, -2.309553, 0, 270.0002, 0, 0.58796, 9.548929, 0.58796, -19.81897, 4.479258, -2.891868, 0, 315.0002, 0, 0.8234969, 9.548929, 0.8234969, -9.382658, 4.479258, 4.556731, 0, 315.0002, 0, 0.8234969, 9.548929, 0.8234969, -9.388305, 4.479258, 3.97465, 0, 270.0002, 0, 0.58796, 9.548929, 0.58796, -9.388298, 4.479258, 6.303619, 0, 270.0002, 0, 0.58796, 9.548929, 0.58796, -9.382655, 4.479258, 5.721303, 0, 315.0002, 0, 0.8234969, 9.548929, 0.8234969, -9.388323, 4.479258, -2.309584, 0, 270.0002, 0, 0.58796, 9.548929, 0.58796, -9.382681, 4.479258, -2.891899, 0, 315.0002, 0, 0.8234969, 9.548929, 0.8234969, -9.382684, 4.479258, -4.05647, 0, 315.0002, 0, 0.8234969, 9.548929, 0.8234969, -9.38833, 4.479258, -4.638552, 0, 270.0002, 0, 0.58796, 9.548929, 0.58796, -9.370663, 9.858856, 5.012518, 90, 180.0002, 0, 0.7852538, 2.375345, 1.135058, -9.370667, 10.10174, 3.998582, 0, 270.0002, 0, 0.6879132, 1.702585, 0.6879132, -9.370659, 10.10074, 6.37394, 0, 270.0002, 0, 0.6879132, 1.702585, 0.6879132, -9.370684, 10.10074, -2.256726, 0, 270.0002, 0, 0.6879132, 1.702585, 0.6879132, -9.370687, 9.858856, -3.618147, 90, 180.0002, 0, 0.7852538, 2.375345, 1.135058, -9.370691, 10.10174, -4.632084, 0, 270.0002, 0, 0.6879132, 1.702585, 0.6879132, -14.50891, 9.953989, 8.604674, 90, 180.0002, 0, 4.352775, 5.936173, 2.793971, -14.57998, 12.14626, 7.455801, 0, 270.0002, 0, 1.804861, 8.460285, 1.804861, -14.57998, 22.83537, 7.455801, 0, 270.0002, 0, 1.804861, 8.460285, 1.804861, -13.21592, 16.66767, 6.638533, 314.9999, 210.0001, 90, 0.7767588, 0.3441429, 0.7767589, -9.429473, 10.19423, 0.006332397, 90, 270.0002, 0, 1.374507, 0.4123523, 1.374508, -17.52569, 12.26973, -3.092193, 0, 270.0002, 0, 0.1329436, 1.573174, 0.1329436, -11.42266, 12.69894, -1.592913, 55, 180.0002, 2.138652E-06, 0.58796, 0.58796, 0.5879602, -8.994383, 10.21187, -0.02306652, 270, 270.0002, 0, 0.8403081, 0.5356712, 0.8403081, -9.570581, 6.205449, 0.6883664, 270, 270.0002, 0, 1.642892, 0.4107232, 1.642893, -9.570581, 4.58268, 0.6883664, 314.9999, 180.0002, 90, 2.301542, 0.4107231, 2.301543, -14.58, 4.15, 1, 0, 315.0002, 0, 6.925241, 8.901354, 6.925241, -14.46285, 10.66989, 0.07819599, 90, 270.0002, 0, 4.590056, 10.02809, 4.138515, 0, 4.77, 10.25, 90, 0, 0, 0.7, 0.5, 0.7, -4.86, 5.44, 17.15, 0, 0, 0, 0.3, 1, 0.3, -4.96, 5.44, 19.25, 0, 0, 0, 0.3, 1, 0.3, 4.76, 3.18, 17.54, 90, 90, 0, 3, 2, 3, 4.64, 0.54, 12.51, 0, 45, 0, 2.5, 2, 2.5, -3.38, 5.44, 20.78, 0, 0, 0, 0.3, 1, 0.3, -0.05, 5.63, 12.57, 0, 45, 0, 4.5, 4, 4.5, 2.2, 3.75, 19.54, 90, 0, 0, 3, 2, 3, 4.26, 3.47, 12.32, 0, 45, 0, 3.5, 4, 3.5, -0.67, 5.44, 20.31, 0, 0, 0, 0.3, 1, 0.3, -2.66, 2.46, 18.26, 0, 0, 0, 3, 5, 3, -1.84, 5.44, 15.93, 0, 0, 0, 0.3, 1, 0.3, -4.48, 5.44, 20.25, 0, 0, 0, 0.3, 1, 0.3, 4.26, 2.45, 10.75, 90, 0, 0, 0.5, 1, 0.5, 0.847, 1.046, 9.51, 0, 0, 0, 0.1, 2.5, 0.1, 0, 1.64, 12.51, 0, 45, 0, 4, 4, 4, -0.06099999, 1.037, 10.388, 0, 45, 0, 1.2, 2.5, 1.2, 0, 0, 0.14, 0.09299753, 21.99999, 359.229, 10, 0.1, 10, -0.981, 1.046, 9.51, 0, 0, 0, 0.1, 2.5, 0.1, -0.67, 5.44, 16.28, 0, 0, 0, 0.3, 1, 0.3, 2.15, 5.54, 17.46, 0, 45, 0, 6, 5, 6, -2.41, 4.77, 12.75, 90, 270, 0, 0.7, 0.5, 0.7, 3.519, 3.32, 14.696, 0, 45, 0, 1, 9, 1, -2.04, 5.44, 20.78, 0, 0, 0, 0.3, 1, 0.3, 5.84, 2.45, 12.34, 90, 90, 0, 0.5, 1, 0.5, -4.21, 5.44, 16.27, 0, 0, 0, 0.3, 1, 0.3, -0.06, 2.31, 9.51, 0, 0, 90, 0.1, 2, 0.1, 3.519, 9.8, 14.696, 0, 45, 0, 1, 4, 1, 2.16, 1.64, 17.6, 0, 45, 0, 5, 4, 5, -5.23, 5.44, 18.28, 0, 0, 0, 0.3, 1, 0.3, -2.93, 5.42, 15.78, 0, 0, 0, 0.3, 1, 0.3
};
//*/

int objectInfo[] =
{
	4, 0, 2, 5, 1, 3, 5, 1, 3, 6, 1, 1, 3, 1, 3, 3, 1, 3, 5, 0, 3, 5, 0, 3, 5, 0, 3, 5, 0, 3, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 6, 0, 0, 6, 1, 1, 4, 0, 0, 3, 0, 1, 3, 0, 1, 8, 1, 1, 8, 1, 1, 3, 0, 1, 8, 1, 1, 8, 1, 1, 4, 0, 0, 8, 0, 0, 8, 0, 0, 4, 0, 0, 4, 0, 0, 8, 0, 0, 8, 0, 0, 4, 0, 0, 4, 0, 0, 8, 0, 0, 8, 0, 0, 4, 0, 0, 8, 0, 0, 4, 0, 0, 4, 0, 0, 8, 0, 0, 3, 0, 1, 8, 1, 1, 8, 1, 1, 8, 1, 1, 3, 0, 1, 8, 1, 1, 3, 0, 1, 6, 0, 0, 6, 1, 1, 4, 0, 0, 5, 0, 3, 3, 1, 3, 5, 1, 3, 4, 1, 3, 8, 0, 2, 4, 0, 2, 4, 0, 0, 3, 0, 1, 8, 0, 3, 4, 0, 0, 4, 0, 0, 3, 0, 1, 4, 0, 0, 4, 0, 0, 4, 1, 1, 3, 0, 1, 4, 1, 1, 4, 0, 0, 8, 0, 0, 4, 0, 0, 4, 0, 0, 3, 0, 1, 8, 0, 0, 4, 0, 0, 4, 0, 2, 8, 0, 3, 8, 0, 0, 4, 0, 0, 4, 1, 1, 8, 0, 3, 8, 0, 0, 4, 0, 0, 3, 0, 1, 4, 0, 0, 8, 0, 0, 8, 1, 1, 4, 0, 0, 4, 0, 0, 4, 0, 0
};

GLuint MatrixID;
GLuint ModelMatrixID;
GLuint ViewMatrixID;
GLuint LightPosID;
GLuint LightPosID2;
glm::mat4 MVP;
glm::mat4 View;
glm::mat4 Projection;
glm::vec3 CamPos;
glm::vec3 lookDir;
glm::vec3 up;
glm::vec3 LightPos;
glm::vec3 LightPos2;
glm::vec2 mousePos;
float mouseSensitivity;

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

	LightPos = glm::vec3(0, 10, 0);
	LightPos2 = glm::vec3(50, 50, 50.f);
	CamPos = glm::vec3(15, 10, 15.f);
	lookDir = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
	mousePos = glm::vec2(1280/2, 720/2);
	mouseSensitivity = 1.f;
	MatrixID = glGetUniformLocation(program, "MVP");
	ModelMatrixID = glGetUniformLocation(program, "M");
	ViewMatrixID = glGetUniformLocation(program, "V");
	LightPosID = glGetUniformLocation(program, "lightPosition[0]");
	LightPosID2 = glGetUniformLocation(program, "lightPosition[1]");
	glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
	glUniform3fv(LightPosID2, 1, glm::value_ptr(LightPos2));
	Projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 2000.0f);
	View = glm::lookAt(
		CamPos,
		CamPos+lookDir,
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
		float ang = transformInfo[(i * 10) + 6]+1;
		glm::vec3 scl = glm::vec3(transformInfo[(i * 10) + 7], transformInfo[(i * 10) + 8], transformInfo[(i * 10) + 9]);
		/*/
		glm::vec3 pos = glm::vec3(transformInfo[i * 9], transformInfo[(i * 9) + 1], (transformInfo[(i * 9) + 2]*-1));
		glm::vec3 rot = glm::vec3(transformInfo[(i * 9) + 3]*-1, transformInfo[(i * 9) + 4]*-1, transformInfo[(i * 9) + 5]);
		glm::vec3 scl = glm::vec3(transformInfo[(i * 9) + 6], transformInfo[(i * 9) + 7], transformInfo[(i * 9) + 8]);
		float ang = 0;
		//*/
		Transform temp = Transform(pos, rot, ang, scl);
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


	lightObj2 = new DrawableObject(4, Type::Column, TextureID::Brick);
	lightObj2->transform.scale = glm::vec3(0.2f);
	lightObj2->transform.position = LightPos2;
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
	Model = glm::rotate(Model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	Model = glm::rotate(Model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
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
		CamPos + lookDir,
		up
	);

#pragma region CameraObjects
	glBindVertexArray(*lightObj->getVAO());
	glBindTexture(GL_TEXTURE_2D, textures[lightObj->id]);
	transformObject(lightObj->transform);
	glDrawElements(GL_TRIANGLES, *lightObj->num_index, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(*lightObj2->getVAO());
	glBindTexture(GL_TEXTURE_2D, textures[lightObj2->id]);
	transformObject(lightObj2->transform);
	glDrawElements(GL_TRIANGLES, *lightObj2->num_index, GL_UNSIGNED_SHORT, 0);
#pragma endregion

#pragma region DrawableObjects
	for (int i = 0; i < numObj; i++)
	{
		glBindVertexArray(*objects[i]->getVAO());
		glBindTexture(GL_TEXTURE_2D, textures[objects[i]->id]);
		/*/
		transformObject(objects[i]->transform);
		/*/
		customTransformObject(objects[i]->transform);
		//*/
		glDrawElements(GL_TRIANGLES, *objects[i]->num_index, GL_UNSIGNED_SHORT, 0);
	}
#pragma endregion


	prevTime = curTime;
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void Timer(int id)
{
	glutPostRedisplay();
	glutTimerFunc(15, Timer, 0);
}
void KeyDown(unsigned char key, int x, int y)
{
	glm::vec3 z_movement;
	switch (key)
	{
	case 'w':
		z_movement = glm::vec3((deltaTime / 1000.0f) * 25.f);
		z_movement *= lookDir;
		CamPos += z_movement;
		//printf("In\n");
		break;
	case 's':
		z_movement = glm::vec3((deltaTime / 1000.0f) * -25.f);
		z_movement *= lookDir;
		CamPos += z_movement;
		//printf("Out\n");
		break;
	case 'a':
		z_movement = glm::cross(up, lookDir)*(deltaTime / 1000.0f) * 25.f;
		CamPos += z_movement;
		break;
	case 'd':
		z_movement = glm::cross(lookDir, up)*(deltaTime / 1000.0f) * 25.f;
		CamPos += z_movement;
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
		LightPos.y += (deltaTime / 1000.0f) * 25.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("In\n");
		break;
	case 'j':
		LightPos.x -= (deltaTime / 1000.0f) * 25.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("Out\n");
		break;
	case 'k':
		LightPos.y -= (deltaTime / 1000.0f) * 25.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("Left\n");
		break;
	case 'l':
		LightPos.x += (deltaTime / 1000.0f) * 25.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("Right\n");
		break;
	case 'u':
		LightPos.z += (deltaTime / 1000.0f) * 25.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("Right\n");
		break;
	case 'o':
		LightPos.z -= (deltaTime / 1000.0f) * 25.f;
		glUniform3fv(LightPosID, 1, glm::value_ptr(LightPos));
		lightObj->transform.position = LightPos;
		//printf("Right\n");
		break;
	case 'q':
		mouseSensitivity += 0.5f;
		cout << "Mouse sensitivity up : " << mouseSensitivity << endl;
		break;
	case 'e':
		mouseSensitivity -= 0.5f;
		cout << "Mouse sensitivity down : " << mouseSensitivity << endl;
		break;
	default:
		break;
	}
}

void MouseMove(int _x, int _y)
{
	
	glm::vec2 mouseDelta = glm::vec2(_x, _y) - mousePos;
	// calculate look direction
	//rotate look dir on y axis with this angle
	float angle_hor = (deltaTime / 1000.f) * mouseDelta.x * mouseSensitivity;
	//rotate look dir on x axis with this angle
	float angle_ver = (deltaTime / 1000.f) * mouseDelta.y * mouseSensitivity;
	glm::mat4 rot_mat(1);
	rot_mat = glm::rotate(rot_mat, -angle_hor, glm::vec3(0, 1, 0));
	//rot_mat = glm::rotate(rot_mat, -angle_ver, glm::vec3(1, 0, 0));
	glm::vec3 dir(rot_mat * glm::vec4(lookDir, 1.0));
	dir.y += angle_ver* (deltaTime / 1000.f)*-10;
	glm::normalize(dir);
	lookDir = dir;


	//Calculate up vector
	glm::mat4 rot_y(1);
	glm::vec3 right = glm::cross(up, dir);
	glm::normalize(right);
	//up = glm::cross(dir, right);

	cout << "X : " << lookDir.x << ", Y : " << lookDir.y << ", Z : "<< lookDir.z<<endl;
	mousePos = glm::vec2(_x, _y);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("CastleCrasher Final Project");

	glewInit();	//Initializes the glew and prepares the drawing pipeline.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	init();
	glutDisplayFunc(display);

	glutKeyboardFunc(KeyDown);
	glutMotionFunc(MouseMove);

	glutTimerFunc(15, Timer, 0);
	//glutIdleFunc(idle);
	glutMainLoop();
}
