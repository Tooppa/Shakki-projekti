#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include "kayttoliittyma.h"

using namespace std;


Kayttoliittyma* Kayttoliittyma::instance = 0;


Kayttoliittyma* Kayttoliittyma::getInstance()
{
	if (instance == 0)
		instance = new Kayttoliittyma();
	return instance;
}


void Kayttoliittyma::piirraLauta()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	bool lastSquareBlack = true;


	for (int i = 0; i < 8; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
			BACKGROUND_GREEN | BACKGROUND_BLUE);
		wcout << " " << i + 1 << " ";
		for (int j = 0; j < 8; j++)
		{
			if (lastSquareBlack) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);

			if (_asema->_lauta[i][j] == nullptr) {
				wcout << "   ";
			}
			else wcout << " " << _asema->_lauta[i][j]->getUnicode() << " ";

			lastSquareBlack = !lastSquareBlack;
		}
		wcout << "\n";
		lastSquareBlack = !lastSquareBlack;
	}
	char kirjaimet[8] = { 'a','b','c','d','e','f','g','h' };
	wcout << "   ";
	for (int i = 0; i < 8; i++)
	{
		wcout << " " << kirjaimet[i] << " ";
	}
}


/*
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	Siirto siirto;
	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
