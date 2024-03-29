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


	for (short int i = 0; i < 8; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
			BACKGROUND_GREEN | BACKGROUND_BLUE);
		wcout << " " << i + 1 << " ";
		for (short int j = 7; j >= 0; j--)
		{
			if (lastSquareBlack) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
					BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);

			if (_asema->_lauta[j][i] == nullptr) {
				wcout << "   ";
			}
			else wcout << " " << _asema->_lauta[j][i]->getUnicode() << " ";

			lastSquareBlack = !lastSquareBlack;
		}
		wcout << "\n";
		lastSquareBlack = !lastSquareBlack;
	}

	wcout << "   ";
	for (short int i = 7; i >= 0; i--)
	{
		wcout << " " << _kirjaimet[i] << " ";
	}
}


/*
	Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on
	muodollisesti korrekti (ei tarkista aseman laillisuutta)
	Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korrekti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto(Asema asema)
{
	Siirto siirto;
	bool laillinenSiirto = false;

	while (!laillinenSiirto) {


		wstring vastaus;
		wcin >> vastaus;


		if (vastaus.length() == 5) {
			// pitk� linna
			//0 unikodessa numero 48
			if (vastaus[0] == 48)
			{
				siirto = Siirto(false, true);
			}
			else
			{
				//sotilas input
					// 0 unikodessa numero 48, eli 49 miinustetaan vastauksesta ja 
					// saadaan short int muotoinen numero. "Purkkaa" t. menneisyyden Miika.
				short int aloitusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[0]);
				Ruutu aloitusRuutu = Ruutu(aloitusRuudunKirjain, vastaus[1] - 49);

				short int lopetusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[3]);
				Ruutu lopetusRuutu = Ruutu(lopetusRuudunKirjain, vastaus[4] - 49);

				siirto = Siirto(aloitusRuutu, lopetusRuutu);
			}

		}
		else if (vastaus.length() == 6) {
			//joku nappula siirto;
			short int aloitusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[1]);
			Ruutu aloitusRuutu = Ruutu(aloitusRuudunKirjain, vastaus[2] - 49);

			short int lopetusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[4]);
			Ruutu lopetusRuutu = Ruutu(lopetusRuudunKirjain, vastaus[5] - 49);

			siirto = Siirto(aloitusRuutu, lopetusRuutu);
		}
		else if (vastaus.length() == 3)
		{
			siirto = Siirto(true, false);
		}
		else if (vastaus.length() == 7)
		{
			//korotus siirto;
			short int aloitusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[0]);
			Ruutu aloitusRuutu = Ruutu(aloitusRuudunKirjain, vastaus[1] - 49);

			short int lopetusRuudunKirjain = koordinaattiKirjainNumeroksi(vastaus[3]);
			Ruutu lopetusRuutu = Ruutu(lopetusRuudunKirjain, vastaus[4] - 49);

			siirto = Siirto(aloitusRuutu, lopetusRuutu);
			// vastaus[4] - 49 on nolla jos musta on p��tyriviss�

			// defaulttina kuningatar 78 = N, 82 = R, 66 = B, 81 = Q
			if (vastaus[4] - 49 == 0) {
				switch (vastaus[6])
				{
				case 78:
					siirto._miksikorotetaan = Asema::mr;
					break;
				case 82:
					siirto._miksikorotetaan = Asema::mt;
					break;
				case 66:
					siirto._miksikorotetaan = Asema::ml;
					break;
				case 81:
					siirto._miksikorotetaan = Asema::md;
					break;
				default:
					siirto._miksikorotetaan = Asema::md;
					break;
				}
			}
			else
			{
				switch (vastaus[6])
				{
				case 78:
					siirto._miksikorotetaan = Asema::vr;
					break;
				case 82:
					siirto._miksikorotetaan = Asema::vt;
					break;
				case 66:
					siirto._miksikorotetaan = Asema::vl;
					break;
				case 81:
					siirto._miksikorotetaan = Asema::vd;
					break;
				default:
					siirto._miksikorotetaan = Asema::vd;
					break;
				}
			}
		}
		list<Siirto> lista;
		asema.annaLaillisetSiirrot(lista);
		for (const Siirto& indeksiSiirto : lista) {
			if (indeksiSiirto == siirto) {
				laillinenSiirto = true;
				return siirto;
			}
		}
		wcout << "\nLaiton siirto/huono formatointi!\nAnna siirrot muodossa:\nSotilas siirrot: g2-g3 \nMuut siirrot:ra1-a2 \nKorotukset: g2-g1=R (muista isot kirjaimet lopussa)\n";

	}

}

short int Kayttoliittyma::koordinaattiKirjainNumeroksi(char kirjain)
{
	for (short int i = 0; i < 8; i++)
	{
		if (_kirjaimet[i] == kirjain)
		{
			return i;
		}
	}
}


short int Kayttoliittyma::kysyVastustajanVari()
{
	wstring vastaus; vastaus;
	wcout << "Valitse puoli 0=valkoinen/1=musta: ";
	wcin >> vastaus;
	return vastaus[0] - 48;
}
