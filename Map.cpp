#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	MapFile.open("objects\\map.txt");
	TCFile.open("objects\\textures.txt");
	MapEditorRunning = 0;
	TexturesContainerCount = 0;
	TxPlayerXInf.setLikeConstructor(50, 70, 20, sf::Color::Red, sf::Text::Bold);
	TxPlayerX.setLikeConstructor(70, 70, 20, sf::Color::Red, sf::Text::Bold);
	TxPlayerYInf.setLikeConstructor(50, 100, 20, sf::Color::Red, sf::Text::Bold);
	TxPlayerY.setLikeConstructor(70, 100, 20, sf::Color::Red, sf::Text::Bold);
	TxPlayerZInf.setLikeConstructor(50, 130, 20, sf::Color::Red, sf::Text::Bold);
	TxPlayerZ.setLikeConstructor(70, 130, 20, sf::Color::Red, sf::Text::Bold);	
}


Map::~Map()
{
}

void Map::PreparationMap(FormStartSpace::FormStart^ formStart)
{
	string buf;

	std::getline(MapFile, buf, '\n');
	std::getline(MapFile, buf, '\t');
	std::getline(MapFile, buf, '\n');
	BoxCount = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	std::getline(MapFile, buf, '\n');
	CircleCount = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	std::getline(MapFile, buf, '\n');
	ConeCount = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	std::getline(MapFile, buf, '\n');
	CylinderCount = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	std::getline(MapFile, buf, '\n');
	LineCount = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	std::getline(MapFile, buf, '\n');
	SquareCount = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	std::getline(MapFile, buf, '\n');
	TriangleCount = atoi(buf.c_str());
	std::getline(MapFile, buf, '\n');
	std::getline(MapFile, buf, '\n');

	StaticCount = BoxCount + CircleCount + ConeCount + CylinderCount + LineCount + SquareCount + TriangleCount;

	std::getline(TCFile, buf, '\n');
	std::getline(TCFile, buf, '\t');
	std::getline(TCFile, buf, '\n');
	TexturesContainerCount = atoi(buf.c_str());
	texturesContainer = new TexturesContainer[TexturesContainerCount];
	formStart->SetProgressBarValue(0);
	formStart->CoefficientProgressBar = 80 / (float)TexturesContainerCount;
	TCLoader(formStart);
}

void Map::ModelParamLoader(float &Obja,
	float &Objb,
	float &Objc,
	float &ObjX,
	float &ObjY,
	float &ObjZ,
	float &ObjAngX,
	float &ObjAngY,
	float &ObjAngZ,
	string &ObjName,
	string &ObjComment)
{
	string buf;
	std::getline(MapFile, buf, '\t');
	std::getline(MapFile, buf, '\t');
	ObjName = buf;
	std::getline(MapFile, buf, '\t');
	Obja = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	Objb = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	Objc = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	ObjX = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	ObjY = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	ObjZ = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	ObjAngX = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	ObjAngY = atoi(buf.c_str());
	std::getline(MapFile, buf, '\t');
	ObjAngZ = atoi(buf.c_str());
	std::getline(MapFile, buf, '\n');
	ObjComment = buf;
}

void Map::TCLoader( FormStartSpace::FormStart^ formStart)
{
	string TCName, Count;
	for (int i = 1; i < TexturesContainerCount; i++)
	{
		std::getline(TCFile, TCName, '\t');
		std::getline(TCFile, Count, '\n');
		texturesContainer[i].LoadTextures(TCName, atoi(Count.c_str()));
		formStart->SetProgressBarValue(i);

	}
}

void Map::LinkObjects(Box *box,
	Circle *circle,
	Cone *cone,
	Cylinder *cylinder,
	Line *line,
	Square *square,
	Triangle *triangle,
	StaticMapObject **Obj)
{
	int CurStatCount = 0;

	for (int i = 0; i < BoxCount; i++)
	{
		Obj[CurStatCount] = &box[i];
		CurStatCount++;
	}
	for (int i = 0; i < CircleCount; i++)
	{
		Obj[CurStatCount] = &circle[i];
		CurStatCount++;
	}
	for (int i = 0; i < ConeCount; i++)
	{
		Obj[CurStatCount] = &cone[i];
		CurStatCount++;
	}
	for (int i = 0; i < CylinderCount; i++)
	{
		Obj[CurStatCount] = &cylinder[i];
		CurStatCount++;
	}
	for (int i = 0; i < LineCount; i++)
	{
		Obj[CurStatCount] = &line[i];
		CurStatCount++;
	}
	for (int i = 0; i < SquareCount; i++)
	{
		Obj[CurStatCount] = &square[i];
		CurStatCount++;
	}
	for (int i = 0; i < TriangleCount; i++)
	{
		Obj[CurStatCount] = &triangle[i];
		CurStatCount++;
	}
}



void Map::LoadObjectsParamFromFile(StaticMapObject **Obj)
{
	float Obja,
		Objb,
		Objc,
		ObjX,
		ObjY,
		ObjZ,
		ObjAngX,
		ObjAngY,
		ObjAngZ;
	string ObjName,
		ObjComment,
		buf;


	for (int i = 0; i < StaticCount; i++)
	{
		ModelParamLoader(Obja, Objb, Objc, ObjX, ObjY, ObjZ, ObjAngX, ObjAngY, ObjAngZ, ObjName, ObjComment);
		Obj[i]->SetTC(texturesContainer, TexturesContainerCount);
		Obj[i]->Initialize(Obja, Objb, Objc, ObjX, ObjY, ObjZ, ObjAngX, ObjAngY, ObjAngZ, ObjName, ObjComment);
	}
}


void Map::MapEditor(StaticMapObject **Obj,
	FormMapEditor::Form1^ f2,
	FormMenuSpace::FormMenu^ formMenu)
{
	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		if (MapEditorRunning)MapEditorRunning = 0; else MapEditorRunning = 1;
	}


	if ((Keyboard::isKeyPressed(Keyboard::Escape)) && (!formMenu->Runing))
	{
		formMenu->Show();
		formMenu->MyShow();
	}


	if ((MapEditorRunning) && (Keyboard::isKeyPressed(Keyboard::I)) && (!f2->Runing))
	{
		f2->Show();
		f2->MyShow();
	}

	if (Keyboard::isKeyPressed(Keyboard::LControl))
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		ofstream Edit("objects\\Map.txt");
		Edit << "---Declaration---";
		Edit << "\nBox\t";
		Edit << BoxCount;
		Edit << "\nCircle\t";
		Edit << CircleCount;
		Edit << "\nCone\t";
		Edit << ConeCount;
		Edit << "\nCylinder\t";
		Edit << CylinderCount;
		Edit << "\nLine\t";
		Edit << LineCount;
		Edit << "\nSquare\t";
		Edit << SquareCount;
		Edit << "\nTriangle\t";
		Edit << TriangleCount;
		Edit << "\n---Objects---\n";
		Edit << "#\tName\t\ta\tb\tc\tX\tY\tZ\tAngleX\tAngleY\tAngleZ\n";

		for (int i = 0; i < StaticCount; i++)
		{
			Edit << i;
			Edit << "\t";
			Edit << Obj[i]->Name;
			Edit << "\t";
			Edit << Obj[i]->a;
			Edit << "\t";
			Edit << Obj[i]->b;
			Edit << "\t";
			Edit << Obj[i]->c;
			Edit << "\t";
			Edit << Obj[i]->X;
			Edit << "\t";
			Edit << Obj[i]->Y;
			Edit << "\t";
			Edit << Obj[i]->Z;
			Edit << "\t";
			Edit << Obj[i]->AngleX;
			Edit << "\t";
			Edit << Obj[i]->AngleY;
			Edit << "\t";
			Edit << Obj[i]->AngleZ;
			Edit << ";\t";
			Edit << Obj[i]->Comment;
			Edit << "\n";
			formMenu->timer1->Enabled = 1;
		}
	}
}

void Map::DrawTextInfo(sf::RenderWindow &window,
	StaticMapObject **Obj,
	Player &player)
{
	if (MapEditorRunning)
	{
		window.draw(TxPlayerXInf.SetStr("X:"));
		window.draw(TxPlayerX.SetStr(player.X));
		window.draw(TxPlayerYInf.SetStr("Y:"));
		window.draw(TxPlayerY.SetStr(player.Y));
		window.draw(TxPlayerZInf.SetStr("Z:"));
		window.draw(TxPlayerZ.SetStr(player.Z));
	}
}

TexturesContainer* Map::getTC()
{
	return texturesContainer;
}