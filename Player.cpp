#include "stdafx.h"
#include "Player.h"
#define Pi 3.14159265359
#define CollisionSize 20
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;


Player::Player(float _X, float _Y, float _Z, Envir::Environment &environment)
{
	Speed = 2;
	X = _X;
	Y = _Y;
	Z = _Z;
	BoostX = 0.0f;
	BoostY = 0.0f;
	BoostZ = 0.0f;
	Height = 20;
	Width = 5;
	Depth = 5;
	CameraX=4;
	CameraY=4;
	Sensivity=4;
	this->environment = &environment;
	SoundGoing.openFromFile("Audio\\game\\Going.ogg");
	SoundRunning.openFromFile("Audio\\game\\Running.ogg");
	SoundJumping.openFromFile("Audio\\game\\Jumping.ogg");
}


Player::~Player()
{
}



void Player::Forward(float SpeedCoefficient)
{
	if (sf::SoundSource::Status::Playing != SoundGoing.getStatus() &&
		sf::SoundSource::Status::Playing != SoundRunning.getStatus())
	if (SpeedCoefficient==1)
		SoundGoing.play();
	else
		SoundRunning.play();
	BoostX = -sin(CameraX / 180 * Pi) * Speed*SpeedCoefficient;
	BoostZ = -cos(CameraX / 180 * Pi) * Speed*SpeedCoefficient;
}

void Player::Back(float SpeedCoefficient)
{
	if (sf::SoundSource::Status::Playing != SoundGoing.getStatus() &&
		sf::SoundSource::Status::Playing != SoundRunning.getStatus())
	if (SpeedCoefficient == 1)
		SoundGoing.play();
	else
		SoundRunning.play();
	BoostX = sin(CameraX / 180 * Pi) * Speed*SpeedCoefficient;
	BoostZ = cos(CameraX / 180 * Pi) * Speed*SpeedCoefficient;
}


void Player::Left(float SpeedCoefficient)
{
	if (sf::SoundSource::Status::Playing != SoundGoing.getStatus() &&
		sf::SoundSource::Status::Playing != SoundRunning.getStatus())
	if (SpeedCoefficient == 1)
		SoundGoing.play();
	else
		SoundRunning.play();
	BoostX = sin((CameraX - 90) / 180 * Pi) * Speed*SpeedCoefficient;
	BoostZ = cos((CameraX - 90) / 180 * Pi) * Speed*SpeedCoefficient;
}


void Player::Right(float SpeedCoefficient)
{
	if (sf::SoundSource::Status::Playing != SoundGoing.getStatus() &&
		sf::SoundSource::Status::Playing != SoundRunning.getStatus())
	if (SpeedCoefficient == 1)
		SoundGoing.play();
	else
		SoundRunning.play();
	BoostX = sin((CameraX + 90) / 180 * Pi) * Speed*SpeedCoefficient;
	BoostZ = cos((CameraX + 90) / 180 * Pi) * Speed*SpeedCoefficient;
}



