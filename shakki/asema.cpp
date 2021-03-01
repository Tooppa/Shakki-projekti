#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"
using namespace std;

Nappula* Asema::vk = new Kuningas(L"\u2654", 0, VK);
Nappula* Asema::vd = new Daami(L"\u2655", 0, VD);
Nappula* Asema::vt = new Torni(L"\u2656", 0, VT);
Nappula* Asema::vl = new Lahetti(L"\u2657", 0, VL);
Nappula* Asema::vr = new Ratsu(L"\u2658", 0, VR);
Nappula* Asema::vs = new Sotilas(L"\u2659", 0, VS);

Nappula* Asema::mk = new Kuningas(L"\u265A", 1, MK);
Nappula* Asema::md = new Daami(L"\u265B", 1, MD);
Nappula* Asema::mt = new Torni(L"\u265C", 1, MT);
Nappula* Asema::ml = new Lahetti(L"\u265D", 1, ML);
Nappula* Asema::mr = new Ratsu(L"\u265E", 1, MR);
Nappula* Asema::ms = new Sotilas(L"\u265F", 1, MS);


Asema::Asema()
{
	_siirtovuoro = 0;
	_onkoValkeaKuningasLiikkunut = false;;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			_lauta[i][j] = nullptr;
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa

	// mustat sotilaat
	for (int i = 0; i < 8; i++)
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
	for (int i = 0; i < 8; i++)
	{
		_lauta[i][1] = vs;
	}
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
		}
		if (getSiirtovuoro() == 1 && !getOnkoMustaKTliikkunut() && !getOnkoMustaKuningasLiikkunut()) {
			_lauta[4][7] = nullptr;
			_lauta[7][7] = nullptr;
			_lauta[5][7] = mt;
			_lauta[6][7] = mk;
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
		}
		if (getSiirtovuoro() == 1 && !getOnkoMustaDTliikkunut() && !getOnkoMustaKuningasLiikkunut()) {
			_lauta[4][7] = nullptr;
			_lauta[0][7] = nullptr;
			_lauta[3][7] = mt;
			_lauta[2][7] = mk;
		}
	}
	// Kaikki muut siirrot
	else
	{
		int alkuRivi = siirto->getAlkuruutu().getRivi();
		int alkuSarake = siirto->getAlkuruutu().getSarake();

		int loppuRivi = siirto->getLoppuruutu().getRivi();
		int loppuSarake = siirto->getLoppuruutu().getSarake();

		// jos laiton siirto niin vaihdetaan vuoroa
		if (alkuRivi < 0 || alkuRivi > 7 || loppuRivi < 0 || loppuRivi > 7 || alkuSarake < 0 || alkuSarake > 7 || loppuSarake < 0 || loppuSarake > 7)
		{
			if (_siirtovuoro == 1) _siirtovuoro = 0;
			else _siirtovuoro = 1;
			return;
		}
		//Ottaa siirron alkuruudussa olleen nappulan talteen 
		Nappula* nappula = _lauta[alkuSarake][alkuRivi];

		//Alustus
		int nappulanKoodi = nappula->getKoodi();

		_lauta[alkuSarake][alkuRivi] = nullptr;
		//Laittaa talteen otettu nappula uuteen ruutuun
		_lauta[loppuSarake][loppuRivi] = nappula;

		// Tarkistetaan oliko sotilaan kaksoisaskel
		if (nappulanKoodi == MS || nappulanKoodi == VS)
			if (abs(alkuRivi - loppuRivi) == 2)
				kaksoisaskelSarakkeella = alkuSarake;
			else
				kaksoisaskelSarakkeella = -1;

		// (asetetaan kaksoisaskel-lippu)
		if (kaksoisaskelSarakkeella != -1 && loppuSarake == kaksoisaskelSarakkeella)
		{
			// Ohestalyönti on tyhjään ruutuun. Vieressä oleva (sotilas) poistetaan.
			if (nappulanKoodi == MS && alkuRivi == 3)
				if (alkuSarake != loppuSarake)
					if (_lauta[loppuSarake][loppuRivi] == nullptr)
						_lauta[loppuSarake][loppuRivi + 1] == nullptr;

			if (nappulanKoodi == VS && alkuRivi == 4)
				if (alkuSarake != loppuSarake)
					if (_lauta[loppuSarake][loppuRivi] == nullptr)
						_lauta[loppuSarake][loppuRivi - 1] == nullptr;
		}


		//// Katsotaan jos nappula on sotilas ja rivi on päätyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittymän laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		if ((nappulanKoodi == MS && loppuRivi == 0) || (nappulanKoodi == VS && loppuRivi == 7))
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
		case VK:
			if (!_onkoValkeaKuningasLiikkunut)_onkoValkeaKuningasLiikkunut = true;
		case MT:
			if (alkuRivi == 7 && alkuSarake == 7) _onkoMustaKTliikkunut = true;
			else if (alkuRivi == 7 && alkuSarake == 0) _onkoMustaDTliikkunut = true;
		case MK:
			if (!_onkoMustaKuningasLiikkunut)_onkoMustaKuningasLiikkunut = true;
		}
		//päivitetään _siirtovuoro

	}
	if (_siirtovuoro == 1) _siirtovuoro = 0;
	else _siirtovuoro = 1;
}



int Asema::getSiirtovuoro()
{
	return _siirtovuoro;
}


void Asema::setSiirtovuoro(int vuoro)
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
	double k = 100000, d = 9, t = 5, l = 3.25, r = 3, s = 1;

	Ruutu valkoinenK;
	Ruutu mustaK;

	//1. Nappuloiden arvo
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[i][j])
			{
				if (_lauta[i][j]->getVari() == 0)
				{
					switch (_lauta[i][j]->getKoodi())
					{
					case VS:
						evaluaatio += s;
					case VT:
						evaluaatio += t;
					case VR:
						evaluaatio += r;
					case VL:
						evaluaatio += l;
					case VD:
						evaluaatio += d;
						// otetaan kuningas talteen
					case VK:
						evaluaatio += k;
						valkoinenK = Ruutu(i, j);
					}
				}
				else
				{
					switch (_lauta[i][j]->getKoodi())
					{
					case MS:
						evaluaatio -= s;
					case MT:
						evaluaatio -= t;
					case MR:
						evaluaatio -= r;
					case ML:
						evaluaatio -= l;
					case MD:
						evaluaatio -= d;
						// otetaan kuningas talteen
					case MK:
						evaluaatio -= k;
						mustaK = Ruutu(i, j);
					}
				}
			}
		}

	int vkSarake = valkoinenK.getSarake();
	int vkRivi = valkoinenK.getRivi();

	int mkSarake = mustaK.getSarake();
	int mkRivi = mustaK.getRivi();

	// 2. kuninkaan turvallisuus
	// evaluaatioon lisätään 0.25 jos kuningas on tornittanut ja/tai liikkunut pois keskeltä
	// lisäksi mikäli kuninkaan edessä ja ainakin toisessa viistoruudussa on oma nappula lisätään 0.75
	// numeroita varmasti pitää viilata
	if (vkRivi == 0)
		if (vkSarake <= 7 || vkSarake >= 6 || vkSarake <= 2 || vkSarake >= 0)
		{
			evaluaatio += 0.25;
			if ((_lauta[vkSarake][1] && _lauta[vkSarake][1]->getVari() == 0) &&
				((vkSarake - 1 >= 0 && _lauta[vkSarake - 1][1] && _lauta[vkSarake - 1][1]->getVari() == 0) ||
					(vkSarake + 1 <= 7 && _lauta[vkSarake + 1][1] && _lauta[vkSarake + 1][1]->getVari() == 0)))
				evaluaatio += 0.75;
		}
	if (mkRivi == 7)
		if (mkSarake <= 7 || mkSarake >= 6 || mkSarake <= 2 || mkSarake >= 0)
		{
			evaluaatio -= 0.25;
			if ((_lauta[mkSarake][6] && _lauta[mkSarake][6]->getVari() == 1) &&
				((mkSarake - 1 >= 0 && _lauta[mkSarake - 1][6] && _lauta[mkSarake - 1][6]->getVari() == 0) ||
					(mkSarake + 1 <= 7 && _lauta[mkSarake + 1][6] && _lauta[mkSarake + 1][6]->getVari() == 0)))
				evaluaatio -= 0.75;
		}

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
	float arvostusTaulukkoMS[8][8] =
	{ {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4},
	{0.0, 0.0, 0.0, 0.3, 0.3, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.3, 0.3, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.3, 0.3, 0.0, 0.0, 0.0},
	{0.1, 0.0, 0.0, 0.2, 0.2, 0.0, 0.0, 0.1},
	{0.05, 0.1, 0.1, -0.2, -0.2, 0.1, 0.1, 0.05},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} };

	float arvostusTaulukkoVS[8][8] =
	{ {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{0.05, 0.1, 0.1, -0.2, -0.2, 0.1, 0.1, 0.05},
	{0.1, 0.0, 0.0, 0.2, 0.2, 0.0, 0.0, 0.1},
	{0.0, 0.0, 0.0, 0.3, 0.3, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.3, 0.3, 0.0, 0.0, 0.0},
	{0.0, 0.0, 0.0, 0.3, 0.3, 0.0, 0.0, 0.0},
	{0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4},
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} };

	float arvostusTaulukkoMR[8][8] =
	{ {-0.3, -0.2, -0.1, 0.0, 0.0, -0.1, -0.2, -0.3},
	{0.0, 0.1, 0.2, 0.2, 0.2, 0.2, 0.1, 0.0},
	{0.0, 0.2, 0.3, 0.3, 0.3, 0.3, 0.2, 0.0},
	{0.0, 0.2, 0.3, 0.4, 0.4, 0.3, 0.2, 0.0},
	{0.0, 0.2, 0.3, 0.4, 0.4, 0.3, 0.2, 0.0},
	{0.0, 0.2, 0.3, 0.3, 0.3, 0.3, 0.2, 0.0},
	{0.0, 0.1, 0.2, 0.2, 0.2, 0.2, 0.1, 0.0},
	{-0.3, -0.2, -0.1, 0.0, 0.0, -0.1, -0.2, -0.3} };

	float arvostusTaulukkoVR[8][8] =
	{ {-0.3, -0.2, -0.1, 0.0, 0.0, -0.1, -0.2, -0.3},
	{0.0, 0.1, 0.2, 0.2, 0.2, 0.2, 0.1, 0.0},
	{0.0, 0.2, 0.3, 0.3, 0.3, 0.3, 0.2, 0.0},
	{0.0, 0.2, 0.3, 0.4, 0.4, 0.3, 0.2, 0.0},
	{0.0, 0.2, 0.3, 0.4, 0.4, 0.3, 0.2, 0.0},
	{0.0, 0.2, 0.3, 0.3, 0.3, 0.3, 0.2, 0.0},
	{0.0, 0.1, 0.2, 0.2, 0.2, 0.2, 0.1, 0.0},
	{-0.3, -0.2, -0.1, 0.0, 0.0, -0.1, -0.2, -0.3} };

	float arvostusTaulukkoMT[8][8] =
	{ {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2},
	{0.3, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.3},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{0.0, 0.0, 0.1, 0.2, 0.2, 0.1, 0.0, 0.0} };

	float arvostusTaulukkoVT[8][8] =
	{ {0.0, 0.0, 0.1, 0.2, 0.2, 0.1, 0.0, 0.0},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.1},
	{0.3, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.3},
	{0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2} };

	float arvostusTaulukkoML[8][8] =
	{ {-0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, -0.1},
	{0.1, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.1},
	{0.1, 0.2, 0.0, 0.3, 0.3, 0.0, 0.2, 0.1},
	{0.1, 0.25, 0.0, 0.3, 0.3, 0.0, 0.25, 0.1},
	{0.1, 0.2, 0.4, 0.3, 0.3, 0.4, 0.2, 0.1},
	{0.1, 0.0, 0.3, 0.3, 0.3, 0.3, 0.0, 0.1},
	{0.1, 0.0, 0.2, 0.2, 0.2, 0.2, 0.0, 0.1},
	{0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2} };

	float arvostusTaulukkoVL[8][8] =
	{ {0.2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.2 },
	{ 0.1, 0.0, 0.2, 0.2, 0.2, 0.2, 0.0, 0.1 },
	{ 0.1, 0.0, 0.3, 0.3, 0.3, 0.3, 0.0, 0.1 },
	{ 0.1, 0.2, 0.4, 0.3, 0.3, 0.4, 0.2, 0.1 },
	{ 0.1, 0.25, 0.0, 0.3, 0.3, 0.0, 0.25, 0.1},
	{ 0.1, 0.2, 0.0, 0.3, 0.3, 0.0, 0.2, 0.1 },
	{ 0.1, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.1 },
	{ -0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, -0.1} };

	float arvostusTaulukkoMD[8][8] =
	{ {-0.1, 0.1, 0.1, 0.2, 0.2, 0.1, 0.1, -0.1},
		{0.1, 0.3, 0.3, 0.3, 0.3, 0.3, 030, 0.1},
		{0.1, 0.3, 0.4, 0.4, 0.4, 0.4, 0.3, 0.1},
		{0.2, 0.3, 0.4, 0.4, 0.4, 0.4, 0.3, 0.1},
		{0.3, 0.3, 0.4, 0.4, 0.4, 0.4, 0.3, 0.2},
		{0.1, 0.4, 0.4, 0.4, 0.4, 0.4, 0.3, 0.1},
		{0.1, 0.2, 0.4, 0.4, 0.4, 0.3, 0.3, 0.1},
		{-0.2, 0.1, 0.1, 0.2, 0.2, 0.1, 0.1, -0.2} };

	float arvostusTaulukkoVD[8][8] =
	{ {-0.2, 0.1, 0.1, 0.2, 0.2, 0.1, 0.1, -0.2},
		{0.1, 0.2, 0.4, 0.4, 0.4, 0.3, 0.3, 0.1},
		{0.1, 0.4, 0.4, 0.4, 0.4, 0.4, 0.3, 0.1},
		{0.2, 0.3, 0.4, 0.4, 0.4, 0.4, 0.3, 0.3},
		{0.1, 0.3, 0.4, 0.4, 0.4, 0.4, 0.3, 0.2},
		{0.1, 0.3, 0.4, 0.4, 0.4, 0.4, 0.3, 0.2},
		{0.1, 0.3, 0.3, 0.3, 0.3, 0.3, 030, 0.1},
		{-0.1, 0.1, 0.1, 0.2, 0.2, 0.1, 0.1, -0.1} };

	int valkoisiaNappuloita = 0;
	int mustiaNappuloita = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (_lauta[i][j])
				if (_lauta[i][j]->getVari() == 0)
					valkoisiaNappuloita++;
				else mustiaNappuloita++;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			if (_lauta[i][j] && _lauta[i][j]->getKoodi() == MS)
				evaluaatio -= arvostusTaulukkoMS[i][j];
			else if (_lauta[i][j] && _lauta[i][j]->getKoodi() == VS)
				evaluaatio += arvostusTaulukkoVS[i][j];
			else if (_lauta[i][j] && _lauta[i][j]->getKoodi() == MR)
				evaluaatio -= arvostusTaulukkoMR[i][j];
			else if (_lauta[i][j] && _lauta[i][j]->getKoodi() == VR)
				evaluaatio += arvostusTaulukkoVR[i][j];
			else if (_lauta[i][j] && _lauta[i][j]->getKoodi() == MT)
				evaluaatio -= arvostusTaulukkoMT[i][j];
			else if (_lauta[i][j] && _lauta[i][j]->getKoodi() == VT)
				evaluaatio += arvostusTaulukkoVT[i][j];
			else if (_lauta[i][j] && _lauta[i][j]->getKoodi() == ML)
				evaluaatio -= arvostusTaulukkoML[i][j];
			else if (_lauta[i][j] && _lauta[i][j]->getKoodi() == VL)
				evaluaatio += arvostusTaulukkoVL[i][j];
			else if (_lauta[i][j] && _lauta[i][j]->getKoodi() == MD)
				evaluaatio -= arvostusTaulukkoMD[i][j];
			else if (_lauta[i][j] && _lauta[i][j]->getKoodi() == VD)
				evaluaatio += arvostusTaulukkoVD[i][j];
		}

	// 4. Arvosta linjoja
	return evaluaatio;
}

// laskee nappuloiden arvot ja ottaa kuninkaat talteen
double Asema::laskeNappuloidenArvo(int i)
{
	return 0;
}


bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	return 0;
	// Jos upseereita 3 tai vähemmän on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami jäljellä

	//Jos vari on 0 eli valkoiset
	//niin on keskipeli jos mustalla upseereita yli 2 tai jos daami+1


}


double Asema::nappuloitaKeskella(int vari)
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


double Asema::linjat(int vari)
{
	return 0;

	//valkoiset

	//mustat

}
MinMaxPaluu Asema::alphaBeta(int depth, double alpha, double beta)
{
	MinMaxPaluu paluu;
	std::list<Siirto> lista;
	Ruutu kuninkaanRuutu;
	// Kantatapaukset 1 ja 2 : matti tai patti?
	this->annaLaillisetSiirrot(lista);

	//// mikäli jää aikaa nii hyvä tapa optimoida on järjestää nopeesti lista
	//this->jarjestaLista(lista);

	if (lista.size() == 0)
	{
		int vihu = _siirtovuoro == 0 ? 1 : 0;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (_lauta[i][j] && ( _lauta[i][j]->getKoodi() == VK ||  _lauta[i][j]->getKoodi() == MK))
					kuninkaanRuutu = Ruutu(i, j);
		if (this->onkoRuutuUhattu(kuninkaanRuutu, vihu))
		{
			paluu._evaluointiArvo = _siirtovuoro == 0 ? DBL_MIN : DBL_MAX;
		}
		else
		{
			paluu._evaluointiArvo = 0;
		}
		return paluu;
	}
	// Kantatapaus 3: katkaisusyvyys
	if (depth == 0)
	{
		paluu._evaluointiArvo = this->evaluoi();
		return paluu;
	}
	if (_siirtovuoro == 0)
	{
		paluu._evaluointiArvo = DBL_MIN;
		for each (Siirto siirto in lista)
		{
			Asema uusiAsema = *this;
			uusiAsema.paivitaAsema(&siirto);
			double arvo = uusiAsema.alphaBeta(depth - 1, alpha, beta)._evaluointiArvo;
			if (arvo > paluu._evaluointiArvo)
			{
				paluu._evaluointiArvo = arvo;
				paluu._parasSiirto = siirto;
			}
			alpha = std::max(alpha, paluu._evaluointiArvo);
			if (alpha >= beta)
				break;
		}
	}
	else
	{
		paluu._evaluointiArvo = DBL_MAX;
		for each (Siirto siirto in lista)
		{
			Asema uusiAsema = *this;
			uusiAsema.paivitaAsema(&siirto);
			double arvo = uusiAsema.alphaBeta(depth - 1, alpha, beta)._evaluointiArvo;
			if (arvo < paluu._evaluointiArvo)
			{
				paluu._evaluointiArvo = arvo;
				paluu._parasSiirto = siirto;
			}
			beta = std::min(beta, paluu._evaluointiArvo);
			if (beta <= alpha)
				break;
		}
	}
	return paluu;
}

// jotai optimointia
void Asema::jarjestaLista(std::list<Siirto>& lista)
{
	for each (Siirto siirto in lista)
	{

	}
}

bool Asema::onkoRuutuUhattu(Ruutu ruutu, int vastustajanVari)
{
	list<Siirto> siirrot;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (_lauta[i][j] && _lauta[i][j]->getVari() == vastustajanVari)
				_lauta[i][j]->annaSiirrot(siirrot, &Ruutu(i, j), this, vastustajanVari);

	for each (Siirto siirto in siirrot)
		if (siirto.getLoppuruutu() == ruutu)
			return true;
	return false;
}


void Asema::huolehdiKuninkaanShakeista(list<Siirto>& lista, int vari)
{

}


void Asema::annaLaillisetSiirrot(list<Siirto>& lista) {
	Ruutu kuninkaanRuutu;
	Asema uusiAsema;
	list<Siirto> poistettava;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
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
		
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
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
