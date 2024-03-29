#pragma once

#include <list>
#include <string>
#include "asema.h"
#include "siirto.h"


// Vakioarvot nappulatyypeille.
enum
{
	VT, VR, VL, VD, VK, VS,
	MT, MR, ML, MD, MK, MS
};


// Yliluokka shakkinappuloille.
class Nappula
{

private:
	std::wstring	_unicode;	// nappulaa vastaava unicode-merkki
	int				_vari;		// valkea = 0, musta = 1
	int				_koodi;		// VT, VR, MT tms.
	double			_arvo;

public:
	Nappula(std::wstring, short int, short  int, short  int);
	Nappula() { }

	// Siirtojen generointi. Puhdas virtuaalifunktio, eli aliluokat toteuttavat t�m�n
	// omalla tavallaan.
	virtual void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, short int vari) = 0;

	void setUnicode(std::wstring unicode) { _unicode = unicode; }
	std::wstring getUnicode() { return _unicode; }
	void setVari(short int vari) { _vari = vari; }
	short int getVari() { return _vari; }
	short int getKoodi() { return _koodi; }
	double getArvo() { return _arvo; }
	void setKoodi(short int koodi) { _koodi = koodi; }
};

// Torni-aliluokka. Virtuaalinen perint� tarkoittaa, ett� kantaluokka perit��n moniperinn�ss� vain kerran
// (koska daami perii sek� tornin ett� l�hetin).
class Torni : public virtual Nappula {
public:
	Torni(std::wstring unicode, short int vari, short int koodi, short int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, short int vari);
};

// Ratsu-aliluokka.
class Ratsu : public Nappula {
public:
	Ratsu(std::wstring unicode, short int vari, short int koodi, short int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, short int vari);
};

// L�hetti-aliluokka. Virtuaalinen perint� tarkoittaa, ett� kantaluokka perit��n moniperinn�ss� vain kerran
// (koska daami perii sek� tornin ett� l�hetin).
class Lahetti : public virtual Nappula {
public:
	Lahetti(std::wstring unicode, short int vari, short int koodi, short int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, short int vari);
};

// Daami-aliluokka. Perii sek� l�hetin ett� tornin.
class Daami : public Lahetti, public Torni {
public:
	Daami(std::wstring unicode, short int vari, short int koodi, short int arvo) :
		Nappula(unicode, vari, koodi, arvo), Lahetti(unicode, vari, koodi, arvo), Torni(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, short int vari);
};

// Kuningas-aliluokka.
class Kuningas : public Nappula {
public:
	Kuningas(std::wstring unicode, short int vari, short int koodi, short int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, short int vari);
};

// Sotilas-aliluokka.
class Sotilas : public Nappula {
public:
	Sotilas(std::wstring unicode, short int vari, short int koodi, short int arvo) : Nappula(unicode, vari, koodi, arvo) {}
	void annaSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, short int vari);
private:
	void lisaaSotilaanKorotukset(Siirto, std::list<Siirto>& lista, short int vari);
};


