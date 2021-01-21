#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;


Nappula::Nappula(wstring unicode, int vari, int koodi)
{
	_unicode = unicode;
	_vari = vari;
	_koodi = koodi;
}


void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int aloitusRivi = ruutu->getRivi();
	int aloitusSarake = ruutu->getSarake();
	for (int i = ruutu->getRivi() + 1; i < 8; i++){
		if (asema->_lauta[i][aloitusSarake] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, aloitusSarake)));
		else if (asema->_lauta[i][aloitusRivi]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, aloitusSarake)));
			break;
		}	
		else break;
	}
	for (int i = ruutu->getRivi() - 1; i >= 0; i--) {
		if (asema->_lauta[i][aloitusSarake] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, aloitusSarake)));
		else if (asema->_lauta[i][aloitusRivi]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, aloitusSarake)));
			break;
		}
		else break;
	}
	for (int i = ruutu->getSarake() + 1; i < 8; i++) {
		if (asema->_lauta[aloitusRivi][i] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi, i)));
		else if (asema->_lauta[i][aloitusRivi]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi, i)));
			break;
		}
		else break;
	}
	for (int i = ruutu->getSarake() - 1; i >= 0; i--) {
		if (asema->_lauta[aloitusRivi][i] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi, i)));
		else if (asema->_lauta[aloitusRivi][i]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi, i)));
			break;
		}
		else break;
	}
}


void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int aloitusRivi = ruutu->getRivi();
	int aloitusSarake = ruutu->getSarake();
	int Xmoves[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int Ymoves[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	for (int i = 0; i < 8; i++) {
		int x = aloitusRivi + Xmoves[i];
		int y = aloitusSarake + Ymoves[i];
		if (x >= 0 && y >= 0 && x < 8 && y < 8 && (asema->_lauta[x][y] == nullptr || asema->_lauta[x][y]->getVari() != vari))
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(x, y)));
	}
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int aloitusRivi = ruutu->getRivi();
	int aloitusSarake = ruutu->getSarake();
	for (int i = ruutu->getRivi() + 1, j = ruutu->getSarake() + 1; i < 8 && j < 8; i++, j++) {
		if (asema->_lauta[i][j] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, j)));
		else if (asema->_lauta[i][j]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, j)));
			break;
		}
		else break;
	}
	for (int i = ruutu->getRivi() + 1, j = ruutu->getSarake() - 1; i < 8 && j >= 0; i++, j--) {
		if (asema->_lauta[i][j] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, j)));
		else if (asema->_lauta[i][j]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, j)));
			break;
		}
		else break;
	}
	for (int i = ruutu->getRivi() - 1, j = ruutu->getSarake() - 1; i >= 0 && j >= 0; i--, j--) {
		if (asema->_lauta[i][j] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, j)));
		else if (asema->_lauta[i][j]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, j)));
			break;
		}
		else break;
	}
	for (int i = ruutu->getRivi() - 1, j = ruutu->getSarake() + 1; i >= 0 && j < 8; i--, j++) {
		if (asema->_lauta[i][j] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, j)));
		else if (asema->_lauta[i][j]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, j)));
			break;
		}
		else break;
	}
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	Lahetti::annaSiirrot(lista, ruutu, asema, vari);
	Torni::annaSiirrot(lista, ruutu, asema, vari);
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja lähetillä,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.

	Kaikki muu kuninkaaseen liittyvä tarkistus tehdään eri paikassa*/
	int aloitusRivi = ruutu->getRivi();
	int aloitusSarake = ruutu->getSarake();
	int Xmoves[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	int Ymoves[8] = { 1, 0, -1, -1, 1, 1, 0, -1 };
	for (int i = 0; i < 8; i++) {
		int x = aloitusRivi + Xmoves[i];
		int y = aloitusSarake + Ymoves[i];
		if (x >= 0 && y >= 0 && x < 8 && y < 8 && (asema->_lauta[x][y] == nullptr || asema->_lauta[x][y]->getVari() != vari))
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(x, y)));
	}
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int aloitusRivi = ruutu->getRivi();
	int aloitusSarake = ruutu->getSarake();

	if (vari == (int)0) {
		if (aloitusRivi == 1) {
			if (asema->_lauta[2][aloitusSarake] == nullptr) {
				lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(2, aloitusSarake)));
				if (asema->_lauta[3][aloitusSarake] == nullptr)
					lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(3, aloitusSarake)));
			}
		}else if (asema->_lauta[aloitusRivi + 1][aloitusSarake] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi + 1, aloitusSarake)));
		if(asema->_lauta[aloitusRivi + 1][aloitusSarake + 1] != nullptr)
			if(asema->_lauta[aloitusRivi + 1][aloitusSarake + 1]->getVari() != vari)
				lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi + 1, aloitusSarake + 1)));
		if (asema->_lauta[aloitusRivi + 1][aloitusSarake - 1] != nullptr)
			if(asema->_lauta[aloitusRivi + 1][aloitusSarake - 1]->getVari() != vari)
				lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi + 1, aloitusSarake - 1)));
	}
	if (vari == (int)1) {
		if (aloitusRivi == 6) {
			if (asema->_lauta[5][aloitusSarake] == nullptr) {
				lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(5, aloitusSarake)));
				if (asema->_lauta[4][aloitusSarake] == nullptr)
					lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(4, aloitusSarake)));
			}
		}else if (asema->_lauta[aloitusRivi - 1][aloitusSarake] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi - 1, aloitusSarake)));
		if (asema->_lauta[aloitusRivi - 1][aloitusSarake - 1] != nullptr)
			if(asema->_lauta[aloitusRivi - 1][aloitusSarake - 1]->getVari() != vari)
				lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi - 1, aloitusSarake - 1)));
		if (asema->_lauta[aloitusRivi - 1][aloitusSarake + 1] != nullptr)
			if(asema->_lauta[aloitusRivi - 1][aloitusSarake + 1]->getVari() != vari)
				lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi - 1, aloitusSarake + 1)));
	}
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
