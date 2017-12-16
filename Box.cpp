#include "stdafx.h"
#include "Box.h"
#include <string.h>
#include "Draw.h"
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <windows.h> 
using namespace System;
using namespace std;


Box::Box()
{
}

Box::~Box()
{
}


void Box::Initialize(float a, float b, float c, float _X, float _Y, float _Z, float _AngleX, float _AngleY, float _AngleZ, string _Name, string Comment)
{
	this->a = a;
	this->b = b;
	this->c = c;

	GenerateVertex();

	this->X = _X;
	this->Y = _Y;
	this->Z = _Z;

	this->AngleX = _AngleX;
	this->AngleY = _AngleY;
	this->AngleZ = _AngleZ;

	this->Name = _Name;
	this->Comment = Comment;

	int ContrainerIndex = 0;

	LinkTextures();
}

void Box::GenerateVertex()
{
	VertexX[0] = -1 * a / 2;
	VertexY[0] = b / 2;
	VertexZ[0] = c / 2;
	VertexX[1] = -1 * a / 2;
	VertexY[1] = -1 * b / 2;
	VertexZ[1] = c / 2;
	VertexX[2] = a / 2;
	VertexY[2] = -1 * b / 2;
	VertexZ[2] = c / 2;
	VertexX[3] = a / 2;
	VertexY[3] = b / 2;
	VertexZ[3] = c / 2;
	VertexX[4] = -1 * a / 2;
	VertexY[4] = b / 2;
	VertexZ[4] = -1 * c / 2;
	VertexX[5] = -1 * a / 2;
	VertexY[5] = -1 * b / 2;
	VertexZ[5] = -1 * c / 2;
	VertexX[6] = a / 2;
	VertexY[6] = -1 * b / 2;
	VertexZ[6] = -1 * c / 2;
	VertexX[7] = a / 2;
	VertexY[7] = b / 2;
	VertexZ[7] = -1 * c / 2;
}

void Box::Draw()
{
	glTranslatef(X, Y, Z);

	glRotatef(AngleX, 1.0, 0.0, 0.0);
	glRotatef(AngleY, 0.0, 1.0, 0.0);
	glRotatef(AngleZ, 0.0, 0.0, 1.0);


	glBindTexture(GL_TEXTURE_2D, Textures[0]);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 0);   glVertex3f(VertexX[5], VertexY[5], VertexZ[5]);
	glTexCoord2f(1, 0);   glVertex3f(VertexX[6], VertexY[6], VertexZ[6]);
	glTexCoord2f(1, 1);   glVertex3f(VertexX[7], VertexY[7], VertexZ[7]);
	glTexCoord2f(0, 1);   glVertex3f(VertexX[4], VertexY[4], VertexZ[4]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Textures[1]);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0); glVertex3f(VertexX[1], VertexY[1], VertexZ[1]);
	glTexCoord2f(1, 0); glVertex3f(VertexX[5], VertexY[5], VertexZ[5]);
	glTexCoord2f(1, 1); glVertex3f(VertexX[4], VertexY[4], VertexZ[4]);
	glTexCoord2f(0, 1); glVertex3f(VertexX[0], VertexY[0], VertexZ[0]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Textures[2]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0); glVertex3f(VertexX[2], VertexY[2], VertexZ[2]);
	glTexCoord2f(1, 0); glVertex3f(VertexX[1], VertexY[1], VertexZ[1]);
	glTexCoord2f(1, 1); glVertex3f(VertexX[0], VertexY[0], VertexZ[0]);
	glTexCoord2f(0, 1); glVertex3f(VertexX[3], VertexY[3], VertexZ[3]);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, Textures[3]);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(0, 0); glVertex3f(VertexX[6], VertexY[6], VertexZ[6]);
	glTexCoord2f(1, 0); glVertex3f(VertexX[2], VertexY[2], VertexZ[2]);
	glTexCoord2f(1, 1); glVertex3f(VertexX[3], VertexY[3], VertexZ[3]);
	glTexCoord2f(0, 1); glVertex3f(VertexX[7], VertexY[7], VertexZ[7]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Textures[4]);
	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(0, 0); glVertex3f(VertexX[1], VertexY[1], VertexZ[1]);
	glTexCoord2f(1, 0); glVertex3f(VertexX[2], VertexY[2], VertexZ[2]);
	glTexCoord2f(1, 1); glVertex3f(VertexX[6], VertexY[6], VertexZ[6]);
	glTexCoord2f(0, 1); glVertex3f(VertexX[5], VertexY[5], VertexZ[5]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Textures[5]);
	glBegin(GL_QUADS);
	//top  		
	glTexCoord2f(0, 0); glVertex3f(VertexX[4], VertexY[4], VertexZ[4]);
	glTexCoord2f(1, 0); glVertex3f(VertexX[7], VertexY[7], VertexZ[7]);
	glTexCoord2f(1, 1); glVertex3f(VertexX[3], VertexY[3], VertexZ[3]);
	glTexCoord2f(0, 1); glVertex3f(VertexX[0], VertexY[0], VertexZ[0]);
	glEnd();



	glRotatef(-AngleX, 1.0, 0.0, 0.0);
	glRotatef(-AngleY, 0.0, 1.0, 0.0);
	glRotatef(-AngleZ, 0.0, 0.0, 1.0);

	glTranslatef(-X, -Y, -Z);

}