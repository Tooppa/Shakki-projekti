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
	
	wcout << "   ";
	for (int i = 0; i < 8; i++)
	{
		wcout << " " << _kirjaimet[i] << " ";
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

	if (vastaus.length() == 5) {
		// pitkä linna
		//0 unikodessa numero 48
		if (vastaus[0] == 48)
		{
			siirto = Siirto(false, true);
		}
		else 
		{
		//sotilas input
			// 0 unikodessa numero 48, eli 49 miinustetaan vastauksesta ja 
			// saadaan int muotoinen numero. "Purkkaa" t. menneisyyden Miika.
			int aloitusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[0]);
			Ruutu aloitusRuutu = Ruutu(aloitusRuudunKirjain, vastaus[1]-49);

			int lopetusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[3]);
			Ruutu lopetusRuutu = Ruutu(lopetusRuudunKirjain, vastaus[4] - 49);

			siirto = Siirto(aloitusRuutu, lopetusRuutu);
		}
		
	}
	else if (vastaus.length() == 6) {
		//joku nappula siirto;
		int aloitusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[1]);
		Ruutu aloitusRuutu = Ruutu(aloitusRuudunKirjain, vastaus[2] - 49);

		int lopetusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[4]);
		Ruutu lopetusRuutu = Ruutu(lopetusRuudunKirjain, vastaus[5] - 49);

		siirto = Siirto(aloitusRuutu, lopetusRuutu);
	}
	else if (vastaus.length() == 3)
	{
		siirto = Siirto(true, false);
	}
	return siirto;
	
}

int Kayttoliittyma::koordinaattiKirjainNumeroksi(char kirjain) 
{
	for (int i = 0; i < 8; i++)
	{
		if (_kirjaimet[i] == kirjain) 
		{
			return i;
		}
	}
}


int Kayttoliittyma::kysyVastustajanVari()
{
	return 0;
}
