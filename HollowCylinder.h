#include "StaticMapObject.h"
#pragma once
class HollowCylinder:
	public StaticMapObject
{
public:
	HollowCylinder();
	~HollowCylinder();
	void Draw();
	void GenerateVertex(){}
	void Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment);
private:
	void DrawCylinder(float RadiusX, float Angles, float c);
	//GLuint Textures[1];
};

