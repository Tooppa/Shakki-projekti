﻿#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"
#include "kayttoliittyma.h"
#include "zobrist.h"
#include "math.h"

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK, 0);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD, 9);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT, 5);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL, 3.25);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR, 3);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS, 1);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK, 0);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD, 9);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT, 5);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML, 3.25);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR, 3);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS, 1);


Asema::Asema()
{
	_siirtovuoro = 0;
	_onkoValkeaKuningasLiikkunut = false;;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;

	for (short int i = 0; i < 8; i++)
		for (short int j = 0; j < 8; j++)
			_lauta[i][j] = nullptr;
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa

	// mustat sotilaat
	for (short int i = 0; i < 8; i++)
		_lauta[i][6] = ms;
	//muut mustat nappulat
	_lauta[7][7] = mt;
	_lauta[6][7] = mr;
	_lauta[5][7] = ml;
	_lauta[4][7] = mk;
	_lauta[3][7] = md;
	_lauta[2][7] = ml;
	_lauta[1][7] = mr;
	_lauta[0][7] = mt;

	// valkoiset sotilaat
	for (short int i = 0; i < 8; i++)
		_lauta[i][1] = vs;
	//muut valkoiset nappulat
	_lauta[7][0] = vt;
	_lauta[6][0] = vr;
	_lauta[5][0] = vl;
	_lauta[4][0] = vk;
	_lauta[3][0] = vd;
	_lauta[2][0] = vl;
	_lauta[1][0] = vr;
	_lauta[0][0] = vt;


	// Asetetaan alkuaseman mukaisesti nappulat ruuduille

}

//Asema::~Asema()
//{
//		delete[] _lauta;
//}


void Asema::paivitaAsema(Siirto* siirto)
{
	// Kaksoisaskel-lippu on oletusarvoisesti pois päältä.
	// Asetetaan myöhemmin, jos tarvii.

	// Alustus



	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna())
	{
		if (getSiirtovuoro() == 0 && !getOnkoValkeaKTliikkunut() && !getOnkoValkeaKuningasLiikkunut()) {
			_lauta[4][0] = nullptr;
			_lauta[7][0] = nullptr;
			_lauta[5][0] = vt;
			_lauta[6][0] = vk;
			_onkoValkeaKTliikkunut = true;
			_onkoValkeaKuningasLiikkunut = true;
		}
		if (getSiirtovuoro() == 1 && !getOnkoMustaKTliikkunut() && !getOnkoMustaKuningasLiikkunut()) {
			_lauta[4][7] = nullptr;
			_lauta[7][7] = nullptr;
			_lauta[5][7] = mt;
			_lauta[6][7] = mk;
			_onkoMustaKTliikkunut = true;
			_onkoMustaKuningasLiikkunut = true;
		}
	}
	// onko pitkä linna
	else if (siirto->onkoPitkalinna())
	{
		if (getSiirtovuoro() == 0 && !getOnkoValkeaDTliikkunut() && !getOnkoValkeaKuningasLiikkunut()) {
			_lauta[4][0] = nullptr;
			_lauta[0][0] = nullptr;
			_lauta[3][0] = vt;
			_lauta[2][0] = vk;
			_onkoValkeaDTliikkunut = true;
			_onkoValkeaKuningasLiikkunut = true;
		}
		if (getSiirtovuoro() == 1 && !getOnkoMustaDTliikkunut() && !getOnkoMustaKuningasLiikkunut()) {
			_lauta[4][7] = nullptr;
			_lauta[0][7] = nullptr;
			_lauta[3][7] = mt;
			_lauta[2][7] = mk;
			_onkoMustaDTliikkunut = true;
			_onkoMustaKuningasLiikkunut = true;
		}
	}
	// Kaikki muut siirrot
	else
	{
		short int alkuRivi = siirto->getAlkuruutu().getRivi();
		short int alkuSarake = siirto->getAlkuruutu().getSarake();

		short int loppuRivi = siirto->getLoppuruutu().getRivi();
		short int loppuSarake = siirto->getLoppuruutu().getSarake();


		//Ottaa siirron alkuruudussa olleen nappulan talteen 


		Nappula* nappula = _lauta[alkuSarake][alkuRivi];

		//Alustus
		short int nappulanKoodi = nappula->getKoodi();

		//oheistalyönti
		if (nappulanKoodi == MS || nappulanKoodi == VS)
			if (abs(alkuRivi - loppuRivi) == 2)
				kaksoisaskelSarakkeella = alkuSarake;
			else if (kaksoisaskelSarakkeella >= 0) {
				if (nappulanKoodi == VS) {
					if (_lauta[kaksoisaskelSarakkeella - 1][4] && kaksoisaskelSarakkeella == alkuSarake + 1 && loppuRivi == 5) {
						_lauta[loppuSarake][loppuRivi - 1] = nullptr;
					}
					else if (_lauta[kaksoisaskelSarakkeella + 1][4] && kaksoisaskelSarakkeella == alkuSarake - 1 && loppuRivi == 5) {
						_lauta[loppuSarake][loppuRivi - 1] = nullptr;
					}
				}
				else if (nappulanKoodi == MS) {
					if (_lauta[kaksoisaskelSarakkeella - 1][3] && kaksoisaskelSarakkeella == alkuSarake + 1 && loppuRivi == 2) {
						_lauta[loppuSarake][loppuRivi + 1] = nullptr;
					}
					else if (_lauta[kaksoisaskelSarakkeella + 1][3] && kaksoisaskelSarakkeella == alkuSarake - 1 && loppuRivi == 2) {
						_lauta[loppuSarake][loppuRivi + 1] = nullptr;
					}
				}
				kaksoisaskelSarakkeella = -1;
			}

		_lauta[alkuSarake][alkuRivi] = nullptr;
		//Laittaa talteen otettu nappula uuteen ruutuun
		_lauta[loppuSarake][loppuRivi] = nappula;






		//// Katsotaan jos nappula on sotilas ja rivi on päätyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittymän laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		if ((nappulanKoodi == MS || nappulanKoodi == VS) && (loppuRivi == 0 || loppuRivi == 7))
		{
			_lauta[alkuSarake][alkuSarake] = nullptr;
			_lauta[loppuSarake][loppuRivi] = siirto->_miksikorotetaan;
		}

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta lähtenyt nappula

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille väreille)
		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille väreille ja molemmille torneille)

		switch (nappulanKoodi)
		{
		case VT:
			if (alkuRivi == 0 && alkuSarake == 7) _onkoValkeaKTliikkunut = true;
			else if (nappulanKoodi == 0 && alkuRivi == 0 && alkuSarake == 0) _onkoValkeaDTliikkunut = true;
			break;
		case VK:
			if (!_onkoValkeaKuningasLiikkunut)_onkoValkeaKuningasLiikkunut = true;
			break;
		case MT:
			if (alkuRivi == 7 && alkuSarake == 7) _onkoMustaKTliikkunut = true;
			else if (alkuRivi == 7 && alkuSarake == 0) _onkoMustaDTliikkunut = true;
			break;
		case MK:
			if (!_onkoMustaKuningasLiikkunut)_onkoMustaKuningasLiikkunut = true;
			break;
		}
		//päivitetään _siirtovuoro

	}
	if (_siirtovuoro == 1) _siirtovuoro = 0;
	else _siirtovuoro = 1;
}



short int Asema::getSiirtovuoro()
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(short int vuoro)
{
	_siirtovuoro = vuoro;
}


bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	return _onkoValkeaKuningasLiikkunut;
}


bool Asema::getOnkoMustaKuningasLiikkunut()
{
	return _onkoMustaKuningasLiikkunut;
}


bool Asema::getOnkoValkeaDTliikkunut()
{
	return _onkoValkeaDTliikkunut;
}


bool Asema::getOnkoValkeaKTliikkunut()
{
	return _onkoValkeaKTliikkunut;
}


bool Asema::getOnkoMustaDTliikkunut()
{
	return _onkoMustaDTliikkunut;
}


bool Asema::getOnkoMustaKTliikkunut()
{
	return _onkoMustaKTliikkunut;
}


/* 1. Laske nappuloiden arvo
Daami = 9
Torni = 5
Lähetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyvä että kunigas g1 tai b1/c1
Loppupelissä vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla estämässä vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitkiä linjoja daami, torni ja lähetti
*/
double Asema::evaluoi()
{
	double evaluaatio = 0;
	//kertoimet asetettu sen takia että niiden avulla asioiden painoarvoa voidaan säätää helposti yhdestä paikasta
	double k = 1000, d = 120, t = 90, l = 32, r = 30, s = 10;

	Ruutu valkoinenK;
	Ruutu mustaK;

	//1. Nappuloiden arvo
	double arvostusTaulukkoMS[8][8] =
	{ {0, 0, 0, 0, 0, 0, 0, 0},
	{4, 4, 4, 4, 4, 4, 4, 4},
	{0, 0, 0.0, 2, 2, 0, 0, 0},
	{0, 0, 0.0, 7, 4, 0, 0, 0},
	{0, 2, 3, 5, 5, 3, 3, 0},
	{1, 3, 3, 3, 3, 3, 3, 1},
	{1, 1, 1, -2, -2, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0} };

	double arvostusTaulukkoVS[8][8] =
	{ {0, 0, 0, 0, 0, 0, 0, 0},
	{0.5, 1, 1, -2, -2, 1, 1, 0.5},
	{1, 2, 3, 3, 3, 3, 4, 1},
	{0, 2, 0, 7, 4, 0, 4, 0},
	{0, 0, 0, 4, 4, 0, 0, 0},
	{0, 0, 0, 3, 3, 0, 0, 0},
	{4, 4, 4, 4, 4, 4, 4, 4},
	{0, 0, 0, 0, 0, 0, 0, 0} };

	double arvostusTaulukkoMR[8][8] =
	{ {-3, -2, -1, 0, 0, -1, -2, -3},
	{0, 1, 2, 2, 2, 2, 1, 0},
	{0, 2, 3, 3, 3, 3, 2, 0},
	{0, 2, 3, 4, 4, 3, 2, 0},
	{0, 2, 3, 4, 4, 3, 2, 0},
	{0, 2, 2, 3, 3, 2, 2, 0},
	{0, 1, 2, 2, 2, 2, 1, 0},
	{-3, -2, -1, 0, 0, -1, -2, -3} };

	double arvostusTaulukkoVR[8][8] =
	{ {-3, -2, -1, 0, 0, -1, 2, -3},
	{0, 0, 0, 0, 0, 2, 1, 0},
	{0, 2, 2, 3, 3, 2, 2, 0},
	{0, 2, 3, 4, 4, 3, 2, 0},
	{0, 2, 3, 4, 4, 3, 2, 0},
	{0, 2, 3, 3, 3, 3, 2, 0},
	{0, 1, 2, 2, 2, 0.2, 0.1, 0},
	{-3, -2, -1, 0, 0, -1, -2, -3} };

	double arvostusTaulukkoMT[8][8] =
	{ {1, 2, 2, 2, 2, 2, 2, 1},
	{3, 4, 4, 4, 4, 4, 4, 3},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 3, 4, 4, 3, 0, -1} };

	double arvostusTaulukkoVT[8][8] =
	{ {-1, 0, 1, 2, 2, 1, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, 0, 0, 0, -0},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{3, 4, 4, 4, 4, 4, 4, 3},
	{1, 2, 2, 2, 2, 2, 2, 1} };

	double arvostusTaulukkoML[8][8] =
	{ {-1, 1, -1, 1, 1, -1, 1, -1},
	{1, 2, 2, 2, 2, 2, 2, 1},
	{1, 2, 0, 3, 3, 0, 2, 1},
	{1, 2, 0, 3, 3, 0, 2, 1},
	{1, 2, 5, 3, 3, 5, 2, 1},
	{1, 0, 3, 3, 3, 3, 0, 1},
	{1, 0, 2, 2, 2, 2, 0, 1},
	{2, 0, 0, 0, 0, 0, 0, 2} };

	double arvostusTaulukkoVL[8][8] =
	{ {2, 0, 0, 0, 0, 0, 0, 2 },
	{ 1, 0, 2, 2, 2, 2, 0, 1 },
	{ 1, 0, 3, 3, 3, 3, 0, 1 },
	{ 1, 1, 5, 3, 3, 5, 2, 1 },
	{ 1, 2, 0, 3, 3, 3, 2, 1},
	{ 1, 2, 0, 3, 3, 0, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 1 },
	{ -1, 1, -1, 1, 1, -1, 1, -1} };

	double arvostusTaulukkoMD[8][8] =
	{ {-1, 1, 1, 2, 2, 1, 1, -1},
		{1, 3, 3, 3, 3, 3, 3, 1},
		{1, 3, 4, 4, 4, 4, 3, 1},
		{1, 3, 4, 4, 4, 4, 3, 1},
		{3, 3, 4, 4, 4, 4, 3, 2},
		{1, 4, 4, 4, 4, 4, 3, 1},
		{1, 2, 4, 4, 4, 3, 3, 1},
		{-2, 1, 1, 2, 2, 1, 1, -2} };

	double arvostusTaulukkoVD[8][8] =
	{ {-2, 1, 1, 2, 2, 1, 1, -2},
		{1, 2, 4, 4, 4, 3, 3, 1},
		{1, 4, 4, 4, 4, 4, 3, 1},
		{2, 3, 4, 4, 4, 4, 3, 3},
		{1, 3, 4, 4, 4, 4, 4, 2},
		{1, 3, 4, 4, 4, 4, 3, 2},
		{1, 3, 3, 3, 3, 3, 3, 1},
		{-1, 1, 1, 2, 2, 1, 1, -1} };

	double arvostusTaulukkoVK[8][8] =
	{ {4, 5, 3, 0, 0, 0, 5, 4},
		{0, 0, -3, -2, -2, -1, 0, 2},
		{0, -1, -1, -2, -2, -1, -1, 0},
		{0, 0, 0, -2, -2, 0, 0, 0},
		{0, 0, 0, -2, -2, 0, 0, 0},
		{0, -1, -1, -2, -2, -1, -1, 0},
		{0, 0, -1, -2, -2, -1, 2},
		{-1, -1, -1, -2, -2, -1, -1, -1} };

	double arvostusTaulukkoMK[8][8] =
	{ { -1, -1, -1, -2, -2, -1, -1, -1 },
		{0, 0, -1, -2, -2, -1, 0, 2},
		{0, -1, -1, -2, -2, -1, -1, 0},
		{0, 0, 0, -2, -2, 0, 0, 0},
		{0, 0, 0, -2, -2, 0, 0, 0},
		{0, -1, -1, -2, -2, -1, -1, 0},
		{0, 0, -1, -2, -3, -1, 2},
		{4, 5, 3, 0, 0, 0, 5, 4} };

	double arvostusTaulukkoKLoppupeli[8][8] =
	{ {5, 4, 3, 0, 0, 3, 4, 5},
		{4, 3, 1, 0, 0, 1, 3, 4},
		{3, 1, 0, 0, 0, 0, 1, 3},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{3, 1, 0, 0, 0, 0, 1, 3},
		{4, 3, 1, 0, 0, 1, 3, 4},
		{5, 4, 3, 0, 0, 3, 4, 5} };

	Ruutu kuninkaanRuutu;
	Ruutu VKuninkaanRuutu;
	Ruutu MKuninkaanRuutu;
	list<Siirto> lista;
	annaLaillisetSiirrot(lista);

	short int vihu = _siirtovuoro == 0 ? 1 : 0;
	for (short int i = 0; i < 8; i++)
		for (short int j = 0; j < 8; j++)
			if (_lauta[i][j] && _lauta[i][j]->getVari() == vihu && (_lauta[i][j]->getKoodi() == VK || _lauta[i][j]->getKoodi() == MK))
				kuninkaanRuutu = Ruutu(i, j);
	if (this->onkoRuutuUhattu(kuninkaanRuutu, _siirtovuoro && lista.size() == 0))
		evaluaatio = _siirtovuoro == 0 ? DBL_MAX : -DBL_MAX;
	if (this->onkoRuutuUhattu(kuninkaanRuutu, _siirtovuoro && lista.size() != 0))
		evaluaatio = _siirtovuoro == 0 ? 1000 : -1000;


	double valkoisiaNappuloita = 0;
	double mustiaNappuloita = 0;
	for (short int i = 0; i < 8; i++)
		for (short int j = 0; j < 8; j++)
			if (_lauta[i][j])
				if (_lauta[i][j]->getVari() == 0)
					valkoisiaNappuloita++;
				else mustiaNappuloita++;

	double mustaKerroin = mustiaNappuloita / 5;
	double valkoinenKerroin = valkoisiaNappuloita / 5;



	//1. Nappuloiden arvo
	for (short int i = 0; i < 8; i++)
		for (short int j = 0; j < 8; j++)
		{
			if (_lauta[i][j])
			{
				if (_lauta[i][j]->getVari() == 0)
				{
					switch (_lauta[i][j]->getKoodi())
					{
					case VS:
						evaluaatio += s;
						evaluaatio += arvostusTaulukkoVS[i][j] * valkoinenKerroin;
						break;
					case VT:
						evaluaatio += t;
						evaluaatio += arvostusTaulukkoVT[i][j] * valkoinenKerroin;
						break;
					case VR:
						evaluaatio += r;
						evaluaatio += arvostusTaulukkoVR[i][j] * valkoinenKerroin;
						break;
					case VL:
						evaluaatio += l;
						evaluaatio += arvostusTaulukkoVL[i][j] * valkoinenKerroin;
						break;
					case VD:
						evaluaatio += d;
						evaluaatio += arvostusTaulukkoVD[i][j] * valkoinenKerroin;
						break;
					case VK:
						evaluaatio += k;
						evaluaatio += arvostusTaulukkoVK[i][j] * valkoinenKerroin;
						evaluaatio -= arvostusTaulukkoKLoppupeli[i][j] * (3 / valkoisiaNappuloita);
						VKuninkaanRuutu = Ruutu(i, j);
						break;
					default:
						break;
					}
				}
				else
				{
					switch (_lauta[i][j]->getKoodi())
					{
					case MS:
						evaluaatio -= s;
						evaluaatio -= arvostusTaulukkoMS[i][j] * mustaKerroin;
						break;
					case MT:
						evaluaatio -= t;
						evaluaatio -= arvostusTaulukkoMT[i][j] * mustaKerroin;
						break;
					case MR:
						evaluaatio -= r;
						evaluaatio -= arvostusTaulukkoMR[i][j] * mustaKerroin;
						break;
					case ML:
						evaluaatio -= l;
						evaluaatio -= arvostusTaulukkoML[i][j] * mustaKerroin;
						break;
					case MD:
						evaluaatio -= d;
						evaluaatio -= arvostusTaulukkoMD[i][j] * mustaKerroin;
						break;
					case MK:
						evaluaatio -= k;
						evaluaatio -= arvostusTaulukkoMK[i][j] * mustaKerroin;
						evaluaatio += arvostusTaulukkoKLoppupeli[i][j] * (3 / mustiaNappuloita);
						MKuninkaanRuutu = Ruutu(i, j);
						break;
					default:
						break;
					}
				}

			}

		}
	evaluaatio += sqrt(pow(((double)VKuninkaanRuutu.getRivi() - (double)MKuninkaanRuutu.getRivi()), 2) + pow(((double)VKuninkaanRuutu.getSarake() - (double)MKuninkaanRuutu.getSarake()), 2))
		* 4 * (valkoisiaNappuloita - mustiaNappuloita);

	short int vkSarake = valkoinenK.getSarake();
	short int vkRivi = valkoinenK.getRivi();

	short int mkSarake = mustaK.getSarake();
	short int mkRivi = mustaK.getRivi();

	// 2. kuninkaan turvallisuus
	// evaluaatioon lisätään 0.25 jos kuningas on tornittanut ja/tai liikkunut pois keskeltä
	// lisäksi mikäli kuninkaan edessä ja ainakin toisessa viistoruudussa on oma nappula lisätään 0.75
	// numeroita varmasti pitää viilata



	/*
	* float tyhjaArvostusTaulu[8][8] =
	{ {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} };

	*/
	// 3. Arvosta nappuloiden sijainteja


	// 4. Arvosta linjoja
	return evaluaatio;
}


// laskee nappuloiden arvot ja ottaa kuninkaat talteen
double Asema::laskeNappuloidenArvo(short int i)
{
	return 0;
}


bool Asema::onkoAvausTaiKeskipeli(short int vari)
{
	return 0;
	// Jos upseereita 3 tai vähemmän on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami jäljellä

	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1


}


double Asema::nappuloitaKeskella(short int vari)
{
	return 0;

	//sotilaat ydinkeskustassa + 0.25/napa
	//ratsut ydinkeskustassa + 0.25/napa
	//sotilaat laitakeskustassa + 0.11/napa
	//ratsut laitakeskustassa + 0.11/napa

	//valkeille ydinkeskusta



	//valkeille laitakeskusta



	//mustille ydinkeskusta

	//mustille laitakeskusta

}


double Asema::linjat(short int vari)
{
	return 0;

	//valkoiset

	//mustat

}

uint64_t Asema::GetHash()
{
	ZobristHash hashGenerator;

	bool castlingData[4];
	castlingData[0] = getSiirtovuoro() == 0 && !getOnkoValkeaKTliikkunut() && !getOnkoValkeaKuningasLiikkunut();
	castlingData[1] = getSiirtovuoro() == 0 && !getOnkoValkeaDTliikkunut() && !getOnkoValkeaKuningasLiikkunut();
	castlingData[2] = getSiirtovuoro() == 1 && !getOnkoMustaKTliikkunut() && !getOnkoMustaKuningasLiikkunut();
	castlingData[3] = getSiirtovuoro() == 1 && !getOnkoMustaDTliikkunut() && !getOnkoMustaKuningasLiikkunut();

	return hashGenerator.GetHash(_lauta, castlingData);
}

MinMaxPaluu Asema::alphaBeta(short int syvyys, double alpha, double beta)
{
	Kayttoliittyma* k = Kayttoliittyma::getInstance();
	k->_counter++;
	chrono::steady_clock::time_point start = k->_aika; // tallennetaan startti aika käyttöliittymästä
	MinMaxPaluu paluu;

	bool kesken = false;

	std::list<Siirto> lista;

	Ruutu kuninkaanRuutu;
	// Kantatapaukset 1 ja 2 : matti tai patti?
	this->annaLaillisetSiirrot(lista);

	// mikäli jää aikaa nii hyvä tapa optimoida on järjestää nopeesti lista
	this->jarjestaLista(lista);

	if (lista.size() == 0)
	{
		paluu._evaluointiArvo = 0;
		short int vihu = _siirtovuoro == 0 ? 1 : 0;
		for (short int i = 0; i < 8; i++)
			for (short int j = 0; j < 8; j++)
				if (_lauta[i][j] && _lauta[i][j]->getVari() == _siirtovuoro && (_lauta[i][j]->getKoodi() == VK || _lauta[i][j]->getKoodi() == MK)) {
					kuninkaanRuutu = Ruutu(i, j);
					if (this->onkoRuutuUhattu(kuninkaanRuutu, vihu)) {
						paluu._evaluointiArvo = _siirtovuoro == 0 ? -DBL_MAX : DBL_MAX;
						paluu._matissa = true;
					}
				}
		return paluu;
	}
	if (paluu._parasSiirto == Siirto())
		paluu._parasSiirto = lista.front();
	// Kantatapaus 3: katkaisusyvyys
	if (syvyys == 0)
	{
		paluu._evaluointiArvo = evaluoi();
		if (paluu._evaluointiArvo == DBL_MAX || paluu._evaluointiArvo == -DBL_MAX)
			paluu._matissa = true;
		return paluu;
	}
	if (_siirtovuoro == 0)
	{
		paluu._evaluointiArvo = -DBL_MAX;
		for each (Siirto siirto in lista)
		{
			if (chrono::steady_clock::now() - start >= std::chrono::seconds(k->_maxAika)) { kesken = true; break; }  // lähdetään pois mikäli aika on loppu
			Asema uusiAsema = *this;
			uusiAsema.paivitaAsema(&siirto);

			// kommentteihin tämä iffi ja alempaa muutama rivi jos haluaa taulukot pois päältä
			uint64_t laudanHash = uusiAsema.GetHash();
			if (k->_transpositiot.Exist(laudanHash))
			{
				HashData item = k->_transpositiot.Get(laudanHash);
				if (item._syvyys == syvyys - 1 && item._vari == uusiAsema.getSiirtovuoro())
					paluu = item._parasSiirto;
			}

			MinMaxPaluu tempPaluu = uusiAsema.alphaBeta(syvyys - 1, alpha, beta);

			if (tempPaluu._evaluointiArvo > paluu._evaluointiArvo || tempPaluu._matissa == true)
			{
				paluu = tempPaluu;
				paluu._parasSiirto = siirto;
			}
			alpha = std::max(alpha, paluu._evaluointiArvo);
			if (beta <= alpha)
				break;
		}
	}
	else
	{
		paluu._evaluointiArvo = DBL_MAX;
		for each (Siirto siirto in lista)
		{
			if (chrono::steady_clock::now() - start >= std::chrono::seconds(k->_maxAika)) { kesken = true; break; }  // lähdetään pois mikäli aika on loppu
			Asema uusiAsema = *this;
			uusiAsema.paivitaAsema(&siirto);

			// kommentteihin tämä iffi ja alempaa muutama rivi jos haluaa taulukot pois päältä
			uint64_t laudanHash = uusiAsema.GetHash();// hash tekee nyt hashin uudesta asemasta
			if (k->_transpositiot.Exist(laudanHash))
			{
				HashData item = k->_transpositiot.Get(laudanHash);
				if (item._syvyys == syvyys - 1 && item._vari == uusiAsema.getSiirtovuoro())	// mikäli hashin tuloksen väri ja syvyys on täsmälleen sama nii
					paluu = item._parasSiirto;												// asetetaan paluu arvon tilalle se paras siirto. alpha beta cut of tulee nopeemmin
			}
			MinMaxPaluu tempPaluu = uusiAsema.alphaBeta(syvyys - 1, alpha, beta);


			if (tempPaluu._evaluointiArvo < paluu._evaluointiArvo || tempPaluu._matissa == true)
			{
				paluu = tempPaluu;
				paluu._parasSiirto = siirto;
			}
			beta = std::min(beta, paluu._evaluointiArvo);
			if (beta <= alpha)
				break;

		}
	}
	if (!kesken) {
		// kommentteihin nämä kaksi riviä taulukko systeemin poistamiseksi
		HashData item(syvyys, paluu, getSiirtovuoro());
		uint64_t laudanHash = GetHash();
		k->_transpositiot.Add(laudanHash, item);// tallennetaan tietokantaan
	}
	return paluu;
}

// jotai optimointia
void Asema::jarjestaLista(std::list<Siirto>& lista)
{
	std::list<Siirto> siirrettava;
	Nappula* alku;
	Nappula* loppu;
	for each (Siirto siirto in lista)
	{
		// jos tornitus. yleensä ihan hyvä siirto
		if (siirto.onkoLyhytLinna() || siirto.onkoPitkalinna())
			siirrettava.push_back(siirto);
		else
		{
			alku = _lauta[siirto.getAlkuruutu().getSarake()][siirto.getAlkuruutu().getRivi()];
			loppu = _lauta[siirto.getLoppuruutu().getSarake()][siirto.getLoppuruutu().getRivi()];

			//jos syödään
			if (loppu && loppu->getVari() != _siirtovuoro)
				if (alku->getArvo() <= loppu->getArvo())
					siirrettava.push_back(siirto);
		}
	}
	if (siirrettava.size() != 0)
		for each (Siirto siirto in siirrettava)
		{
			lista.remove(siirto);
			lista.push_front(siirto);
		}
}

bool Asema::onkoRuutuUhattu(Ruutu ruutu, short int vastustajanVari)
{
	std::list<Siirto> siirrot;

	for (short int i = 0; i < 8; i++)
		for (short int j = 0; j < 8; j++)
			if (_lauta[i][j] && _lauta[i][j]->getVari() == vastustajanVari)
				_lauta[i][j]->annaSiirrot(siirrot, &Ruutu(i, j), this, vastustajanVari);

	for each (Siirto siirto in siirrot)
		if (siirto.getLoppuruutu() == ruutu)
			return true;
	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, short int vari)
{

}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	Ruutu kuninkaanRuutu;
	Asema uusiAsema;
	std::list<Siirto> poistettava;

	for (short int i = 0; i < 8; i++)
		for (short int j = 0; j < 8; j++)
		{
			if (_lauta[i][j] && _lauta[i][j]->getVari() == _siirtovuoro)
			{
				_lauta[i][j]->annaSiirrot(lista, &Ruutu(i, j), this, _siirtovuoro);
			}
		}

	for each (Siirto siirto in lista)
	{
		uusiAsema = *this;
		uusiAsema.paivitaAsema(&siirto);

		// tämmönen ehkä toimii kuninkaanRuutu.getSarake() > 0

		for (short int i = 0; i < 8; i++)
			for (short int j = 0; j < 8; j++)
				if (uusiAsema._lauta[i][j] && ((uusiAsema._siirtovuoro == 1 && uusiAsema._lauta[i][j]->getKoodi() == VK) || (uusiAsema._siirtovuoro == 0 && uusiAsema._lauta[i][j]->getKoodi() == MK)))
					kuninkaanRuutu = Ruutu(i, j);

		//mikäli siirto uhkaa kuningasta laitetaan se poistettavaksi
		if (uusiAsema.onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro)) poistettava.push_back(siirto);
	}
	// käy läpi loopissa ja poistaa kaikki pää listasta 
	if (poistettava.size() != 0)
		for each (Siirto siirto in poistettava)
			lista.remove(siirto);


	//Tornitukset
	annaLinnoitusSiirrot(kuninkaanRuutu, lista);
	annaOheistaLyonnit(lista);
}


void Asema::annaLinnoitusSiirrot(const Ruutu& kuninkaanRuutu, std::list<Siirto>& lista)
{
	if (_siirtovuoro == 0 && (!getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaDTliikkunut())) {
		bool laiton = false;
		Ruutu ruutu1 = Ruutu(2, 0);
		Ruutu ruutu2 = Ruutu(3, 0);
		if (_lauta[1][0] || _lauta[2][0] || _lauta[3][0]) laiton = true;
		else if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu1, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu2, !_siirtovuoro)) laiton = true;
		if (!laiton) lista.push_back(Siirto(false, true));
	}
	if (_siirtovuoro == 1 && (!getOnkoMustaKuningasLiikkunut() && !getOnkoMustaDTliikkunut())) {
		bool laiton = false;
		Ruutu ruutu1 = Ruutu(2, 7);
		Ruutu ruutu2 = Ruutu(3, 7);
		if (_lauta[1][7] || _lauta[2][7] || _lauta[3][7]) laiton = true;
		else if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu1, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu2, !_siirtovuoro)) laiton = true;
		if (!laiton) lista.push_back(Siirto(false, true));
	}
	if (_siirtovuoro == 0 && (!getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaKTliikkunut())) {
		bool laiton = false;
		Ruutu ruutu1 = Ruutu(5, 0);
		if (_lauta[5][0] || _lauta[6][0]) laiton = true;
		else if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu1, !_siirtovuoro)) laiton = true;
		if (!laiton) lista.push_back(Siirto(true, false));

	}
	if (_siirtovuoro == 1 && (!getOnkoMustaKuningasLiikkunut() && !getOnkoMustaKTliikkunut())) {
		bool laiton = false;
		Ruutu ruutu1 = Ruutu(5, 7);
		if (_lauta[5][7] || _lauta[6][7]) laiton = true;
		else if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu1, !_siirtovuoro)) laiton = true;
		if (!laiton) lista.push_back(Siirto(true, false));
	}
}
void Asema::annaOheistaLyonnit(std::list<Siirto>& lista) {
	if (_siirtovuoro == 0) {
		if (kaksoisaskelSarakkeella >= 0) {
			if (0 < kaksoisaskelSarakkeella && kaksoisaskelSarakkeella < 7) {
				if (_lauta[kaksoisaskelSarakkeella][4] && _lauta[kaksoisaskelSarakkeella][4]->getKoodi() == MS) {
					if (_lauta[kaksoisaskelSarakkeella - 1][4] && _lauta[kaksoisaskelSarakkeella - 1][4]->getKoodi() == VS) {
						lista.push_back(Siirto(Ruutu(kaksoisaskelSarakkeella - 1, 4), Ruutu(kaksoisaskelSarakkeella, 5)));
					}
					if (_lauta[kaksoisaskelSarakkeella + 1][4] && _lauta[kaksoisaskelSarakkeella + 1][4]->getKoodi() == VS) {
						lista.push_back(Siirto(Ruutu(kaksoisaskelSarakkeella + 1, 4), Ruutu(kaksoisaskelSarakkeella, 5)));
					}
				}
				else if (kaksoisaskelSarakkeella == 0) {
					if (_lauta[kaksoisaskelSarakkeella + 1][4] && _lauta[kaksoisaskelSarakkeella + 1][4]->getKoodi() == VS) {
						lista.push_back(Siirto(Ruutu(kaksoisaskelSarakkeella + 1, 4), Ruutu(kaksoisaskelSarakkeella, 5)));
					}
				}
				else if (kaksoisaskelSarakkeella == 7) {
					if (_lauta[kaksoisaskelSarakkeella - 1][4] && _lauta[kaksoisaskelSarakkeella - 1][4]->getKoodi() == VS) {
						lista.push_back(Siirto(Ruutu(kaksoisaskelSarakkeella - 1, 4), Ruutu(kaksoisaskelSarakkeella, 5)));
					}
				}
			}
		}
	}
	else {
		if (kaksoisaskelSarakkeella >= 0) {
			if (0 < kaksoisaskelSarakkeella && kaksoisaskelSarakkeella < 7) {
				if (_lauta[kaksoisaskelSarakkeella][3] && _lauta[kaksoisaskelSarakkeella][3]->getKoodi() == VS) {
					if (_lauta[kaksoisaskelSarakkeella - 1][3] && _lauta[kaksoisaskelSarakkeella - 1][3]->getKoodi() == MS) {
						lista.push_back(Siirto(Ruutu(kaksoisaskelSarakkeella - 1, 3), Ruutu(kaksoisaskelSarakkeella, 2)));
					}
					if (_lauta[kaksoisaskelSarakkeella + 1][3] && _lauta[kaksoisaskelSarakkeella + 1][3]->getKoodi() == MS) {
						lista.push_back(Siirto(Ruutu(kaksoisaskelSarakkeella + 1, 3), Ruutu(kaksoisaskelSarakkeella, 2)));
					}
				}
				else if (kaksoisaskelSarakkeella == 0) {
					if (_lauta[kaksoisaskelSarakkeella + 1][3] && _lauta[kaksoisaskelSarakkeella + 1][3]->getKoodi() == MS) {
						lista.push_back(Siirto(Ruutu(kaksoisaskelSarakkeella + 1, 3), Ruutu(kaksoisaskelSarakkeella, 2)));
					}
				}
				else if (kaksoisaskelSarakkeella == 7) {
					if (_lauta[kaksoisaskelSarakkeella - 1][3] && _lauta[kaksoisaskelSarakkeella - 1][3]->getKoodi() == MS) {
						lista.push_back(Siirto(Ruutu(kaksoisaskelSarakkeella - 1, 3), Ruutu(kaksoisaskelSarakkeella, 2)));
					}
				}
			}
		}
	}
}
