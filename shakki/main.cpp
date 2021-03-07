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
	Kayttoliittyma* k = Kayttoliittyma::getInstance();
	int lopetus = 100;
	Asema asema;
	list<Siirto> lista;
	system("cls");

	// alphabetan alku syvyys ja max aika. t�m� menee k�yt�nn�ss� aina yli noin 20 sek omalla koneella
	int maxAika = 5;
	int alkuSyvyys;

	k->_maxAika = maxAika;
	k->aseta_asema(&asema);
	wcout << "Tervetuloa pelaamaan! \nSiirrot muodossa g2-g3, ra1-a2 ja korotukset \ng2-g1=R (muista isot kirjaimet lopussa)\n\n";
	Peli peli(k->kysyVastustajanVari());
	int koneenVari = peli.getKoneenVari();

	while (lopetus != 0) {
		lista.clear();
		k->piirraLauta();
		wcout << "\n";
		// Tarkasta onko peli loppu?
		asema.annaLaillisetSiirrot(lista);
		if (lista.size() == 0) {
			lopetus = 0;
			wcout << "Peli loppui";
			continue;
		}
		Siirto siirto;
		//if (asema.getSiirtovuoro() == koneenVari) {
		alkuSyvyys = 1;

		k->_counter = 0; // asetetaan siirtojen lasku nollaan
		chrono::steady_clock::time_point begin = chrono::steady_clock::now();
		k->_aika = begin; // asetetaan asemaan haun alku aika
		std::list<MinMaxPaluu> paluu;
		// testaillaan yksi syvyys kerralla kunnes aika loppuu
		// sama on alphabeta kaavassa. se kaava ottaa alku ja max ajan k�ytt�liittym�st� instancin avulla
		while (chrono::steady_clock::now() - begin <= std::chrono::seconds(maxAika))
		{
			wcout << "syvyydess�: " << alkuSyvyys;
			paluu.push_back(asema.alphaBeta(alkuSyvyys));
			alkuSyvyys++;
		}
		paluu.pop_back(); // poistetaan viiminen keskener�inen siirto
		siirto = paluu.back()._parasSiirto;
		chrono::steady_clock::time_point end = chrono::steady_clock::now();

		wcout
			<< "evaluaatio: " << paluu.back()._evaluointiArvo
			<< " ja " << Kayttoliittyma::getInstance()->_counter
			<< " testattua siirtoa.\naika: "
			<< chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000.0
			<< "/s syvyydess� " << alkuSyvyys - 1 << endl << endl; // alkusyvyys -1 koska vika oli keskener�inen
		paluu.clear();
	/*}
	else {
		siirto = Kayttoliittyma::getInstance()->
			annaVastustajanSiirto(asema);
	}*/
		asema.paivitaAsema(&siirto);
	}


	return 0;
}
