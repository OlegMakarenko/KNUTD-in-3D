#pragma once
#include "StaticMapObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;

class Circle :
	public StaticMapObject
{
public:
	Circle();
	~Circle();
	void Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment);
	void Draw();
	void GenerateVertex();
protected:	void DrawCircle(float RadiusX, float RadiusY, float PositionZ, GLuint Textures);
private:	//GLuint Textures;
};

