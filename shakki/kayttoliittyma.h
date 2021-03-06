#pragma once
#include "asema.h"
#include "nappula.h"
#include "peli.h"
#include "siirto.h"
#include "hashTaulukko.h"
#include <chrono>


// Shakkiohjelman k�ytt�liittym�, joka osaa visualisoida nykyisen aseman
// ja lukea k�ytt�j�n sy�tt�m�t siirrot. Singleton.
class Kayttoliittyma
{
public:

	void aseta_asema(Asema* asema) { this->_asema = asema; }
	void piirraLauta();
	Siirto annaVastustajanSiirto(Asema asema);
	int kysyVastustajanVari();
	int koordinaattiKirjainNumeroksi(char kirjain);

	static Kayttoliittyma* getInstance();
	uint64_t _counter;
	HashTaulukko _transpositiot;
	chrono::steady_clock::time_point _aika;
	int _maxAika;
private:

	Asema* _asema;
	static Kayttoliittyma* instance; // osoitin luokan ainoaan olioon (Singleton).
	char _kirjaimet[8] = { 'a','b','c','d','e','f','g','h' };

	Kayttoliittyma() {}
	Kayttoliittyma(Asema* asema) { this->_asema = asema; }
};
