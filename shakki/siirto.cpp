#include "siirto.h"


Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu)
{
	_alkuRuutu = alkuRuutu;
	_loppuRuutu = loppuRuutu;
	_lyhytLinna = false;
	_pitkaLinna = false;
}


Siirto::Siirto(bool lyhytLinna, bool pitkaLinna) 
{
	_lyhytLinna = lyhytLinna;
	_pitkaLinna = pitkaLinna;

	// w�rk in pr�gress
	if (_pitkaLinna) 
	{
		Siirto();
		Siirto();
	}
}


Ruutu Siirto::getAlkuruutu()
{
	return _alkuRuutu;
}


Ruutu Siirto::getLoppuruutu()
{
	return _loppuRuutu;
}


bool Siirto::onkoLyhytLinna() 
{
	return _lyhytLinna;
}


bool Siirto::onkoPitk�linna() 
{
	return _pitkaLinna;
}
