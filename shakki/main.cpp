#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <chrono>
#include "kayttoliittyma.h"
#include "Siirto.h"
#include "asema.h"

using namespace std;

int main()
{
	wcout << "HeippariShakki\n";
	wcout << "Tervetuloa pelaamaan!\n";
	int lopetus = 100;
	Asema asema;
	Kayttoliittyma::getInstance()->aseta_asema(&asema);

	Peli peli(Kayttoliittyma::getInstance()->
		kysyVastustajanVari());
	list<Siirto> lista;
	system("cls");
	int koneenVari = peli.getKoneenVari();
	// alphabetan alku syvyys
	int syvyys = 4;
	int kierros = 0;

	while (lopetus != 0) {
		kierros++;
		lista.clear();
		Kayttoliittyma::getInstance()->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		if (lista.size() == 0) {
			lopetus = 0;
			wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		if (asema.getSiirtovuoro() == koneenVari) {
			Kayttoliittyma::getInstance()->_counter = 0;
			chrono::steady_clock::time_point begin = chrono::steady_clock::now();
			MinMaxPaluu paluu;
			// kierroksen 20 jälkeen vähän tarkempi alpha beta
			if (kierros > 20) syvyys = 5;
			paluu = asema.alphaBeta(syvyys);
			siirto = paluu._parasSiirto;
			chrono::steady_clock::time_point end = chrono::steady_clock::now();

			wcout
				<< "evaluaatio: " << paluu._evaluointiArvo 
				<< " ja " << Kayttoliittyma::getInstance()->_counter 
				<< " testattua siirtoa.\naika: " 
				<< chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000000.0
				<< "/s" << endl << endl;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}
		asema.paivitaAsema(&siirto);
	}


	return 0;
}
