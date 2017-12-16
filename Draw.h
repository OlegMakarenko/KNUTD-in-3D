#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
class Draw
{
public:
	Draw();
	~Draw();
	static GLuint LoadTexture(sf::String name);
	static void Box(GLuint Texture[], float size);
	static void Piped(GLuint Texture[], float a, float b, float c);
};

