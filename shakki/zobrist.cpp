#include "zobrist.h"

bool ZobristHash::_isInit = false;
uint64_t ZobristHash::_castlingTable[4];
uint64_t ZobristHash::_randomLauta[8][8][12];

ZobristHash::ZobristHash()
{
	if (!_isInit)
	{
		std::random_device randomDevice;
		std::mt19937_64 gen64bit(randomDevice());
		std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);

		for (short int x = 0; x < 8; x++)
		{
			for (short int y = 0; y < 8; y++)
			{
				for (short int i = 0; i < 12; i++)
				{
					_randomLauta[x][y][i] = dis(gen64bit);
				}
			}
		}
		_isInit = true;
	}
}

ZobristHash::~ZobristHash()
{

}

uint64_t ZobristHash::GetHash(Nappula* lauta[8][8], bool castlingArray[4])
{
	uint64_t hash = 0;

	for (short int i = 0; i < 8; i++)
	{
		for (short int j = 0; j < 8; j++)
		{
			if (lauta[i][j])
			{
				short int pieceValue = nappulanArvo(lauta[i][j]->getKoodi());
				hash ^= _randomLauta[i][j][pieceValue];
			}
		}
	}
	for (short int i = 0; i < 4; i++)
	{
		if (castlingArray[i])
			hash ^= _castlingTable[i];
	}

	return hash;
}

short int ZobristHash::nappulanArvo(char nappulaKoodi)
{
	switch (nappulaKoodi)
	{
	case(VS): return 0;
	case(MS): return 1;
	case(VT): return 2;
	case(MT): return 3;
	case(VR): return 4;
	case(MR): return 5;
	case(VL): return 6;
	case(ML): return 7;
	case(VD): return 8;
	case(MD): return 9;
	case(VK): return 10;
	case(MK): return 11;
	}
}