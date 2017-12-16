#pragma once
#include "StaticMapObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;

class Triangle :
	public StaticMapObject
{
public:
	Triangle();
	~Triangle();
	void Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment);
	void Draw();
	void GenerateVertex();
private:
	float VertexX[3];
	float VertexY[3];
	float VertexZ[3];
	//GLuint Textures;
};

