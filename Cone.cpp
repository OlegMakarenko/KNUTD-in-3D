#include "stdafx.h"
#include "Cone.h"
#include <string.h>
#include "Draw.h"
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <windows.h> 
#include <fstream>
using namespace System;
using namespace std;
#define Pi 3.14159265359

Cone::Cone()
{
}


Cone::~Cone()
{
}

void Cone::Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment)
{

	this->a = a;
	this->b = b;
	this->c = c;

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

void Cone::Draw()
{
	glTranslatef(X, Y, Z);

	glRotatef(AngleX, 1.0, 0.0, 0.0);
	glRotatef(AngleY, 0.0, 1.0, 0.0);
	glRotatef(AngleZ, 0.0, 0.0, 1.0);


	//DrawCircle(a, b, 0, Textures[0]);
	DrawCone(a, b, c);


	glRotatef(-AngleX, 1.0, 0.0, 0.0);
	glRotatef(-AngleY, 0.0, 1.0, 0.0);
	glRotatef(-AngleZ, 0.0, 0.0, 1.0);

	glTranslatef(-X, -Y, -Z);
}

void Cone::DrawCone(float Radius, float b, float Angles)
{

	glBindTexture(GL_TEXTURE_2D, Textures[0]);

	float angle, radian, x, y, vx, vy, tx, ty;

	glBegin(GL_TRIANGLE_STRIP);

	for (angle = 0.0; angle<=360.0; angle += 360/Angles)
	{
		radian = angle * (Pi / 180.0f);
		x = (float)cos(radian);
		y = (float)sin(radian);
		tx = x * 0.5 + 0.5;
		ty = y * 0.5 + 0.5;
		vx = x * Radius;
		vy = y * Radius;
		glTexCoord2f(0, ty);
		glVertex3f(vx, vy, 0);
		glTexCoord2f(1, 0);
		glVertex3f(0, 0, b);
	}

	glEnd();

}

void Cone::GenerateVertex(){}