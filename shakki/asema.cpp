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
	_siirtovuoro = 1;
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


void Asema::paivitaAsema(Siirto* siirto)
{
	// Kaksoisaskel-lippu on oletusarvoisesti pois p‰‰lt‰.
	// Asetetaan myˆhemmin, jos tarvii.

	// Alustus
	int alkuRivi = siirto->getAlkuruutu().getRivi();
	int alkuSarake = siirto->getAlkuruutu().getSarake();

	int loppuRivi = siirto->getLoppuruutu().getRivi();
	int loppuSarake = siirto->getLoppuruutu().getSarake();

	if (alkuRivi < 0 || alkuRivi > 7 || loppuRivi < 0 || loppuRivi > 7 || alkuSarake < 0 || alkuSarake > 7 || loppuSarake < 0 || loppuSarake > 7)
	{
		if (_siirtovuoro == 1) _siirtovuoro = 0;
		else _siirtovuoro = 1;
		return;
	}


	//Tarkastetaan on siirto lyhyt linna
	if (siirto->onkoLyhytLinna())
	{
		if (getSiirtovuoro() == 0 && !getOnkoValkeaKTliikkunut() && !getOnkoValkeaKuningasLiikkunut()) {
			_lauta[4][0] = nullptr;
			_lauta[7][0] = nullptr;
			_lauta[5][0] = vt;
			_lauta[5][0] = vk;
		}
		if (getSiirtovuoro() == 1 && !getOnkoMustaKTliikkunut() && !getOnkoMustaKuningasLiikkunut()) {
			_lauta[4][7] = nullptr;
			_lauta[7][7] = nullptr;
			_lauta[5][7] = mt;
			_lauta[5][7] = mk;
		}
	}
	// onko pitk‰ linna
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
			// Ohestalyˆnti on tyhj‰‰n ruutuun. Vieress‰ oleva (sotilas) poistetaan.
			if (nappulanKoodi == MS && alkuRivi == 3)
				if (alkuSarake != loppuSarake)
					if (_lauta[loppuSarake][loppuRivi] == nullptr)
						_lauta[loppuSarake][loppuRivi + 1] == nullptr;

			if (nappulanKoodi == VS && alkuRivi == 4)
				if (alkuSarake != loppuSarake)
					if (_lauta[loppuSarake][loppuRivi] == nullptr)
						_lauta[loppuSarake][loppuRivi - 1] == nullptr;
		}


		//// Katsotaan jos nappula on sotilas ja rivi on p‰‰tyrivi niin ei vaihdeta nappulaa 
		////eli alkuruutuun laitetaan null ja loppuruudussa on jo kliittym‰n laittama nappula MIIKKA, ei taida minmaxin kanssa hehkua?
		if (nappulanKoodi == MS)
		{
			if (loppuRivi == 0)
			{
				wcout << "Miksi korotetaan N/R/B/Q" << endl;
				wchar_t input;
				wcin >> input;
				_lauta[alkuSarake][alkuRivi] = nullptr;
				switch (input)
				{
				case 78:
					_lauta[loppuSarake][loppuRivi] = mr;
					break;
				case 82:
					_lauta[loppuSarake][loppuRivi] = mt;
					break;
				case 66:
					_lauta[loppuSarake][loppuRivi] = ml;
					break;
				case 81:
					_lauta[loppuSarake][loppuRivi] = md;
					break;
				}
			}
		}
		else if (nappulanKoodi == VS)
		{
			if (loppuRivi == 7)
			{
				wcout << "Miksi korotetaan N/R/B/Q" << endl;
				wchar_t input;
				wcin >> input;
				_lauta[alkuSarake][alkuRivi] = nullptr;
				switch (input)
				{
				case 78:
					_lauta[loppuSarake][loppuRivi] = vr;
					break;
				case 82:
					_lauta[loppuSarake][loppuRivi] = vt;
					break;
				case 66:
					_lauta[loppuSarake][loppuRivi] = vl;
					break;
				case 81:
					_lauta[loppuSarake][loppuRivi] = vd;
					break;
				}
			}
		}

		//
		////muissa tapauksissa alkuruutuun null ja loppuruutuun sama alkuruudusta l‰htenyt nappula

		// katsotaan jos liikkunut nappula on kuningas niin muutetaan onkoKuningasLiikkunut arvo (molemmille v‰reille)
		// katsotaan jos liikkunut nappula on torni niin muutetaan onkoTorniLiikkunut arvo (molemmille v‰reille ja molemmille torneille)

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
		//p‰ivitet‰‰n _siirtovuoro

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
L‰hetti = 3,25
Ratsu = 3
Sotilas = 1

2. Kuninkaan hyvyys
Jos avaus tai keskipeli, niin hyv‰ ett‰ kunigas g1 tai b1/c1
Loppupeliss‰ vaikea sanoa halutaanko olla auttamassa omaa sotilasta korottumaan
vai olla est‰m‰ss‰ vastustajan korotusta siksi ei oteta kantaa
3. Arvosta keskustaa sotilailla ja ratsuilla
4. Arvosta pitki‰ linjoja daami, torni ja l‰hetti
*/
double Asema::evaluoi()
{
	double evaluaatio = 0;

	Ruutu* valkoinenK;
	Ruutu* mustaK;
	//kertoimet asetettu sen takia ett‰ niiden avulla asioiden painoarvoa voidaan s‰‰t‰‰ helposti yhdest‰ paikasta
	double d = 9, t = 5, l = 3.25, r = 3, s = 1;

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
						valkoinenK = new Ruutu(i, j);
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
						mustaK = new Ruutu(i, j);
					}
				}
			}
		}

	int vkSarake = valkoinenK->getSarake();
	int vkRivi = valkoinenK->getRivi();

	int mkSarake = mustaK->getSarake();
	int mkRivi = mustaK->getRivi();

	// 2. kuninkaan turvallisuus
	// evaluaatioon lis‰t‰‰n 0.25 jos kuningas on tornittanut ja/tai liikkunut pois keskelt‰
	// lis‰ksi mik‰li kuninkaan edess‰ ja ainakin toisessa viistoruudussa on oma nappula lis‰t‰‰n 0.75
	// numeroita varmasti pit‰‰ viilata
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
		if (mkSarake <= 7 || mkSarake == 6 || mkSarake == 2 || mkSarake >= 0)
		{
			evaluaatio -= 0.25;
			if ((_lauta[mkSarake][6] && _lauta[mkSarake][6]->getVari() == 0) &&
				((mkSarake - 1 >= 0 && _lauta[mkSarake - 1][6] && _lauta[mkSarake - 1][6]->getVari() == 0) ||
					(mkSarake + 1 <= 7 && _lauta[mkSarake + 1][6] && _lauta[mkSarake + 1][6]->getVari() == 0)))
				evaluaatio -= 0.75;
		}


	// 3. Arvosta keskustaa

	// 4. Arvosta linjoja
	return evaluaatio;
}


double Asema::laskeNappuloidenArvo(int vari)
{
	return 0;

}


bool Asema::onkoAvausTaiKeskipeli(int vari)
{
	return 0;
	// Jos upseereita 3 tai v‰hemm‰n on loppupeli
	// mutta jos daami laudalla on loppueli vasta kun kuin vain daami j‰ljell‰

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


// https://chessprogramming.wikispaces.com/Minimax MinMax-algoritmin pseudokoodi (lis‰sin parametrina aseman)
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
	std::list<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);
	// Rekursion kantatapaus 1: peli on loppu
	if (siirrot.size() == 0) {
		return paluuarvo;
	}
	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	else if (getSiirtovuoro() == 0) paluuarvo = maxi(syvyys);
	else if (getSiirtovuoro() == 1) paluuarvo = mini(syvyys);

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).

	return paluuarvo;
}


MinMaxPaluu Asema::maxi(int syvyys)
{
	MinMaxPaluu paluu;
	paluu._evaluointiArvo = evaluoi();
	if (syvyys == 0) return paluu;

	std::list<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);
	double korkeinArvo = 0;
	Siirto parasSiirto;

	for each (Siirto siirto in siirrot) {
		//siirret‰‰n nappulaa siirron mukaisesti
		int alkuSarake = siirto.getAlkuruutu().getSarake();
		int alkuRivi = siirto.getAlkuruutu().getRivi();
		int loppuSarake = siirto.getLoppuruutu().getSarake();
		int loppuRivi = siirto.getLoppuruutu().getRivi();

		Nappula* poistoNappula = nullptr;
		if(_lauta[loppuSarake][loppuRivi])
			poistoNappula = _lauta[loppuSarake][loppuRivi];

		_lauta[loppuSarake][loppuRivi] = _lauta[alkuSarake][alkuRivi];
		_lauta[alkuSarake][alkuRivi] = nullptr;
		//katsotaan seuraavat arvot

		double ehdotettuArvo = mini(syvyys - 1)._evaluointiArvo;
		if (korkeinArvo < ehdotettuArvo) {
			korkeinArvo = ehdotettuArvo;
			parasSiirto = siirto;
		}

		//siirret‰‰n nappula takaisin.
		_lauta[alkuSarake][alkuRivi] = _lauta[loppuSarake][loppuRivi];

		_lauta[loppuSarake][loppuRivi] = poistoNappula;
	}
	paluu._evaluointiArvo = korkeinArvo;
	paluu._parasSiirto = parasSiirto;


	return paluu;
}


MinMaxPaluu Asema::mini(int syvyys)
{
	MinMaxPaluu paluu;

	if (syvyys == 0) {
		paluu._evaluointiArvo = evaluoi();
		return paluu;
	}

	std::list<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);
	double matalinArvo = 0;
	Siirto parasSiirto;

	for each (Siirto siirto in siirrot) {
		//siirret‰‰n nappulaa siirron mukaisesti
		int alkuSarake = siirto.getAlkuruutu().getSarake();
		int alkuRivi = siirto.getAlkuruutu().getRivi();
		int loppuSarake = siirto.getLoppuruutu().getSarake();
		int loppuRivi = siirto.getLoppuruutu().getRivi();

		Nappula* poistoNappula = nullptr;
		if (_lauta[loppuSarake][loppuRivi])
			poistoNappula = _lauta[loppuSarake][loppuRivi];

		_lauta[loppuSarake][loppuRivi] = _lauta[alkuSarake][alkuRivi];
		_lauta[alkuSarake][alkuRivi] = nullptr;
		//katsotaan seuraavat arvot

		double ehdotettuArvo = maxi(syvyys - 1)._evaluointiArvo;
		if (ehdotettuArvo < matalinArvo) {
			matalinArvo = ehdotettuArvo;
			parasSiirto = siirto;
		}

		//siirret‰‰n nappula takaisin.
		_lauta[alkuSarake][alkuRivi] = _lauta[loppuSarake][loppuRivi];

		_lauta[loppuSarake][loppuRivi] = poistoNappula;
	}
	paluu._evaluointiArvo = matalinArvo;
	paluu._parasSiirto = parasSiirto;


	return paluu;
}


bool Asema::onkoRuutuUhattu(Ruutu* ruutu, int vastustajanVari)
{
	std::list<Siirto> tempLista;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (_lauta[i][j] && _lauta[i][j]->getVari() == vastustajanVari)
				_lauta[i][j]->annaSiirrot(tempLista, new Ruutu(i, j), this, vastustajanVari);

	std::list<Siirto>::iterator iterator;
	for (iterator = tempLista.begin(); iterator != tempLista.end(); iterator++)
		if (&iterator->getLoppuruutu() == ruutu)
			return true;
	return false;
}


void Asema::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, int vari)
{

}


void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista) {
	Ruutu* kuninkaanRuutu;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (_lauta[i][j] && _lauta[i][j]->getVari() == _siirtovuoro)
				_lauta[i][j]->annaSiirrot(lista, new Ruutu(i, j), this, _siirtovuoro);

			if (_lauta[i][j] && ((_siirtovuoro == 0 && _lauta[i][j]->getKoodi() == VK) || (_siirtovuoro == 1 && _lauta[i][j]->getKoodi() == MK)))
				kuninkaanRuutu = new Ruutu(i, j);
		}

	for each (Siirto siirto in lista)
	{
		int alkuSarake = siirto.getAlkuruutu().getSarake();
		int alkuRivi = siirto.getAlkuruutu().getRivi();
		int loppuSarake = siirto.getLoppuruutu().getSarake();
		int loppuRivi = siirto.getLoppuruutu().getRivi();

		Nappula* poistoNappula = _lauta[loppuSarake][loppuRivi];
		_lauta[loppuSarake][loppuRivi] = _lauta[alkuSarake][alkuRivi];
		_lauta[alkuSarake][alkuRivi] = nullptr;

		if ((_siirtovuoro == 0 && _lauta[kuninkaanRuutu->getSarake()][kuninkaanRuutu->getRivi()]->getKoodi() == VK) || (_siirtovuoro == 1 && _lauta[kuninkaanRuutu->getSarake()][kuninkaanRuutu->getRivi()]->getKoodi() == MK))
		{
			Ruutu* tempRuutu = kuninkaanRuutu;
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					if (_lauta[i][j] && ((_siirtovuoro == 0 && _lauta[i][j]->getKoodi() == VK) || (_siirtovuoro == 1 && _lauta[i][j]->getKoodi() == MK)))
						kuninkaanRuutu = new Ruutu(i, j);

			if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro))
				lista.remove(siirto);

			_lauta[alkuSarake][alkuRivi] = _lauta[loppuSarake][loppuRivi];
			_lauta[loppuSarake][loppuRivi] = poistoNappula;

			delete(kuninkaanRuutu),
				kuninkaanRuutu = tempRuutu;
		}
		else
		{
			if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro))
				lista.remove(siirto);

			_lauta[alkuSarake][alkuRivi] = _lauta[loppuSarake][loppuRivi];
			_lauta[loppuSarake][loppuRivi] = poistoNappula;
		}
	}
	//Tornitukset
	if (_siirtovuoro == 0 && (!getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaDTliikkunut())) {
		bool laiton = false;
		Ruutu* ruutu1 = new Ruutu(2, 0);
		Ruutu* ruutu2 = new Ruutu(3, 0);
		if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu1, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu2, !_siirtovuoro)) laiton = true;
		if (!laiton) lista.push_back(Siirto(false, true));
		delete(ruutu1);
		delete(ruutu2);
	}
	if (_siirtovuoro == 1 && (!getOnkoMustaKuningasLiikkunut() && !getOnkoMustaDTliikkunut())) {
		bool laiton = false;
		Ruutu* ruutu1 = new Ruutu(2, 7);
		Ruutu* ruutu2 = new Ruutu(3, 7);
		if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu1, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu2, !_siirtovuoro)) laiton = true;
		if (!laiton) lista.push_back(Siirto(false, true));
		delete(ruutu1);
		delete(ruutu2);
	}
	if (_siirtovuoro == 0 && (!getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaKTliikkunut())) {
		bool laiton = false;
		Ruutu* ruutu1 = new Ruutu(5, 0);
		if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu1, !_siirtovuoro)) laiton = true;
		if (!laiton) lista.push_back(Siirto(false, true));
		delete(ruutu1);

	}
	if (_siirtovuoro == 1 && (!getOnkoMustaKuningasLiikkunut() && !getOnkoMustaKTliikkunut())) {
		bool laiton = false;
		Ruutu* ruutu1 = new Ruutu(5, 7);
		if (onkoRuutuUhattu(kuninkaanRuutu, !_siirtovuoro)) laiton = true;
		else if (onkoRuutuUhattu(ruutu1, !_siirtovuoro)) laiton = true;
		if (!laiton) lista.push_back(Siirto(false, true));
		delete(ruutu1);
	}
	delete(kuninkaanRuutu);
}
