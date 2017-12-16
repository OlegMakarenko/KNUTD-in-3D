#pragma once
#include "DynamicMapObject.h"
#include "Camera.h"
#include <SFML\Audio.hpp>


class Player : public DynamicMapObject
{
public:
	Player(float _X, float _Y, float _Z, Envir::Environment &environment);
	~Player();
	float CameraX;
	float CameraY;
	float Sensivity;
	void Forward(float SpeedCoefficient);
	void Back(float SpeedCoefficient);
	void Left(float SpeedCoefficient);
	void Right(float SpeedCoefficient);
private:
	sf::Music SoundGoing;
	sf::Music SoundRunning;
	sf::Music SoundJumping;
};

