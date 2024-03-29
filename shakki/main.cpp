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

short int main()
{
	Kayttoliittyma* k = Kayttoliittyma::getInstance();
	short int lopetus = 100;
	Asema asema;
	list<Siirto> lista;
	system("cls");

	// alphabetan alku syvyys ja max aika. tämä menee käytännössä aina yli noin 20 sek omalla koneella
	short int maxAika = 10;
	short int alkuSyvyys;

	k->_maxAika = maxAika;
	k->aseta_asema(&asema);
	wcout << "Tervetuloa pelaamaan! \nSiirrot muodossa g2-g3, ra1-a2 ja korotukset \ng2-g1=R (muista isot kirjaimet lopussa)\n\n";
	Peli peli(k->kysyVastustajanVari());
	short int koneenVari = peli.getKoneenVari();

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
		alkuSyvyys = 0;

		k->_counter = 0; // asetetaan siirtojen lasku nollaan
		chrono::steady_clock::time_point begin = chrono::steady_clock::now();
		k->_aika = begin; // asetetaan asemaan haun alku aika
		std::list<MinMaxPaluu> paluu;
		// testaillaan yksi syvyys kerralla kunnes aika loppuu
		// sama on alphabeta kaavassa. se kaava ottaa alku ja max ajan käyttöliittymästä instancin avulla
		alkuSyvyys++;
		paluu.push_back(asema.alphaBeta(alkuSyvyys));

		while (chrono::steady_clock::now() - begin <= std::chrono::seconds(maxAika) && !paluu.empty() && paluu.back()._matissa == false)
		{
			alkuSyvyys++;
			paluu.push_back(asema.alphaBeta(alkuSyvyys));
		}
		if (paluu.back()._matissa == false) {
			paluu.pop_back(); // poistetaan viiminen keskeneräinen siirto
			alkuSyvyys--;
		}

		if (alkuSyvyys % 2 == 1) {
			paluu.pop_back();
			alkuSyvyys--;
		}

		siirto = paluu.back()._parasSiirto;
		chrono::steady_clock::time_point end = chrono::steady_clock::now();

		wcout
			<< "evaluaatio: " << paluu.back()._evaluointiArvo
			<< " ja " << Kayttoliittyma::getInstance()->_counter
			<< " testattua siirtoa.\naika: "
			<< chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000.0
			<< "/s syvyydessä " << alkuSyvyys << endl << endl; // alkusyvyys -1 koska vika oli keskeneräinen
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
