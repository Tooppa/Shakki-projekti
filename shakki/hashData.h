#pragma once
#include <string>
#include "minmaxpaluu.h"

using namespace std;

class HashData
{
public:
	HashData();
	HashData( int syvyys, MinMaxPaluu parasSiirto);
	~HashData();

	int _syvyys;
	MinMaxPaluu _parasSiirto;
};