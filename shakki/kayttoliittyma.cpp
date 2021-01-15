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
		for (int j = 0; j < 8; j++)
		{
			if(lastSquareBlack){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED  |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);

			if (_asema->_lauta[i][j] == nullptr) {
				wcout << "   ";
			}
			else wcout <<" " << _asema->_lauta[i][j]->getUnicode()<<" ";

			lastSquareBlack = !lastSquareBlack;
		}
		wcout << "\n";
		lastSquareBlack = !lastSquareBlack;
	}
}


/*
	Aliohjelma tarkistaa että käyttäjän antama syöte siirroksi on 
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti myös nappulan kirjaimen (K/D/L/R/T), tarkistaa että kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
	Siirto siirto;
	wstring vastaus;
	wcin >> vastaus;
	if (vastaus.length() == 4) {
		//sotilas input

	}
	if (vastaus.length() == 5) {
		//joku nappula siirto;

	}
	return siirto;
	
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
