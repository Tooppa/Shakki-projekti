#pragma once


// Peli tietokonetta vastaan joko mustilla tai valkeilla.
class Peli
{
public:
	Peli(short int);
	short int getKoneenVari();

private:
	short int _koneenVari; // Valkoinen = 0, Musta = 1
};
