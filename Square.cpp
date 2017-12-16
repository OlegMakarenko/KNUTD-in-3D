#include "stdafx.h"
#include "Square.h"
#include <string.h>
#include "Draw.h"
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <windows.h> 
using namespace System;
using namespace std;

Square::Square()
{
}

Square::~Square()
{
}

void Square::Initialize(float a, float b, float c, float _X, float _Y, float _Z, float _AngleX, float _AngleY, float _AngleZ, string _Name, string Comment)
{
	
	this->a = a;
	this->b = b;

	GenerateVertex();

	X = _X;
	Y = _Y;
	Z = _Z;

	AngleX = _AngleX;
	AngleY = _AngleY;
	AngleZ = _AngleZ;

	Name = _Name;
	this->Comment = Comment;

	LinkTextures();
}

void Square::GenerateVertex()
{
	VertexX[0] = -1 * a / 2;
	VertexY[0] = 0;
	VertexZ[0] = b / 2;
	VertexX[1] = a / 2;
	VertexY[1] = 0;
	VertexZ[1] = b / 2;
	VertexX[2] = -1 * a / 2;
	VertexY[2] = 0;
	VertexZ[2] = -1 * b / 2;
	VertexX[3] = a / 2;
	VertexY[3] = 0;
	VertexZ[3] = -1 * b / 2;
}

void Square::Draw()
{
	glTranslatef(X, Y, Z);

	glRotatef(AngleX, 1.0, 0.0, 0.0);
	glRotatef(AngleY, 0.0, 1.0, 0.0);
	glRotatef(AngleZ, 0.0, 0.0, 1.0);


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, Textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(VertexX[0], VertexY[0], VertexZ[0]);
	glTexCoord2f(1, 0); glVertex3f(VertexX[1], VertexY[1], VertexZ[1]);
	glTexCoord2f(1, 1); glVertex3f(VertexX[3], VertexY[3], VertexZ[3]);
	glTexCoord2f(0, 1); glVertex3f(VertexX[2], VertexY[2], VertexZ[2]);
	glEnd();


	
	glRotatef( - AngleX, 1.0, 0.0, 0.0);
	glRotatef( - AngleY, 0.0, 1.0, 0.0);
	glRotatef( - AngleZ, 0.0, 0.0, 1.0);
	
	glTranslatef(-X, -Y, -Z);

}