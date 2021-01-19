#include <iostream>
#include "asema.h"
#include "minMaxPaluu.h"
#include "nappula.h"
#include "ruutu.h"

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
	_siirtovuoro = 1;
	_onkoValkeaKuningasLiikkunut = false;;
	_onkoMustaKuningasLiikkunut = false;	
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut =false;		
	_onkoMustaDTliikkunut=false;			
	_onkoMustaKTliikkunut=false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_lauta[i][j] = nullptr;
		}
	}
	// Ensin alustetaan kaikki laudan ruudut nappulla "NULL", koska muuten ruuduissa satunnaista tauhkaa

	// mustat sotilaat
	for (int i = 0; i < 8; i++)
	{
		_lauta[6][i] = ms;
	}
	//muut mustat nappulat
	_lauta[7][7] = mt;
	_lauta[7][6] = mr;
	_lauta[7][5] = ml;
	_lauta[7][4] = mk;
	_lauta[7][3] = md;
	_lauta[7][2] = ml;
	_lauta[7][1] = mr;
	_lauta[7][0] = mt;

	// valkoiset sotilaat
	for (int i = 0; i < 8; i++)
	{
		_lauta[1][i] = vs;
	}
	//muut valkoiset nappulat
	_lauta[0][7] = vt;
	_lauta[0][6] = vr;
	_lauta[0][5] = vl;
	_lauta[0][4] = vk;
	_lauta[0][3] = vd;
	_lauta[0][2] = vl;
	_lauta[0][1] = vr;
	_lauta[0][0] = vt;

	// Asetetaan alkuaseman mukaisesti nappulat ruuduille
	
}


void Asema::paivitaAsema(Siirto *siirto)
{
	// Kaksoisaskel-lippu on oletusarvoisesti pois päältä.
	// Asetetaan myöhemmin, jos tarvii.


	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna()) 
	{
		if (getSiirtovuoro() == 0 && !getOnkoValkeaKTliikkunut() && !getOnkoValkeaKuningasLiikkunut()) {
			_lauta[0][4] = nullptr;
			_lauta[0][7] = nullptr;
			_lauta[0][5] = vt;
			_lauta[0][5] = vk;
		}
		if (getSiirtovuoro() == 1 && !getOnkoMustaKTliikkunut() && !getOnkoMustaKuningasLiikkunut()) {
			_lauta[7][4] = nullptr;
			_lauta[7][7] = nullptr;
			_lauta[7][5] = mt;
			_lauta[7][5] = mk;
		} 
	}
	// onko pitkä linna
	else if (siirto->onkoPitkalinna())
	{
		if (getSiirtovuoro() == 0 && !getOnkoValkeaDTliikkunut() && !getOnkoValkeaKuningasLiikkunut()) {
			_lauta[0][4] = nullptr;
			_lauta[0][0] = nullptr;
			_lauta[0][3] = vt;
			_lauta[0][2] = vk;
		}
		if (getSiirtovuoro() == 1 && !getOnkoMustaDTliikkunut() && !getOnkoMustaKuningasLiikkunut()) {
			_lauta[7][4] = nullptr;
			_lauta[7][0] = nullptr;
			_lauta[7][3] = mt;
			_lauta[7][2] = mk;
		}
	}
	// Kaikki muut siirrot
	else
	{
		//Ottaa siirron alkuruudussa olleen nappulan talteen 
		Nappula *nappula = _lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()];
		_lauta[siirto->getAlkuruutu().getRivi()][siirto->getAlkuruutu().getSarake()] = nullptr;
		//Laittaa talteen otetun nappulan uuteen ruutuun
		_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = nappula;
		

		// Tarkistetaan oliko sotilaan kaksoisaskel
		// (asetetaan kaksoisaskel-lippu)

		// Ohestalyönti on tyhjään ruutuun. Vieressä oleva (sotilas) poistetaan.

		//// Katsotaan jos nappula on sotilas ja rivi on päätyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittymän laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta lähtenyt nappula

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille väreille)
		if (nappula->getKoodi() == 10 && !_onkoMustaKuningasLiikkunut)_onkoMustaKuningasLiikkunut = true;
		if (nappula->getKoodi() == 4 && !_onkoValkeaKuningasLiikkunut)_onkoValkeaKuningasLiikkunut = true;
		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille väreille ja molemmille torneille)

		// NÄMÄ KUTSUT OIS HYVÄ ALUSTAA
		if(nappula->getKoodi() == 0 && siirto->getAlkuruutu().getRivi() == 0 && siirto->getAlkuruutu().getSarake() == 7) _onkoValkeaKTliikkunut = true;
		if (nappula->getKoodi() == 0 && siirto->getAlkuruutu().getRivi() == 0 && siirto->getAlkuruutu().getSarake() == 0) _onkoValkeaDTliikkunut = true;
		if (nappula->getKoodi() == 6 && siirto->getAlkuruutu().getRivi() == 7 && siirto->getAlkuruutu().getSarake() == 7) _onkoMustaKTliikkunut = true;
		if (nappula->getKoodi() == 6 && siirto->getAlkuruutu().getRivi() == 7 && siirto->getAlkuruutu().getSarake() == 0) _onkoMustaDTliikkunut = true;
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
	return 0;

	//kertoimet asetettu sen takia että niiden avulla asioiden painoarvoa voidaan säätää helposti yhdestä paikasta
	
	//1. Nappuloiden arvo
	
	//2. Kuningas turvassa
	
	//3. Arvosta keskustaa
	
	// 4. Arvosta linjoja
	
}


double Asema::laskeNappuloidenArvo(int vari) 
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


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lisäsin parametrina aseman)
//int maxi(int depth, asema a) 
//	if (depth == 0) return evaluate();
//	int max = -oo;
//	for (all moves ) {
//		score = mini(depth - 1, seuraaja);
//		if (score > max)
//			max = score;
//	}
//	return max;
//}

//int mini(int depth, asema a) {
//	if (depth == 0) return -evaluate();
//	int min = +oo;
//	for (all moves) {
//		score = maxi(depth - 1);
//		if (score < min)
//			min = score;
//	}
//	return min;
//}
MinMaxPaluu Asema::minimax(int syvyys)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	
	// Rekursion kantatapaus 1: peli on loppu
	
	// Rekursion kantatapaus 2: katkaisusyvyydessä
	
	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	
	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys) 
{
	MinMaxPaluu paluu;
	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{

	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari) 
{ 
	
}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	
}
