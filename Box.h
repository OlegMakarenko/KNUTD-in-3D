#pragma once
#include "StaticMapObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
using namespace sf;
using namespace std;

class Box :
	public StaticMapObject
{
public:
	Box();
	~Box();
	void Initialize(float a, float b, float c, float _X, float _Y, float _Z, float _AngleX, float _AngleY, float _AngleZ, string _Name, string Comment);
	void GenerateVertex();
	void Draw();
private:
	float VertexX[8];
	float VertexY[8];
	float VertexZ[8];
	//GLuint Textures[6];
};

