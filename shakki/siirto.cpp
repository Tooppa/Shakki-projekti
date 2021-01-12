#include "siirto.h"


Siirto::Siirto(Ruutu _alkuRuutu, Ruutu _loppuRuutu)
{
}


Siirto::Siirto(bool _lyhytLinna, bool _pitkaLinna) 
{
	
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
	return 0;
}


bool Siirto::onkoPitkälinna() 
{
	return 0;
}
