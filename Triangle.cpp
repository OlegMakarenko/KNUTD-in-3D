#include "stdafx.h"
#include "Triangle.h"
#include <string.h>
#include "Draw.h"
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <windows.h> 
using namespace System;
using namespace std;

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

void Triangle::Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment)
{

	this->a = a;
	this->b = b;

	GenerateVertex();

	this->X = X;
	this->Y = Y;
	this->Z = Z;

	this->AngleX = AngleX;
	this->AngleY = AngleY;
	this->AngleZ = AngleZ;

	this->Name = Name;
	this->Comment = Comment;

	LinkTextures();
}

void Triangle::GenerateVertex()
{
	VertexX[0] = -a / 2;
	VertexY[0] = -1 * b / 2;
	VertexZ[0] = 0;

	VertexX[1] = a / 2;
	VertexY[1] = -1 * b / 2;
	VertexZ[1] = 0;

	VertexX[2] = 0;
	VertexY[2] = b / 2;
	VertexZ[2] = 0;
}

void Triangle::Draw()
{
	glTranslatef(X, Y, Z);

	glRotatef(AngleX, 1.0, 0.0, 0.0);
	glRotatef(AngleY, 0.0, 1.0, 0.0);
	glRotatef(AngleZ, 0.0, 0.0, 1.0);



	glBindTexture(GL_TEXTURE_2D, Textures[0]);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0, 0); glVertex3f(VertexX[0], VertexY[0], VertexZ[0]);
	glTexCoord2f(1, 0); glVertex3f(VertexX[1], VertexY[1], VertexZ[1]);
	glTexCoord2f(0.5, 1); glVertex3f(VertexX[2], VertexY[2], VertexZ[2]);
	glEnd();




	glRotatef(-AngleX, 1.0, 0.0, 0.0);
	glRotatef(-AngleY, 0.0, 1.0, 0.0);
	glRotatef(-AngleZ, 0.0, 0.0, 1.0);

	glTranslatef(-X, -Y, -Z);
}