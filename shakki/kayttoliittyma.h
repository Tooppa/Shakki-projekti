#pragma once
#include "asema.h"
#include "nappula.h"
#include "peli.h"
#include "siirto.h"
#include "hashTaulukko.h"
#include <chrono>


// Shakkiohjelman käyttöliittymä, joka osaa visualisoida nykyisen aseman
// ja lukea käyttäjän syöttämät siirrot. Singleton.
class Kayttoliittyma
{
public:

	void aseta_asema(Asema* asema) { this->_asema = asema; }
	void piirraLauta();
	Siirto annaVastustajanSiirto(Asema asema);
	short int kysyVastustajanVari();
	short int koordinaattiKirjainNumeroksi(char kirjain);

	static Kayttoliittyma* getInstance();
	uint64_t _counter;
	HashTaulukko _transpositiot;
	chrono::steady_clock::time_point _aika;
	short int _maxAika;
private:

	Asema* _asema;
	static Kayttoliittyma* instance; // osoitin luokan ainoaan olioon (Singleton).
	char _kirjaimet[8] = { 'a','b','c','d','e','f','g','h' };

	Kayttoliittyma() {}
	Kayttoliittyma(Asema* asema) { this->_asema = asema; }
};
