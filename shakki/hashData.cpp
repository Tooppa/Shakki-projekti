#include "hashData.h"

HashData::HashData() : HashData(0, MinMaxPaluu(), -1, -1)
{

}

HashData::HashData(int syvyys, MinMaxPaluu parasSiirto, int tyyppi, int vari)
{
	_syvyys = syvyys;
	_parasSiirto = parasSiirto;
	_tyyppi = tyyppi;
	_vari = vari;
}

HashData::~HashData()
{

}