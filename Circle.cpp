#include "stdafx.h"
#include "Circle.h"
#include <string.h>
#include "Draw.h"
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <windows.h> 
#include <fstream>
using namespace System;
using namespace std;
#define Pi 3.14159265359

Circle::Circle()
{
}


Circle::~Circle()
{
}


void Circle::Initialize(float a, float b, float c, float X, float Y, float Z, float AngleX, float AngleY, float AngleZ, string Name, string Comment)
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

void Circle::GenerateVertex()
{

}

void Circle::Draw()
{
	glTranslatef(X, Y, Z);

	glRotatef(AngleX, 1.0, 0.0, 0.0);
	glRotatef(AngleY, 0.0, 1.0, 0.0);
	glRotatef(AngleZ, 0.0, 0.0, 1.0);

	DrawCircle(a, b, 0, Textures[0]);

	glRotatef(-AngleX, 1.0, 0.0, 0.0);
	glRotatef(-AngleY, 0.0, 1.0, 0.0);
	glRotatef(-AngleZ, 0.0, 0.0, 1.0);

	glTranslatef(-X, -Y, -Z);
}


void Circle::DrawCircle(float RadiusX, float RadiusY, float PositionZ, GLuint Textures)
{

	glBindTexture(GL_TEXTURE_2D, Textures);

	float angle, radian, x, y, vx, vy, tx, ty;

	glBegin(GL_POLYGON);

	for (angle = 0.0; angle<360.0; angle += 2.0)
	{
		radian = angle * (Pi / 180.0f);

		x = (float)cos(radian);
		y = (float)sin(radian);
		tx = x * 0.5 + 0.5;
		ty = y * 0.5 + 0.5;
		vx = x * RadiusX;
		vy = y * RadiusY;
		glTexCoord2f(tx, ty);
		glVertex3f(vx, vy, PositionZ);
	}

	glEnd();

}








/*


double angle;
int TmpX, TmpY;
for (int i = 0; i < 12; i++)
{
angle = 2 * Pi*i / 12;
TmpX = a*cos(angle);
TmpY = b*sin(angle);
VertexX[i] = TmpX;
VertexY[i] = TmpY;
VertexZ[i] = 0;
}



*/






//glBegin(GL_LINE_LOOP);
/*glTexCoord2f(0, 0.5); glVertex3f(VertexX[0], VertexY[0], VertexZ[0]);
glTexCoord2f(0.4325, 0.25); glVertex3f(VertexX[1], VertexY[1], VertexZ[1]);
glTexCoord2f(0.25, 0.4325); glVertex3f(VertexX[2], VertexY[2], VertexZ[2]);
glTexCoord2f(0.5, 0); glVertex3f(VertexX[3], VertexY[3], VertexZ[3]);
glTexCoord2f(0.725, 0.4325); glVertex3f(VertexX[4], VertexY[4], VertexZ[4]);
glTexCoord2f(0.9325, 0.25); glVertex3f(VertexX[5], VertexY[5], VertexZ[5]);
glTexCoord2f(1, 0.5); glVertex3f(VertexX[6], VertexY[6], VertexZ[6]);
glTexCoord2f(0.9325, 0.725); glVertex3f(VertexX[7], VertexY[7], VertexZ[7]);
glTexCoord2f(0.725, 0.9325); glVertex3f(VertexX[8], VertexY[8], VertexZ[8]);
glTexCoord2f(0.5, 1); glVertex3f(VertexX[9], VertexY[9], VertexZ[9]);
glTexCoord2f(0.25, 0.9325); glVertex3f(VertexX[10], VertexY[10], VertexZ[10]);
glTexCoord2f(0.4325, 0.725); glVertex3f(VertexX[11], VertexY[11], VertexZ[11]);
glEnd();
*/