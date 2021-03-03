#include "peli.h"

using namespace std;


Peli::Peli(int ihmisenVari)
{
	if (ihmisenVari == 1)
		_koneenVari = 0;
	else
		_koneenVari = 1;
}


int Peli::getKoneenVari() {
	return _koneenVari;
}
