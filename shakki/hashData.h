#pragma once
#include <string>
#include "minmaxpaluu.h"

using namespace std;

class HashData
{
public:
	HashData();
	HashData( int syvyys, MinMaxPaluu parasSiirto, int tyyppi, int vari);
	~HashData();

	int _syvyys;
	MinMaxPaluu _parasSiirto;
	int _tyyppi;
	int _vari;
};