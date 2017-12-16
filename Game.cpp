#include "stdafx.h"
#include "Game.h"

Zlo2::Zlo2()
{
	srand(time(NULL));
}

void Zlo2::Init(Map *map)
{
	Speed = 0.5;
	MaxX = 310;
	MinX = -10;
	wheelX[0] = 7;
	wheelX[1] = -7;
	wheelX[2] = 7;
	wheelX[3] = -7;
	platformX = 0;
	bodyX = 0;
	faceX = 0;
	HPBoxX = 0;
	X = 143;
	Z = 135;
	HP = 100;
	timer = 0;
	Live = 1;


	SoundDamage1.openFromFile("Audio\\Zlo2\\Damage1.ogg");
	SoundDamage2.openFromFile("Audio\\Zlo2\\Damage2.ogg");
	SoundMove.openFromFile("Audio\\Zlo2\\Move.ogg");
	SoundMove.setLoop(1);
	SoundDie.openFromFile("Audio\\Zlo2\\Die2.ogg");


	this->map = map;

	for (int i = 0; i < 2; i++)
	{
		wheel[i].SetTC(this->map->getTC(), this->map->TexturesContainerCount);
		wheel[i].Initialize(3, 360, 2, wheelX[i] + X, 7, Z - 6, 0, 0, 0, "Wheel", "");
	}
	for (int i = 2; i < 4; i++)
	{
		wheel[i].SetTC(this->map->getTC(), this->map->TexturesContainerCount);
		wheel[i].Initialize(3, 360, 2, wheelX[i] + X, 7, Z + 4, 0, 0, 0, "Wheel", "");
	}

	platform.SetTC(this->map->getTC(), this->map->TexturesContainerCount);
	body.SetTC(this->map->getTC(), this->map->TexturesContainerCount);
	face.SetTC(this->map->getTC(), this->map->TexturesContainerCount);
	HPBox.SetTC(this->map->getTC(), this->map->TexturesContainerCount);

	platform.Initialize(21, 3, 10, platformX + X, 9, Z, 0, 0, 0, "Platform", "");
	body.Initialize(9, 12, 3, bodyX + X, 16, Z + 1, 0, 0, 0, "Body", "");
	face.Initialize(3, 360, 1, faceX + X, 24, Z + 1, 0, 0, 0, "Face", "");
	HPBox.Initialize(10, 1, 1, HPBoxX + X, 29, Z + 1, 0, 0, 0, "HPBox", "");
}

void Zlo2::SetStartParam()
{
	X = 143;
	HP = 100;
	HPBox.SetTexture(2, "HPBox", 2);
	HPBox.SetTexture(0, "HPBox", 2);
	HPBox.SetTexture(4, "HPBox", 2);
	SoundMove.play();
	SoundMove.setVolume(0);
	Live = 1;
}

int Zlo2::Act(float PlayerX, float PlayerZ, float time)
{
	timer += time*0.5;
	if (timer >= 20) timer = 0;
	ChangeVolume(&SoundMove, X, Z, PlayerX, PlayerZ);
	if (Live)
	{
		Move(PlayerX, PlayerZ, time);
		Draw();
		if (CheckPlayer(PlayerX, PlayerZ))
		{
			SoundMove.stop();
			return 1;
		}
	}
	else
	{
		SoundDie.play();
		SoundMove.stop();
		return 2;
	}

	return 0;
}

void Zlo2::Move(float PlayerX, float PlayerZ, float time)
{
	bool Moving = 0;
	
	if (X < PlayerX && X > MinX)
	{
		if (sf::SoundSource::Status::Playing != SoundMove.getStatus())
			SoundMove.play();
		X -= Speed*time;
		WheelRotate(time, 1);
		Moving = 1;
		//SoundMove.setPosition(X, 7, Z);
	}

	if (X > PlayerX && X < MaxX)
	{
		if (sf::SoundSource::Status::Playing != SoundMove.getStatus())
			SoundMove.play();
		X += Speed*time;
		WheelRotate(time, 0);
		Moving = 1;
		//SoundMove.setPosition(X, 7, Z);
	}
	
		if (!Moving) SoundMove.pause();

	for (int i = 0; i < 4; i++)
	{
		wheel[i].X=wheelX[i]+X;
	}
	platform.X = platformX + X;
	body.X = bodyX + X;
	face.X = faceX + X;
	HPBox.X = HPBoxX + X;

}

void Zlo2::WheelRotate(float time, bool Direction)
{
	if (Direction)
	{
		for (int i = 0; i < 4; i++)
		{
			wheel[i].AngleZ += Speed * time * 8;
			wheel[i].AngleZ >= 30
				?
				wheel[i].AngleZ = 0 : 0;
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			wheel[i].AngleZ -= Speed * time * 8;
			wheel[i].AngleZ <= 0
				?
				wheel[i].AngleZ = 30 : 0;
		}
	}
}

bool Zlo2::CheckPlayer(float PlayerX, float PlayerZ)
{
	int ShootRadius = 10;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && timer>10)
	if ((X + platform.a / 2 + ShootRadius >= PlayerX) &&
		(X - platform.a / 2 - ShootRadius <= PlayerX) &&
		(Z - platform.c / 2 - ShootRadius <= PlayerZ) &&
		(Z + platform.c / 2 + ShootRadius >= PlayerZ))
		GetDamage(1);

	if ((X + platform.a/2  >= PlayerX) &&
		(X - platform.a/2  <= PlayerX) &&
		(Z - platform.c/2 <= PlayerZ) &&
		(Z + platform.c/2 >= PlayerZ))
		return 1;
	else return 0;
}

void Zlo2::GetDamage(int D)
{
	float r = rand() % 2;
	if (sf::SoundSource::Status::Playing != SoundDamage1.getStatus() &&
		sf::SoundSource::Status::Playing != SoundDamage2.getStatus())
	{
		r
			? SoundDamage1.play() : 0;
		!r
			? SoundDamage2.play() : 0;
	}
	HP -= D;
	CheckHP();
}

void Zlo2::CheckHP()
{
	if (HP > 74 && HP<100)
	{
		HPBox.SetTexture(2, "HPBox", 23);
		HPBox.SetTexture(0, "HPBox", 231);
		HPBox.SetTexture(4, "HPBox", 231);
		HPBox.SetTexture(3, "HPBox", 20);
	}
	if (HP>49 && HP<75)
	{
		HPBox.SetTexture(2, "HPBox", 22);
		HPBox.SetTexture(0, "HPBox", 221);
		HPBox.SetTexture(4, "HPBox", 221);
	}	
	if (HP>24 && HP < 50)
	{
		HPBox.SetTexture(2, "HPBox", 21);
		HPBox.SetTexture(0, "HPBox", 211);
		HPBox.SetTexture(4, "HPBox", 211);
	}
	if (HP>0 && HP < 25)
	{
		HPBox.SetTexture(2, "HPBox", 20);
		HPBox.SetTexture(0, "HPBox", 20);
		HPBox.SetTexture(4, "HPBox", 20);
		
	}
	if (HP == 0)
		Live = 0;
}

void Zlo2::SoundsStop()
{
	SoundMove.stop();
}


void Zlo2::Draw()
{
	for (int i = 0; i < 4; i++)
	{
		wheel[i].Draw();
	}
	platform.Draw();
	body.Draw();
	face.Draw();
	HPBox.Draw();
}

////PLOT

Plot::Plot()
{
	SoundMove = new sf::Music[6];
	Counter = 0;
	ConeDirection = 0;
	SoundStart.openFromFile("Audio\\Game\\MissionStart.ogg");
	SoundWin.openFromFile("Audio\\Game\\Win.ogg");
	SoundDeath.openFromFile("Audio\\Game\\Death.ogg");
	for (int i = 0; i < 6; i++)
	{
		SoundMove[i].openFromFile("Audio\\Zlo1\\Move.ogg");
		SoundMove[i].setLoop(1);
		SoundMove[i].setVolume(0);
	}
}


Plot::~Plot()
{
}

bool Plot::Act(float _time)
{
	time = _time;
	switch(Counter)
	{
		case 0: 
		{
				  for (int i = 0; i < 6; i++)
				  {
					  SoundMove[i].play();
					  SoundMove[i].setVolume(0);
				  }
			zlo2.SetStartParam();
			SoundStart.play();
			subtitles->setString(L"Уничтожьте повозку: подойдите как можно близко и нажмите ЛМБ");
			subtitles->setColor(sf::Color::White);
			Counter++;
			return 1;
		}
		case 1:
		{
			if (player->X > -100)
				Counter++;
			return 1;
		}
		case 2:
		{
			subtitles->setString(L"Не прикасайтесь к повозке и уклоняйтесь от матриц, чтоб выжить");
			subtitles->setColor(sf::Color::White);

			if (zlo2.Act(player->X, player->Z, time) == 1)
			{
				GameOver();
				Counter=4;
			}
			if (zlo2.Act(player->X, player->Z, time) == 2)
			{
				for (int i = 0; i < 6; i++)
					SoundMove[i].stop();
				Counter++;
			}

			if (ZloAct())
			{
				for (int i = 0; i < 6; i++)
					SoundMove[i].stop();
				GameOver();
				Counter=4;
			}
			return 1;
		}
		case 3:
		{
			subtitles->setString(L"Дойдите до первого корпуса, чтоб охладить");
			subtitles->setColor(sf::Color::White);
			ConeAct();
			if (End())
				Counter++;
			return 1;
		}
		case 4:
		{
			for (int i = 0; i < 6; i++)
				SoundMove[i].stop();
			zlo2.SoundsStop();
			Sleep(2000);
			subtitles->setString(L"");
			subtitles->setPosition(80, 900);
			subtitles->setCharacterSize(20);
			Counter = 0;
			return 0;
		}
	}
	return 0;
}

void Plot::setClasses(Player *_player, Map *map, sf::Text &_subtitles)
{
	player = _player;
	this->map = map;
	subtitles = &_subtitles;
	InitObj();
	zlo2.Init(map);
}

void Plot::InitObj()
{
	cone.SetTC(this->map->getTC(), this->map->TexturesContainerCount);
	cone.Initialize(5, 17, 10, 404, 24, 74, 90, 0, 0, "ConeGame", "");
	for (int i = 0; i < 6; i++)
	{
		Zlo[i].SetTC(this->map->getTC(), this->map->TexturesContainerCount);
		Zlo[i].Initialize(1, 28, 28, ZloXFirst + i * 60, 15, 100, 0, 0, 0, "Zlo_____", "");
	}
}

void Plot::ConeAct()
{
	if (!ConeDirection)
		cone.Y += time*0.5;
	if (ConeDirection)
		cone.Y -= time*0.5;
	if (cone.Y > ConeMaxY) ConeDirection = 1;
	if (cone.Y < ConeMinY) ConeDirection = 0;
	cone.Draw();
}

bool Plot::ZloAct()
{
	for (int i = 0; i < 6; i++)
		ChangeVolume(&SoundMove[i], Zlo[i].X, Zlo[i].Z, player->X, player->Z);
	for (int i = 0; i < 6; i++)
	{
		Zlo[i].Z -= (i + 1)*time*3;
		Zlo[i].AngleX -= (i + 1)*time*3;
		Zlo[i].Draw();
		if (Zlo[i].Z < -100)
			Zlo[i].Z = 210;
		if ((Zlo[i].X + Zlo[i].a+2 >= player->X) &&
			(Zlo[i].X - Zlo[i].a-2 <= player->X) &&
			(Zlo[i].Z - Zlo[i].b <= player->Z) &&
			(Zlo[i].Z + Zlo[i].b >= player->Z))
			return 1;	
	}
	return 0;
}

void Plot::GameOver()
{
	SoundDeath.play();
	subtitles->setString(L"ПОТРАЧЕНО");
	subtitles->setColor(sf::Color::White);
	subtitles->setCharacterSize(60);
	subtitles->setPosition(345, 500);
}

bool Plot::End()
{
	if ((cone.X + cone.a >= player->X) &&
		(cone.X - cone.a <= player->X) &&
		(cone.Z - cone.a <= player->Z) &&
		(cone.Z + cone.a >= player->Z))
	{
		SoundWin.play();
		subtitles->setString(L"ПЕРЕМОГА");
		subtitles->setColor(sf::Color::Yellow);
		subtitles->setCharacterSize(60);
		subtitles->setPosition(345, 500);
		return 1;
	}
	else
	return 0;
}



///////[Game class starts here]

Game::Game(Player &_player, Map &map)
{
	player = &_player;
	this->map = &map;
	cylinder.SetTC(this->map->getTC(), this->map->TexturesContainerCount);
	cylinder.Initialize(9, 16, 10, -286, 0, 180, 270, 0, 0, "StartGame_", "");
	Started = 0;
	plot.setClasses(player, this->map, subtitles);

	subtitles.setString(L"Подойдите к ларчику для начала миссии");
	subtitles.setColor(sf::Color::White);
	font.loadFromFile("fonts\\arial.ttf");
	subtitles.setFont(font);
	subtitles.setPosition(80, 900);
	subtitles.setCharacterSize(20);
	subtitles.setStyle(sf::Text::Bold);
}


Game::~Game()
{
}

void Game::Act(float time)
{
	!Started 
		? Start()
		: Started=plot.Act(time);
}

void Game::Start()
{
	cylinder.Draw();
	if ((cylinder.X + cylinder.a >= player->X) &&
		(cylinder.X - cylinder.a <= player->X) &&
		(cylinder.Z - cylinder.a <= player->Z) &&
		(cylinder.Z + cylinder.a >= player->Z))
		Started = 1;
}

void Game::DrawSprites(sf::RenderWindow &window)
{
	if (getStatus() == 1)
		window.draw(hud.SMap1);
	if (getStatus() == 3)
		window.draw(hud.SMap2);
	if (getStatus() != 10)
		window.draw(hud.SHud);
	window.draw(hud.SEsc);
	window.draw(subtitles);
}

short int Game::getStatus()
{
	if (Started)
		return plot.Counter;
	else return 10;
}

void ChangeVolume(sf::Music *sound, float X, float Z, float PlayerX, float PlayerZ)
{
	float SideA, SideB, SideC;
	SideA = pow(fabs(PlayerX) - fabs(X), 2);
	SideB = pow(fabs(PlayerZ) - fabs(Z), 2);
	SideC = fabs(sqrt(SideA + SideB));
	if (SideC<100)
	sound->setVolume(100 - SideC);
	else
	sound->setVolume(0);
}