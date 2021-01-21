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
	for (int i = ruutu->getRivi(); i < 8; i++){
		if (asema->_lauta[i][aloitusSarake] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, aloitusSarake)));
		else if (asema->_lauta[i][aloitusRivi]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, aloitusSarake)));
		}	
		else break;
	}
	for (int i = ruutu->getRivi(); i >= 0; i--) {
		if (asema->_lauta[i][aloitusSarake] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, aloitusSarake)));
		else if (asema->_lauta[i][aloitusRivi]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(i, aloitusSarake)));
		}
		else break;
	}
	for (int i = ruutu->getSarake(); i < 8; i++) {
		if (asema->_lauta[aloitusRivi][i] == nullptr)
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi, i)));
		else if (asema->_lauta[i][aloitusRivi]->getVari() != vari) {
			lista.push_back(Siirto(Ruutu(aloitusRivi, aloitusSarake), Ruutu(aloitusRivi, i)));
			break;
		}
		else break;
	}
	for (int i = ruutu->getSarake(); i >= 0; i--) {
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
	
}


void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	/*perusidea on että kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja lähetillä,
	oman nappulan päälle ei voi mennä ja vastustajan nappulan voi syödä.

	Kaikki muu kuninkaaseen liittyvä tarkistus tehdään eri paikassa*/


	
}


void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	
}


void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	
}
