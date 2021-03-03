#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
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
	int syvyys = 3;
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
			MinMaxPaluu paluu;
			// kierroksen 10 jälkeen vähän tarkempi alpha beta
			if (kierros > 20) syvyys = 4;
			paluu = asema.alphaBeta(syvyys);
			siirto = paluu._parasSiirto;
			wcout << "evaluaatio: " << paluu._evaluointiArvo << endl;
		}
		else {
			siirto = Kayttoliittyma::getInstance()->
				annaVastustajanSiirto();
		}
		asema.paivitaAsema(&siirto);
	}


	return 0;
}
