#pragma once
#include "Draw.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#define GL_CLAMP_TO_EDGE 0x812F
using namespace sf;
namespace Envir{
	class Environment
	{
	public:
		Environment();
		Environment(const Environment &e);
		~Environment();
		bool GetCollosion(int _X, int _Y, int _Z);
		void CreateSkybox(float _SkyboxSize);
		void DrawSkybox();
		void CreatCollision();
		int getCollision(int i, int j);
		void CreateLight();
		void setLight(float a, float b, float c);
		void setFog(float End);
		int getCollisionCount();
		void PlaySounds();
		/*Sprite SHud;
		Sprite SMap1;
		Sprite SMap2;
		Sprite SEsc;*/
	private:
		int CollisionCount;
		GLuint SkyboxTexture[6];
		void SetSkyboxTexture();
		float SkyboxSize,
			LightDirection[3],
			LightPosition[4];
		bool CollisionMap[300][300][10];
		int CollisionMatrix[26][26];
		float ambient[4];
		GLfloat dim_light[4];
		GLfloat fogColor[4]; 
		sf::Music SoundWind;
		/*Texture THud;
		Texture TMap1;
		Texture TMap2;
		Texture TEsc;*/
	};
}

