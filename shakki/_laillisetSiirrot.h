#pragma once
#include <string>
#include <list>
#include "nappula.h"
#include "ruutu.h"
#include "Siirto.h"
#include "asema.h"

class Asema;

class LaillisetSiirrot{
public:
	LaillisetSiirrot() {};
	void annaLaillisetSiirrot(Asema*, std::list<Siirto>& lista);
	void annaTorninLaillisetSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
	void annaLahetinLaillisetSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
	void annaDaaminLaillisetSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
	void annaKuninkaanLaillisetSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
	void annaRatsunLaillisetSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
	void annaSotilaanLaillisetSiirrot(std::list<Siirto>& lista, Ruutu*, Asema*, int vari);
	void annaLinnoitusSiirrot(std::list<Siirto>& lista, Asema*, int vari);
	void huolehdiKuninkaanShakeista(std::list<Siirto>& lista, Asema*, int vari); // poistaa listasta siirrot jotka vievät kuninkaan shakkiin
	bool onkoRuutuUhattu(Ruutu*, Asema*, int vastustajanVari);
private:
	void lisaaSotilaanKorotukset(Siirto*, std::list<Siirto>& lista, Asema*);
};