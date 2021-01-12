#pragma once


// Peli tietokonetta vastaan joko mustilla tai valkeilla.
class Peli
{
public:
	Peli(int);
	int getKoneenVari();

private:
	int _koneenVari; // Valkoinen = 0, Musta = 1
};
