#pragma once
#include "Circle.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;

class Cylinder :
	public Circle
{
public:
	Cylinder();
	~Cylinder();
	void Draw();
	void Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment);
private:
	void DrawCylinder(float RadiusX, float Angles, float c);
	//GLuint Textures[3];
};

