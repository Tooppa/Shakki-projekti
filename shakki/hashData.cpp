#include "hashData.h"

HashData::HashData() : HashData(0, MinMaxPaluu(), -1)
{

}

HashData::HashData(int syvyys, MinMaxPaluu parasSiirto, int tyyppi)
{
	_syvyys = syvyys;
	_parasSiirto = parasSiirto;
	_tyyppi = tyyppi;
}

HashData::~HashData()
{

}