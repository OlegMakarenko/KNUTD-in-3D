#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#include "Player.h"
#include "Environment.h"
#include "Keyboard.h"
#include "Draw.h"
#include "StaticMapObject.h"
#include <fstream>
#include <sstream>
#include "Box.h"
#include "Square.h"
#include "ExternalObject.h"
#include "Triangle.h"
#include "Circle.h"
#include "Cylinder.h"
#include "Line.h"
#include "Cone.h"
#include "TexturesContainer.h"
#include "MyText.h"
#include "Form1.h"
#include "FormMenu.h"
#include "FormStart.h"
#include <msclr\marshal_cppstd.h>
#include "Map.h"
#include "Game.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;

#define Pi 3.14159265359
using namespace sf;
using namespace std;



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		RECT rect;
		GetWindowRect(hWnd, &rect);
		break;
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//////////[Window init]


	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 2;

	//RenderWindow window(VideoMode::getDesktopMode(), "GTA KNUTD", sf::Style::Default, settings);
	RenderWindow window(VideoMode::VideoMode(1000, 1000, 32), "GTA KNUTD", sf::Style::None, settings);

	//////////[OpenGl init]
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 3000.f);
	glEnable(GL_TEXTURE_2D);
	ShowCursor(FALSE);
	//glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	//////////[Forms init]
	FormMapEditor::Form1^ f2 = gcnew FormMapEditor::Form1;
	FormMenuSpace::FormMenu^ formMenu = gcnew FormMenuSpace::FormMenu;
	FormStartSpace::FormStart^ formStart = gcnew FormStartSpace::FormStart;
	f2->Runing = 0;
	formStart->Show();
	formStart->ReDraw();
	formStart->BringToFront();

	//////////[Gray no-textures]
	Draw::LoadTexture("objects\\1\\jpeg\\0.jpg");

	//////////[Main classes init]
	Clock clock;
	Envir::Environment environment;
	Player player(0, 0, 0, environment);
	TKeyboard keyboard;
	Map map;
	sf::Music MainTheme;
	MainTheme.openFromFile("Audio\\UI\\Start.ogg");
	MainTheme.play();

	//////////[Create environment & effects]
	environment.CreateLight();
	environment.CreateSkybox(1500);
	Texture TMask;
	TMask.loadFromFile("resources\\Mask.png");
	Sprite SMask;
	SMask.setTexture(TMask);

	
	//////////[Variables]
	bool StopCursor = 0;
	float CameraY = 0,
		CameraX = 0;

	//////////[Map & Game init]
	map.PreparationMap(formStart);
	Game game(player, map);
	Box *box = new Box[map.BoxCount];
	Circle *circle = new Circle[map.CircleCount];
	Cone *cone = new Cone[map.ConeCount];
	Cylinder *cylinder = new Cylinder[map.CylinderCount];
	Line *line = new Line[map.LineCount];
	Square *square = new Square[map.SquareCount];
	Triangle *triangle = new Triangle[map.TriangleCount];
	StaticMapObject** Obj;
	Obj = new StaticMapObject*[map.StaticCount];


	map.LinkObjects(box, circle, cone, cylinder, line, square, triangle, Obj);
	map.LoadObjectsParamFromFile(Obj);
	f2->LinkObj(Obj, map.StaticCount);

	//MyText Tx0(50, 180, 20, sf::Color::Red, sf::Text::Bold);
	//MyText Tx1(50, 210, 20, sf::Color::Red, sf::Text::Bold);
	//MyText Tx2(50, 240, 20, sf::Color::Red, sf::Text::Bold);
	
	formStart->Close();
	delete formStart;
	MainTheme.stop();
	environment.PlaySounds();
	short int LoopStep = 1, i=0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////[Main loop]/////////
	while (window.isOpen())
    {
		//////////[reset timer, events]
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time / 50;
		if (time>3) time = 3;
        Event event;
        while (window.pollEvent(event))
        {
			if (event.type == Event::GainedFocus)
			{
				if (f2->Runing)
					f2->BringToFront();
				if (formMenu->Runing)
					formMenu->BringToFront();
			}

            if (event.type == Event::Closed)
				window.close();
        }
		float3 q;

		//////////[Update & control]
		player.Update(time, environment);
		keyboard.Check(player);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glTranslatef(player.X, player.Y, player.Z);

		//////////[Camera values]
		POINT mousexy;
		GetCursorPos(&mousexy);
		int xt = window.getPosition().x + 400;
		int yt = window.getPosition().y + 300;
		if (!f2->Runing && !formMenu->Runing)
		{
			player.CameraX += (xt - mousexy.x) / player.Sensivity;
			player.CameraY += (yt - mousexy.y) / player.Sensivity;

			if (player.CameraY<-89.0){ player.CameraY = -89.0; }
			if (player.CameraY>89.0){ player.CameraY = 89.0; }
			SetCursorPos(xt, yt);
		}

		//////////[Model view]
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//////////[Skybox position & camera moving]
		gluLookAt(player.X, player.Y + player.Height / 2, player.Z, player.X - sin(player.CameraX / 180 * Pi), player.Y + player.Height / 2 + (tan(player.CameraY / 180 * Pi)), player.Z - cos(player.CameraX / 180 * Pi), 0, 1, 0);
		glTranslatef(player.X, player.Y, player.Z);
		environment.DrawSkybox();
		glTranslatef(-player.X, -player.Y, -player.Z);

		//////////[Fog control & light]
		if (Keyboard::isKeyPressed(Keyboard::G))
			environment.setFog(1000.0f);
		if (Keyboard::isKeyPressed(Keyboard::H))
			environment.setFog(2000.0f);
		environment.setLight(-player.X - sin(player.CameraX / 180 * Pi), -player.Y + player.Height / 2 + (tan(player.CameraY / 180 * Pi)) - player.Z - cos(player.CameraX / 180 * Pi), -player.Z - cos(player.CameraX / 180 * Pi));
		
		//////////[Map editor & Game running]
		map.MapEditor(Obj, f2, formMenu);
		game.Act(time);

		//////////[Drawing]
		for (int i = 0; i < map.StaticCount; i++)
			Obj[i]->Draw();
		glNormal3d(0, 1, 0);
		window.pushGLStates();
		game.DrawSprites(window);
		window.draw(SMask);
		map.DrawTextInfo(window, Obj, player);
        window.popGLStates();	
        window.display();


		if (LoopStep==2)
		{
			player.X = -73;
			player.Y = 150;
			player.Z = 121;
			player.BottomCollision = 0;
			environment.setFog(2000.0f);
			CameraX = 0;
			CameraY = 0;
		}

		if (game.getStatus() == 0)
			environment.setFog(1000.0f);
		if (game.getStatus() == 4)
			environment.setFog(2000.0f);
		///

		///

		if (LoopStep <= 2)LoopStep++;

    }
    return 0;
}



