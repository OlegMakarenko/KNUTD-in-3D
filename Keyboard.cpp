#include "stdafx.h"
#include "Keyboard.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;


TKeyboard::TKeyboard()
{
}


TKeyboard::~TKeyboard()
{
}

void TKeyboard::Check(Player &player)
{
	int Speed = 1;

	if (Keyboard::isKeyPressed(Keyboard::LShift))
		Speed = 2;

	if (Keyboard::isKeyPressed(Keyboard::Space)) 
		player.Jump();

	if (Keyboard::isKeyPressed(Keyboard::W))
		player.Forward(Speed);

	if (Keyboard::isKeyPressed(Keyboard::S))
		player.Back(Speed);

	if (Keyboard::isKeyPressed(Keyboard::D))
		player.Right(Speed);

	if (Keyboard::isKeyPressed(Keyboard::A))
		player.Left(Speed);

	if (Keyboard::isKeyPressed(Keyboard::Down))
		player.Y -= 0.5;

	if (Keyboard::isKeyPressed(Keyboard::Up))
		player.Y += 0.5;
}
