
void EditMap(StaticMapObject **Obj, 
	int StaticCount, 
	int &BoxCount,
	int &CircleCount,
	int &ConeCount,
	int &CylinderCount,
	int &LineCount,
	int &SquareCount,
	int &TriangleCount, 
	int &EditObjectCount,
	bool &EnabledToEditing, 
	bool &EnabledToChange, 
	FormMapEditor::Form1^ f2, 
	FormMenuSpace::FormMenu^ formMenu)
{
	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		if (EnabledToEditing)EnabledToEditing = 0; else EnabledToEditing = 1;
	}

	
	if ((Keyboard::isKeyPressed(Keyboard::Escape)) && (!formMenu->Runing))
	{
		formMenu->Show();
		formMenu->MyShow();
	}


	if ((EnabledToEditing) && (Keyboard::isKeyPressed(Keyboard::I)) && (!f2->Runing))
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
			Edit <<"\t";
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

void ShowTextInfo(sf::RenderWindow &window, bool &EnabledToEditing, int &EditObjectCount, StaticMapObject **Obj,
	MyText &TxPlayerXInf,
	MyText &TxPlayerX,
	MyText &TxPlayerYInf,
	MyText &TxPlayerY,
	MyText &TxPlayerZInf,
	MyText &TxPlayerZ,
	 Player &player)
{
	if (EnabledToEditing)
	{
		window.draw(TxPlayerXInf.SetStr("X:"));
		window.draw(TxPlayerX.SetStr(player.X));
		window.draw(TxPlayerYInf.SetStr("Y:"));
		window.draw(TxPlayerY.SetStr(player.Y));
		window.draw(TxPlayerZInf.SetStr("Z:"));
		window.draw(TxPlayerZ.SetStr(player.Z));
	}
}