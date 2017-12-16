#include "stdafx.h"
#include "Cylinder.h"
#include <string.h>
#include <iostream>
#include <windows.h> 
#include <fstream>
using namespace System;
using namespace std;
#define Pi 3.14159265359

Cylinder::Cylinder()
{
}


Cylinder::~Cylinder()
{
}

void Cylinder::Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment)
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

void Cylinder::Draw()
{
	glTranslatef(X, Y, Z);
	
	glRotatef(AngleX, 1.0, 0.0, 0.0);
	glRotatef(AngleY, 0.0, 1.0, 0.0);
	glRotatef(AngleZ, 0.0, 0.0, 1.0);


	DrawCircle(a, a, 0, Textures[0]);
	DrawCylinder(a, b, c);
	DrawCircle(a, a, c, Textures[1]);


	glRotatef(-AngleX, 1.0, 0.0, 0.0);
	glRotatef(-AngleY, 0.0, 1.0, 0.0);
	glRotatef(-AngleZ, 0.0, 0.0, 1.0);

	glTranslatef(-X, -Y, -Z);
	
}

void Cylinder::DrawCylinder(float RadiusX, float Angles, float c)
{

	glBindTexture(GL_TEXTURE_2D, Textures[2]);

	float angle, radian, x, y, vx, vy, tx, ty;

	glBegin(GL_TRIANGLE_STRIP);

	for (angle = 0.0; angle <= 360.0; angle += 360 / Angles)
	{
			radian = angle * (Pi / 180.0f);
			x = (float)cos(radian);
			y = (float)sin(radian);
			tx = x * 0.5 + 0.5;
			ty = y * 0.5 + 0.5;
			vx = x * RadiusX;
			vy = y * RadiusX;
			glTexCoord2f(tx, 0);
			glVertex3f(vx, vy, 0);
			glTexCoord2f(tx, 1);
			glVertex3f(vx, vy, c);
	}

	glEnd();

}

