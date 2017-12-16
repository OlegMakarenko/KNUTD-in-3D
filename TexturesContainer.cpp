#include "stdafx.h"
#include "TexturesContainer.h"
#include <string.h>
#include "Draw.h"
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <windows.h> 
using namespace System;
using namespace std;


TexturesContainer::TexturesContainer()
{
	Name = "";
	Count=0;
}


TexturesContainer::~TexturesContainer()
{
}

void TexturesContainer::LoadTextures(string Name, int Count)
{
	this->Name = Name;
	this->Count = Count;
	Textures = new GLuint[Count];
	for (int i = 0; i < Count; i++)
		Textures[i] = Draw::LoadTexture("Objects\\" + Name + "\\jpeg\\" + msclr::interop::marshal_as<std::string>(i.ToString()) + ".jpg");
}

string TexturesContainer::GetName()
{
	return Name;
}

GLuint *TexturesContainer::GetTexture()
{
	return Textures;
}