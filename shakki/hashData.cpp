#include "hashData.h"

HashData::HashData() : HashData(0, MinMaxPaluu())
{

}

HashData::HashData(int syvyys, MinMaxPaluu parasSiirto)
{
	_syvyys = syvyys;
	_parasSiirto = parasSiirto;
}

HashData::~HashData()
{

}