#pragma once
#include "HollowCylinder.h"
#include "Player.h"
#include "Cone.h"
#include "Box.h"
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string.h>
#include "map.h"
#include <math.h>
#include <time.h>
#include "Hud.h"

class Zlo2
{
public: 
	Zlo2();
	int Act(float PlayerX, float PlayerZ, float time);//
	//1 - game over
	//2 - rdead
	//3 - rdoshot
	void SetStartParam();
	float XShot();
	bool Live;
	void Init(Map *map);
	void SoundsStop();
private:
	void Move(float PlayerX, float PlayerZ, float time);
	void Draw();
	bool CheckPlayer(float PlayerX, float PlayerZ);
	void WheelRotate(float time, bool Direction);
//	void DoShot();
	void CheckHP();
	void GetDamage(int D);
	friend void ChangeVolume(sf::Music *sound, float X, float Z, float PlayerX, float PlayerZ);


	Cylinder wheel[4];
	Box platform;
	Box body;
	Cylinder face;
	Box HPBox;

	float X; 
	float Z;
	int MaxX;
	int MinX;
	int HP;
	float Speed;
	float timer;
	short int DamageSoundCount;


	float wheelX[4];
	float platformX;
	float bodyX;
	float faceX;
	float HPBoxX;

	sf::Music SoundDamage1;
	sf::Music SoundDamage2;
	sf::Music SoundMove;
	sf::Music SoundDie;

	Map *map;

};


class Plot
{
public:
	Plot();
	~Plot();
	bool Act(float _time);
	void setClasses(Player *_player, Map *map, sf::Text &_subtitles);
	int Counter;
private:
	void GameOver();
	bool End();
	void ConeAct();
	bool ZloAct();
	void InitObj();
	friend void ChangeVolume(sf::Music *sound, float X, float Z, float PlayerX, float PlayerZ);
	Player *player;
	Map *map;
	sf::Text *subtitles;
	Cone cone;
	Box Zlo[6];
	Zlo2 zlo2;
	const int ZloXFirst = 1;
	const int ConeMaxY = 26;
	const int ConeMinY = 22;
	bool ConeDirection;
	float time;

	sf::Music SoundStart;
	sf::Music SoundWin;
	sf::Music SoundDeath;
	sf::Music *SoundMove;

};

class Game
{
public:
	Game(Player &_player, Map &map);
	~Game();
	void Act(float time);
	bool Started;
	void DrawSprites(sf::RenderWindow &window);
	short int getStatus();
private:
	HollowCylinder cylinder;
	Player *player;
	Map *map;
	Hud hud;
	Plot plot;
	void Game::Start();
	sf::Text subtitles;
	sf::Font font;
};


