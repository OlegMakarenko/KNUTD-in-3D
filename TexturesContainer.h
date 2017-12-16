#pragma once
#include "TexturesContainer.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
using namespace sf;
using namespace std;

class TexturesContainer
{
public:
	TexturesContainer();
	~TexturesContainer();
	int Count;
	void LoadTextures(string Name, int Count);
	string GetName();
	string Name;
	GLuint *GetTexture();
private:
	GLuint *Textures;
};

