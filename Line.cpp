#include "stdafx.h"
#include "Line.h"
#include <string.h>
#include "Draw.h"
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <windows.h> 
#include <fstream>
using namespace System;
using namespace std;
#define Pi 3.14159265359


Line::Line()
{
}


Line::~Line()
{
}

void Line::Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment)
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

void Line::GenerateVertex()
{

}

void Line::Draw()
{
	glTranslatef(X, Y, Z);

	glRotatef(AngleX, 1.0, 0.0, 0.0);
	glRotatef(AngleY, 0.0, 1.0, 0.0);
	glRotatef(AngleZ, 0.0, 0.0, 1.0);


	glLineWidth(b);
	glBindTexture(GL_TEXTURE_2D, Textures[0]);
	glBegin(GL_LINES);
	glTexCoord2f(0, 0);
	glVertex3f(-a/2, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(a/2, 0, 0);
	glEnd();


	glRotatef(-AngleX, 1.0, 0.0, 0.0);
	glRotatef(-AngleY, 0.0, 1.0, 0.0);
	glRotatef(-AngleZ, 0.0, 0.0, 1.0);

	glTranslatef(-X, -Y, -Z);
}


