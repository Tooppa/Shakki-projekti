#include "ruutu.h"


Ruutu::Ruutu(int sarake, int rivi)
{
	_rivi = rivi;
	_sarake = sarake;
}



int Ruutu::getRivi()
{
	return _rivi;
}


int Ruutu::getSarake()
{
	return _sarake;
}


void Ruutu::setRivi(int rivi)
{
	_rivi = rivi;
}


void Ruutu::setSarake(int sarake)
{
	_sarake = sarake;
}
