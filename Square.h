#pragma once
#include "StaticMapObject.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
using namespace sf;
using namespace std;
class Square :
	public StaticMapObject
{
public:
	Square();
	~Square();
	void Initialize(float a, float b, float c, float _X, float _Y, float _Z, float _AngleX, float _AngleY, float _AngleZ, string _Name, string Comment);
	void Draw();
	void GenerateVertex();
private:
	float VertexX[4];
	float VertexY[4];
	float VertexZ[4];
	//GLuint Textures;
};

