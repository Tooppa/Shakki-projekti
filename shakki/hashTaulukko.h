#pragma once
#include <unordered_map>
#include "hashData.h"

using namespace std;

class HashTaulukko
{
public:
	HashTaulukko();
	~HashTaulukko();

	void Add(uint64_t hash, HashData item);

	bool Exist(uint64_t hash);

	HashData Get(uint64_t hash);

	void Clear();

private:
	unordered_map<uint64_t, HashData> _hashTaulu;
};