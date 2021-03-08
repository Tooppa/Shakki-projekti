#pragma once
#include <random>
#include "asema.h"
#include "nappula.h"

using namespace std;

class ZobristHash
{
public:
	ZobristHash();
	~ZobristHash();

	uint64_t GetHash(Nappula* boardArray[8][8], bool castlingArray[4]);
private:
	static uint64_t _randomLauta[8][8][12];
	static uint64_t _castlingTable[4];
	static bool _isInit;

	short int nappulanArvo(char pieceID);
};