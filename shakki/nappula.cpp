#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
#include <iostream>
using namespace std;


Nappula::Nappula(wstring unicode, short int vari, short int koodi, short int arvo)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
	_arvo = arvo;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, short int vari)
{
	short int aloitusRivi = ruutu->getRivi();
	short int aloitusSarake = ruutu->getSarake();

	for (short int i = aloitusRivi + 1; i < 8; i++){
		if (asema->_lauta[aloitusSarake][i] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake, i)));
		else if (asema->_lauta[aloitusSarake][i]->getVari() != vari) {
			lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake, i)));
			break;
		}	
		else break;
	}

	for (short int i = aloitusRivi - 1; i >= 0; i--) {
		if (asema->_lauta[aloitusSarake][i] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake, i)));
		else if (asema->_lauta[aloitusSarake][i]->getVari() != vari) {
			lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake, i)));
			break;
		}
		else break;
	}

	for (short int i = aloitusSarake + 1; i < 8; i++) {
		if (asema->_lauta[i][aloitusRivi] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(i, aloitusRivi)));
		else if (asema->_lauta[i][aloitusRivi]->getVari() != vari) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, aloitusRivi)));
			break;
		}
		else break;
	}

	for (short int i = aloitusSarake - 1; i >= 0; i--) {
		if (asema->_lauta[i][aloitusRivi] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(i, aloitusRivi)));
		else if (asema->_lauta[i][aloitusRivi]->getVari() != vari) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, aloitusRivi)));
			break;
		}
		else break;
	}
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, short int vari)
{
	short int aloitusRivi = ruutu->getRivi();
	short int aloitusSarake = ruutu->getSarake();
	short int Xmoves[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	short int Ymoves[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	for (short int i = 0; i < 8; i++) {
		short int x = aloitusSarake + Xmoves[i];
		short int y = aloitusRivi + Ymoves[i];
		if (x >= 0 && y >= 0 && x < 8 && y < 8 && (asema->_lauta[x][y] == nullptr || asema->_lauta[x][y]->getVari() != vari))
			lista.push_back(Siirto(*ruutu, Ruutu(x, y)));
	}
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, short int vari)
{
	short int aloitusRivi = ruutu->getRivi();
	short int aloitusSarake = ruutu->getSarake();
	for (short int i = aloitusSarake + 1, j = aloitusRivi + 1; i < 8 && j < 8; i++, j++) {
		if (asema->_lauta[i][j] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
		else if (asema->_lauta[i][j]->getVari() != vari) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
			break;
		}
		else break;
	}
	for (short int i = aloitusSarake + 1, j = aloitusRivi - 1; i < 8 && j >= 0; i++, j--) {
		if (asema->_lauta[i][j] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
		else if (asema->_lauta[i][j]->getVari() != vari) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
			break;
		}
		else break;
	}
	for (short int i = aloitusSarake - 1, j = aloitusRivi - 1; i >= 0 && j >= 0; i--, j--) {
		if (asema->_lauta[i][j] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
		else if (asema->_lauta[i][j]->getVari() != vari) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
			break;
		}
		else break;
	}
	for (short int i = aloitusSarake - 1, j = aloitusRivi + 1; i >= 0 && j < 8; i--, j++) {
		if (asema->_lauta[i][j] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
		else if (asema->_lauta[i][j]->getVari() != vari) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
			break;
		}
		else break;
	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, short int vari)
{
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
	Torni::annaSiirrot(lista, ruutu, asema, vari);
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, short int vari)
{
	/*perusidea on ett� kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l�hetill�,
	oman nappulan p��lle ei voi menn� ja vastustajan nappulan voi sy�d�.

	Kaikki muu kuninkaaseen liittyv� tarkistus tehd��n eri paikassa*/
	short int aloitusRivi = ruutu->getRivi();
	short int aloitusSarake = ruutu->getSarake();
	short int Xmoves[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	short int Ymoves[8] = { 1, 0, -1, -1, 1, 1, 0, -1 };
	for (short int i = 0; i < 8; i++) {
		short int x = aloitusSarake + Xmoves[i];
		short int y = aloitusRivi + Ymoves[i];
		if (x >= 0 && y >= 0 && x < 8 && y < 8 && (asema->_lauta[x][y] == nullptr || asema->_lauta[x][y]->getVari() != vari))
			lista.push_back(Siirto(*ruutu, Ruutu(x, y)));
	}
}

void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, short int vari)
{
	short int aloitusRivi = ruutu->getRivi();
	short int aloitusSarake = ruutu->getSarake();
	Nappula* nappula;

	if (vari == (int)0) {
		if (aloitusRivi == 1) {
			if (asema->_lauta[aloitusSarake][2] == nullptr) {
				lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake, 2)));
				if (asema->_lauta[aloitusSarake][3] == nullptr)
					lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake, 3)));
			}
		}
		else if (aloitusRivi + 1 == 7)
		{
			if (asema->_lauta[aloitusSarake][aloitusRivi + 1] == nullptr)
			{
				lisaaSotilaanKorotukset(Siirto(*ruutu, Ruutu(aloitusSarake, aloitusRivi + 1)), lista, vari);
			}
			if (aloitusSarake - 1 >= 0 && asema->_lauta[aloitusSarake - 1][aloitusRivi + 1])
			{
				lisaaSotilaanKorotukset(Siirto(*ruutu, Ruutu(aloitusSarake - 1, aloitusRivi + 1)), lista, vari);
			}
			if (aloitusSarake + 1 <= 7 && asema->_lauta[aloitusSarake + 1][aloitusRivi + 1])
			{
				lisaaSotilaanKorotukset(Siirto(*ruutu, Ruutu(aloitusSarake + 1, aloitusRivi + 1)), lista, vari);
			}
		}
		else if (asema->_lauta[aloitusSarake][aloitusRivi + 1] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake,aloitusRivi + 1)));

		if (aloitusSarake < 7) {
			nappula = asema->_lauta[aloitusSarake + 1][aloitusRivi + 1];
			if (nappula != nullptr && nappula->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake + 1, aloitusRivi + 1)));
		}

		if (aloitusSarake > 0) {
			nappula = asema->_lauta[aloitusSarake - 1][aloitusRivi + 1];
			if (nappula != nullptr && nappula->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake - 1, aloitusRivi + 1)));
		}
	}
	if (vari == (int)1) {
		if (aloitusRivi == 6) {
			if (asema->_lauta[aloitusSarake][5] == nullptr) {
				lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake, 5)));
				if (asema->_lauta[aloitusSarake][4] == nullptr)
					lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake, 4)));
			}
		}
		else if (aloitusRivi - 1 == 0)
		{
			if (asema->_lauta[aloitusSarake][aloitusRivi + 1] == nullptr)
			{
				lisaaSotilaanKorotukset(Siirto(*ruutu, Ruutu(aloitusSarake, aloitusRivi - 1)), lista, vari);
			}
			if (aloitusSarake - 1 >= 0 && asema->_lauta[aloitusSarake - 1][aloitusRivi - 1])
			{
				lisaaSotilaanKorotukset(Siirto(*ruutu, Ruutu(aloitusSarake - 1, aloitusRivi - 1)), lista, vari);
			}
			if (aloitusSarake + 1 <= 7 && asema->_lauta[aloitusSarake + 1][aloitusRivi - 1])
			{
				lisaaSotilaanKorotukset(Siirto(*ruutu, Ruutu(aloitusSarake + 1, aloitusRivi - 1)), lista, vari);
			}
		}
		else if (asema->_lauta[aloitusSarake][aloitusRivi - 1] == nullptr)
			lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake, aloitusRivi - 1)));

		if (aloitusSarake < 7) {
			nappula = asema->_lauta[aloitusSarake + 1][aloitusRivi - 1];
			if (nappula != nullptr && nappula->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake + 1, aloitusRivi - 1)));
		}

		if (aloitusSarake > 0) {
			nappula = asema->_lauta[aloitusSarake - 1][aloitusRivi - 1];
			if (nappula != nullptr && nappula->getVari() != vari)
				lista.push_back(Siirto(*ruutu, Ruutu(aloitusSarake - 1, aloitusRivi - 1)));
		}
	}
}


void Sotilas::lisaaSotilaanKorotukset(Siirto siirto, std::list<Siirto>& lista, short int vari) 
{
	if (vari == (int)0) 
	{
		siirto._miksikorotetaan = Asema::vt;
		lista.push_back(siirto);
		siirto._miksikorotetaan = Asema::vr;
		lista.push_back(siirto);
		siirto._miksikorotetaan = Asema::vl;
		lista.push_back(siirto);
		siirto._miksikorotetaan = Asema::vd;
		lista.push_back(siirto);
	}
	else 
	{
		siirto._miksikorotetaan = Asema::mt;
		lista.push_back(siirto);
		siirto._miksikorotetaan = Asema::mr;
		lista.push_back(siirto);
		siirto._miksikorotetaan = Asema::ml;
		lista.push_back(siirto);
		siirto._miksikorotetaan = Asema::md;
		lista.push_back(siirto);
	}
}
