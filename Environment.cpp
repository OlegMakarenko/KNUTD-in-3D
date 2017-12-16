#include "stdafx.h"
#include "Environment.h"
#include "Draw.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#define GL_CLAMP_TO_EDGE 0x812F
using namespace sf;
using namespace Envir;

Environment::Environment()
{
	CollisionCount = 26;
	CreatCollision();
	LightPosition[0] = -400;
	LightPosition[1] = 400;
	LightPosition[2] = -200;
	LightPosition[3] = 1;
	ambient[0] = 0.5;
	ambient[1] = 0.5;
	ambient[2] = 0.5;
	ambient[3] = 1;
	dim_light[0] = 0.0f;
	dim_light[1] = 0.0f;
	dim_light[2] = 0.0f;
	dim_light[3] = 1.0f;
	fogColor[0] = 0.9f,
	fogColor[1] = 0.9f;
	fogColor[2] = 0.9f;
	fogColor[3] = 1.0f;
	SoundWind.openFromFile("Audio\\Environment\\Wind.ogg");
	SoundWind.setLoop(1);

}


Environment::~Environment()
{
	for (int i = 0; i < 300; i++)
	for (int j = 0; j < 300; j++)
	for (int k = 0; k < 10; k++)
		CollisionMap[i][j][k] = 0;
}

Environment::Environment(const Environment &e)
{
	for (int i = 0; i < 300; i++)
	for (int j = 0; j < 300; j++)
	for (int k = 0; k < 10; k++)
		CollisionMap[i][j][k] = e.CollisionMap[i][j][k];
}

bool Environment::GetCollosion(int _X, int _Y, int _Z)
{
	if (_Y<0) return 1;
	return CollisionMap[_X][_Y][_Z];
}

void Environment::CreateSkybox(float _SkyboxSize)
{
	SkyboxSize = _SkyboxSize;
	SetSkyboxTexture();
}

void Environment::DrawSkybox()
{
	Draw::Box(SkyboxTexture, SkyboxSize);
}

void Environment::SetSkyboxTexture()
{
	SkyboxTexture[0] = Draw::LoadTexture("resources/skybox/skybox_front.bmp");
	SkyboxTexture[1] = Draw::LoadTexture("resources/skybox/skybox_back.bmp");
	SkyboxTexture[2] = Draw::LoadTexture("resources/skybox/skybox_left.bmp");
	SkyboxTexture[3] = Draw::LoadTexture("resources/skybox/skybox_right.bmp");
	SkyboxTexture[4] = Draw::LoadTexture("resources/skybox/skybox_bottom.bmp");
	SkyboxTexture[5] = Draw::LoadTexture("resources/skybox/skybox_top.bmp");
}

void Environment::CreatCollision()
{
	std::ifstream CollisionFile("Objects\\Collision.txt");
	std::string buf;
	for (int i = 0; i < CollisionCount; i++)
	{
		std::getline(CollisionFile, buf, '\t');
		CollisionMatrix[i][0] = atoi(buf.c_str());
		std::getline(CollisionFile, buf, '\n');
		CollisionMatrix[i][1] = atoi(buf.c_str());
	}
}

int Environment::getCollision(int i, int j)
{
	return CollisionMatrix[i][j];
}

int Environment::getCollisionCount()
{
	return CollisionCount;
}

void Environment::CreateLight()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, dim_light);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);

	//GLfloat ambient[4] = { 0.9f, 0.5f, 0.2f, 1.f };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
}

void Environment::setFog(float End)
{
	glEnable(GL_FOG);                       
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);        
	glFogf(GL_FOG_DENSITY, 0.35f);          
	glHint(GL_FOG_HINT, GL_DONT_CARE);      
	glFogf(GL_FOG_START, 1.0f);             
	glFogf(GL_FOG_END, End);               
}

void Environment::setLight(float a, float b, float c)
{
	LightDirection[0] = a;
	LightDirection[1] = b;
	LightDirection[2] = c;
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDirection);
}

void Environment::PlaySounds()
{
	SoundWind.play();
}