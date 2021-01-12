#pragma once
#include "laillisetSiirrot.h"
class Evaluointi {
public:
	double evaluoi(Asema*, LaillisetSiirrot*);
private:
	double laskeNappuloidenArvo(Asema*, int);
	bool onkoAvausTaiKeskipeli(Asema*, int);
	double nappuloitaKeskella(Asema*, int);
	double linjat(Asema*, int, LaillisetSiirrot*);
};
