#include "hashData.h"

HashData::HashData() : HashData(0, MinMaxPaluu(), -1)
{

}

HashData::HashData(short int syvyys, MinMaxPaluu parasSiirto, short int tyyppi)
{
	_syvyys = syvyys;
	_parasSiirto = parasSiirto;
	_vari = tyyppi;
}

HashData::~HashData()
{

}