#include "vastustaja.h"
using namespace std;


Vastustaja::Vastustaja(wstring nimimerkki)
{
	this->_nimimerkki = nimimerkki;
}


wstring Vastustaja::getNimimerkki()
{
	return _nimimerkki;
}
