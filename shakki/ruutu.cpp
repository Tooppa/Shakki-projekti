#include "ruutu.h"


Ruutu::Ruutu(short int sarake, short int rivi)
{
	_rivi = rivi;
	_sarake = sarake;
}



short int Ruutu::getRivi()
{
	return _rivi;
}


short int Ruutu::getSarake()
{
	return _sarake;
}


void Ruutu::setRivi(short int rivi)
{
	_rivi = rivi;
}


void Ruutu::setSarake(short int sarake)
{
	_sarake = sarake;
}
