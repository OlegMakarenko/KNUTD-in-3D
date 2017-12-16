#pragma once
#include "StaticMapObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;

class Cone :
	public StaticMapObject
{
public:
	Cone();
	~Cone();
	void Draw();
	void Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment);
	void GenerateVertex();
private:
	void DrawCone(float Radius, float b, float Angles);
	//GLuint Textures;
};

