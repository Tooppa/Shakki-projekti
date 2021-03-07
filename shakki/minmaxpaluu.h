#pragma once
#include "siirto.h"


// luokka, jonka avulla saadaan palautettua minmax:ssa sekä siirto-olio että evaluointifunktion arvo
// Struct ajaisi saman asian. Kun ei rakenneta gettereitä ja settereitä, niin ei tarvita toteutus .cpp tiedostoa
class MinMaxPaluu {
public:
	double _evaluointiArvo = 0;
	Siirto _parasSiirto = Siirto();
	bool _matissa = false;
};
