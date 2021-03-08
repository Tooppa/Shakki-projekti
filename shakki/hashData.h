#pragma once
#include <string>
#include "minmaxpaluu.h"

using namespace std;

class HashData
{
public:
	HashData();
	HashData( short int syvyys, MinMaxPaluu parasSiirto, short int vari);
	~HashData();

	short int _syvyys;
	MinMaxPaluu _parasSiirto;
	short int _vari;
};