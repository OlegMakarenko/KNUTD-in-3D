#include "stdafx.h"
#include "Draw.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#define GL_CLAMP_TO_EDGE 0x812F
using namespace sf;


Draw::Draw()
{
}


Draw::~Draw()
{
}

GLuint Draw::LoadTexture(sf::String name)
{
	sf::Image image;
	if (!image.loadFromFile(name))
		return EXIT_FAILURE;

	image.flipVertically();
	image.createMaskFromColor(Color(0, 0, 0));

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return texture;
}

void Draw::Box(GLuint Texture[], float size)
{
	glBindTexture(GL_TEXTURE_2D, Texture[0]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);   glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 0);   glVertex3f(size, -size, -size);
	glTexCoord2f(1, 1);   glVertex3f(size, size, -size);
	glTexCoord2f(0, 1);   glVertex3f(-size, size, -size);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, Texture[1]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, size);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, Texture[2]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();

	
	glBindTexture(GL_TEXTURE_2D, Texture[3]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Texture[4]);
	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Texture[5]);
	glBegin(GL_QUADS);
	//top  		
	glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();
}

void Draw::Piped(GLuint Texture[], float a, float b, float c)
{
	glBindTexture(GL_TEXTURE_2D, Texture[0]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);   glVertex3f(-a, -b, -c);
	glTexCoord2f(1, 0);   glVertex3f(a, -b, -c);
	glTexCoord2f(1, 1);   glVertex3f(a, b, -c);
	glTexCoord2f(0, 1);   glVertex3f(-a, b, -c);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Texture[1]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0); glVertex3f(-a, -b, c);
	glTexCoord2f(1, 0); glVertex3f(-a, -b, -c);
	glTexCoord2f(1, 1); glVertex3f(-a, b, -c);
	glTexCoord2f(0, 1); glVertex3f(-a, b, c);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Texture[2]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0); glVertex3f(a, -b, c);
	glTexCoord2f(1, 0); glVertex3f(-a, -b, c);
	glTexCoord2f(1, 1); glVertex3f(-a, b, c);
	glTexCoord2f(0, 1); glVertex3f(a, b, c);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Texture[2]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0); glVertex3f(-a, -b, c);
	glTexCoord2f(1, 0); glVertex3f(-a, -b, -c);
	glTexCoord2f(1, 1); glVertex3f(-a, b, -c);
	glTexCoord2f(0, 1); glVertex3f(-a, b, c);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Texture[3]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0, 0); glVertex3f(a, -b, -c);
	glTexCoord2f(1, 0); glVertex3f(a, -b, c);
	glTexCoord2f(1, 1); glVertex3f(a, b, c);
	glTexCoord2f(0, 1); glVertex3f(a, b, -c);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Texture[4]);
	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(0, 0); glVertex3f(-a, -b, c);
	glTexCoord2f(1, 0); glVertex3f(a, -b, c);
	glTexCoord2f(1, 1); glVertex3f(a, -b, -c);
	glTexCoord2f(0, 1); glVertex3f(-a, -b, -c);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Texture[5]);
	glBegin(GL_QUADS);
	//top  		
	glTexCoord2f(0, 0); glVertex3f(-a, b, -c);
	glTexCoord2f(1, 0); glVertex3f(a, b, -c);
	glTexCoord2f(1, 1); glVertex3f(a, b, c);
	glTexCoord2f(0, 1); glVertex3f(-a, b, c);
	glEnd();
}