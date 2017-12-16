#pragma once
#include "Enity.h"
#include "TexturesContainer.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Draw.h"
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <string>
using namespace std;
using namespace sf;

class StaticMapObject :
	public Enity
{
public:
	StaticMapObject();
	~StaticMapObject();
	float Z, a, b, c;
	float AngleX, AngleY, AngleZ;
	void SetTC(TexturesContainer *texturesContainer, int TexturesContainerCount);
	virtual void Draw()=0;	
	virtual void GenerateVertex() = 0;
	virtual void Initialize(float, float , float , float , float , float , float , float , float , string, string ) = 0;
	void SetTexture(int Count, string Name, int FileCont);
	string Name;
	string Comment;
protected:
	TexturesContainer *texturesContainer;
	int TexturesContainerCount;
	void LinkTextures();
	GLuint *Textures;
};

