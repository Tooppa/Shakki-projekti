#pragma once
#include <string>


// Vastustajan tiedot.
class Vastustaja
{
public:
	Vastustaja(std::wstring);
	std::wstring getNimimerkki();

private:
	std::wstring _nimimerkki;
};
