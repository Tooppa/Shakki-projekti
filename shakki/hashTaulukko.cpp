#include "hashTaulukko.h"

HashTaulukko::HashTaulukko()
{

}

HashTaulukko::~HashTaulukko()
{

}

void HashTaulukko::Add(uint64_t hash, HashData item)
{
	_hashTaulu[hash] = item;
}

bool HashTaulukko::Exist(uint64_t hash)
{
	if (_hashTaulu.find(hash) == _hashTaulu.end())
		return false;
	return true;
}

HashData HashTaulukko::Get(uint64_t hash)
{
	return _hashTaulu[hash];
}

void HashTaulukko::Clear()
{
	_hashTaulu.clear();
}