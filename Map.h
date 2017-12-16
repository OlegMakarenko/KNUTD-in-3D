#pragma once
#include <fstream>
#include <string>
#include "Box.h"
#include "Square.h"
#include "ExternalObject.h"
#include "Triangle.h"
#include "Circle.h"
#include "Cylinder.h"
#include "Line.h"
#include "Cone.h"
#include "StaticMapObject.h"
#include "FormStart.h"
#include "Form1.h"
#include "FormMenu.h"
#include "MyText.h"
#include "Player.h"
#include "TexturesContainer.h"
using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;

class Map
{
public:
	Map();
	~Map();
	int StaticCount;
	int BoxCount;
	int CircleCount;
	int ConeCount;
	int CylinderCount;
	int LineCount;
	int SquareCount;
	int TriangleCount;
	int TexturesContainerCount;

	bool MapEditorRunning;

	void PreparationMap(FormStartSpace::FormStart^ formStart);
	void LinkObjects(Box *box, 
		Circle *circle, 
		Cone *cone, 
		Cylinder *cylinder,
		Line *line,
		Square *square,
		Triangle *triangle,
		StaticMapObject **Obj);
	void Map::LoadObjectsParamFromFile(StaticMapObject **Obj);
	void Map::MapEditor(StaticMapObject **Obj,
		FormMapEditor::Form1^ f2,
		FormMenuSpace::FormMenu^ formMenu);
	void Map::DrawTextInfo(sf::RenderWindow &window,
		StaticMapObject **Obj,
		Player &player);
	TexturesContainer* getTC();
	TexturesContainer *texturesContainer;
	
private:
	void ModelParamLoader(float &Obja,
		float &Objb,
		float &Objc,
		float &ObjX,
		float &ObjY,
		float &ObjZ,
		float &ObjAngX,
		float &ObjAngY,
		float &ObjAngZ,
		string &ObjName,
		string &ObjComment);

	void TCLoader(FormStartSpace::FormStart^ formStart);

	int EditObjectCount;
	MyText TxPlayerXInf;
	MyText TxPlayerX;
	MyText TxPlayerYInf;
	MyText TxPlayerY;
	MyText TxPlayerZInf;
	MyText TxPlayerZ;
	ifstream MapFile;
	ifstream TCFile;

};

