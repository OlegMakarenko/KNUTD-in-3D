#pragma once
#include "MapObject.h"
#include "Environment.h"
#include <SFML\Audio.hpp>
class DynamicMapObject :
	public MapObject
{
public:
	DynamicMapObject();
	~DynamicMapObject();
	bool BottomCollision;
	float Speed;
	float Height;
	float Width;
	float Depth;
	float GroundHeight;
	void Update(float _Time, Envir::Environment &environment);
	void Jump();
protected:
	float BoostX;
	float BoostY;
	float BoostZ;
	void Action(float BoostX, float BoostY, float BoostZ);
	short int CheckCollision(float _Time);
	Envir::Environment *environment;
};

