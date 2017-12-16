#include "stdafx.h"
#include "StaticMapObject.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.system.h>
#include <msclr\marshal_cppstd.h>
using namespace System;
using namespace System::IO;


StaticMapObject::StaticMapObject(){
	Z = 0.0f;
	AngleX = 0;
	AngleY = 0;
	AngleZ = 0;
	a = 0;
	b = 0;
	c = 0;
}

StaticMapObject::~StaticMapObject(){}

void StaticMapObject::SetTC(TexturesContainer *texturesContainer, int TexturesContainerCount)
{
	this->texturesContainer = texturesContainer;
	this->TexturesContainerCount = TexturesContainerCount;
}

void StaticMapObject::LinkTextures()
{
	for (int i = 0; i < TexturesContainerCount; i++)
		/*texturesContainer[i].GetName() == this->Name
		?
		textures = texturesContainer[i].GetTexture() : 0;
		*/
	if (texturesContainer[i].GetName() == this->Name)
	{
		Textures = texturesContainer[i].GetTexture();
		break;
	}
	else
	{
		Textures = texturesContainer[1].GetTexture();
		}
}

void StaticMapObject::SetTexture(int Count, string Name, int FileCont)
{
	Textures[Count] = Draw::LoadTexture("Objects\\" + Name + "\\jpeg\\" + msclr::interop::marshal_as<std::string>(FileCont.ToString()) + ".jpg");
}
