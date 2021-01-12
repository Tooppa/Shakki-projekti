#include "laillisetSiirrot.h"
#include <iostream>
/*K‰y asema olion kaksiulotteisen taulukon x ja y suuntaiset ruudut l‰pi sek‰ isompaan ett‰ pienemp‰‰n p‰in ja tarkista seuraavat asiat
1) Ruutu tyhj‰, voi menn‰
2) Ruudussa oma nappula, ei voi menn‰
3) Ruudussa vastustajan nappula, voi menn‰ mutta pidemm‰lle ei voi menn‰

Saa parametrinaan listan johon lis‰ys tehd‰‰n
*/




void LaillisetSiirrot::annaTorninLaillisetSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	lahtoruudunNappulanVari = asema->lauta[lahtoruutuX][lahtoruutuY]->getVari();
	// vaakarivi ruudusta eteenp‰in
	for (int i = lahtoruutuX + 1; i < 8; i++) {
		// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
		if (asema->lauta[i][lahtoruutuY] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));
		}
		else if (asema->lauta[i][lahtoruutuY] != NULL) {
			// Jos oma nappula niin poistutaan for silmukasta. Ei lis‰t‰ listaan
			// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
			tuloruudunNappulanVari = asema->lauta[i][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));
				break;
			}
		}
	}
	// vaakarivi ruudusta taaksep‰in
	for (int i = lahtoruutuX - 1; i >= 0; i--) {
		// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
		if (asema->lauta[i][lahtoruutuY] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));
		}
		else if (asema->lauta[i][lahtoruutuY] != NULL) {
			// Jos oma nappula niin poistutaan for silmukasta. Ei lis‰t‰ listaan
			// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
			tuloruudunNappulanVari = asema->lauta[i][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(i, lahtoruutuY)));
				break;
			}
		}
	}
	// pystyrivi ruudusta eteenp‰in
	for (int i = lahtoruutuY + 1; i < 8; i++) {
		// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
		if (asema->lauta[lahtoruutuX][i] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
		}
		else if (asema->lauta[lahtoruutuX][i] != NULL) {
			// Jos oma nappula niin poistutaan for silmukasta. Ei lis‰t‰ listaan
			// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX][i]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
				break;
			}
		}
	}
	// pystyrivi ruudusta taaksep‰in
	for (int i = lahtoruutuY - 1; i >= 0; i--) {
		// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
		if (asema->lauta[lahtoruutuX][i] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
		}
		else if (asema->lauta[lahtoruutuX][i] != NULL) {
			// Jos oma nappula niin poistutaan for silmukasta. Ei lis‰t‰ listaan
			// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX][i]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
				break;
			}
		}
	}
	// testausta varten
	// Huom. uuden standardin mukaista c++ koodia, auto-m‰‰re antaa k‰‰nt‰j‰n p‰‰tell‰ luokan, k‰ytt‰‰ iteraattoreita
	/*for (auto s : lista)
	{
		std::wcout << L"Torni";
		std::wcout << s.getAlkuruutu().getSarake();
		std::wcout << s.getAlkuruutu().getRivi() << "-";

		std::wcout << s.getLoppuruutu().getSarake();
		std::wcout << s.getLoppuruutu().getRivi() << "\n";
	}*/

}
void LaillisetSiirrot::annaLahetinLaillisetSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {

	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	int j;

	lahtoruudunNappulanVari = asema->lauta[lahtoruutuX][lahtoruutuY]->getVari();

	// viistorivi ruudusta oikealle ylˆs
	for (int i = lahtoruutuX + 1; i < 8; i++) {
		// j arvo asetetaan vain silmukan ensimm‰isell‰ kierroksella alkuarvoon
		if (i == lahtoruutuX + 1) {
			j = lahtoruutuY + 1;
		}
		if (j < 0 || j > 7 || i < 0 || i > 7) {
			break;
		}
		// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
		if (asema->lauta[i][j] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
		}
		else if (asema->lauta[i][j] != NULL) {
			// Jos oma nappula niin poistutaan for silmukasta. Ei lis‰t‰ listaan
			// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
			tuloruudunNappulanVari = asema->lauta[i][j]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
				break;
			}

		}
		j++;
	}

	// viistorivi ruudusta oikealle alas
	for (int i = lahtoruutuX + 1; i < 8; i++) {
		// j arvo asetetaan vain silmukan ensimm‰isell‰ kierroksella alkuarvoon
		if (i == lahtoruutuX + 1) {
			j = lahtoruutuY - 1;
		}
		if (j < 0 || j > 7 || i < 0 || i > 7) {
			break;
		}
		// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
		if (asema->lauta[i][j] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
		}
		else if (asema->lauta[i][j] != NULL) {
			// Jos oma nappula niin poistutaan for silmukasta. Ei lis‰t‰ listaan
			// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
			tuloruudunNappulanVari = asema->lauta[i][j]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
				break;
			}
		}

		j--;
	}

	// viistorivi ruudusta vasemmalle ylˆs
	for (int i = lahtoruutuX - 1; i >= 0; i--) {
		// j arvo asetetaan vain silmukan ensimm‰isell‰ kierroksella alkuarvoon
		if (i == lahtoruutuX - 1) {
			j = lahtoruutuY + 1;
		}
		if (j < 0 || j > 7 || i < 0 || i > 7) {
			break;
		}
		// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
		if (asema->lauta[i][j] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
		}
		else if (asema->lauta[i][j] != NULL) {
			// Jos oma nappula niin poistutaan for silmukasta. Ei lis‰t‰ listaan
			// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
			tuloruudunNappulanVari = asema->lauta[i][j]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
				break;
			}
		}

		j++;
	}
	// viistorivi ruudusta vasemmalle alas
	for (int i = lahtoruutuX - 1; i >= 0; i--) {
		// j arvo asetetaan vain silmukan ensimm‰isell‰ kierroksella alkuarvoon
		if (i == lahtoruutuX - 1) {
			j = lahtoruutuY - 1;
		}
		if (j < 0 || j > 7 || i < 0 || i > 7) {
			break;
		}
		// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
		if (asema->lauta[i][j] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
		}
		else if (asema->lauta[i][j] != NULL) {
			// Jos oma nappula niin poistutaan for silmukasta. Ei lis‰t‰ listaan
			// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
			tuloruudunNappulanVari = asema->lauta[i][j]->getVari();
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				break;
			}
			// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(i, j)));
				break;
			}
		}

		j--;
	}
	// testausta varten
	// Huom. uuden standardin mukaista c++ koodia, auto-m‰‰re antaa k‰‰nt‰j‰n p‰‰tell‰ luokan, k‰ytt‰‰ iteraattoreita
	/*for (auto s : lista)
	{
		std::wcout << L"L‰hetti";
		std::wcout << s.getAlkuruutu().getSarake();
		std::wcout << s.getAlkuruutu().getRivi() << "-";

		std::wcout << s.getLoppuruutu().getSarake();
		std::wcout << s.getLoppuruutu().getRivi() << "\n";
	}*/
}
void LaillisetSiirrot::annaDaaminLaillisetSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	this->annaLahetinLaillisetSiirrot(lista, ruutu, asema, vari);
	this->annaTorninLaillisetSiirrot(lista, ruutu, asema, vari);
	/*for (auto s : lista)
	{
		std::wcout << L"Daami";
		std::wcout << s.getAlkuruutu().getSarake();
		std::wcout << s.getAlkuruutu().getRivi() << "-";

		std::wcout << s.getLoppuruutu().getSarake();
		std::wcout << s.getLoppuruutu().getRivi() << "\n";
	}*/
}
void LaillisetSiirrot::annaRatsunLaillisetSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	lahtoruudunNappulanVari = asema->lauta[lahtoruutuX][lahtoruutuY]->getVari();

	// Pit‰‰ huomioida ett‰ kokeiltavat ruudut ovat viel‰ laudalla
	if (lahtoruutuX + 1 < 8 && lahtoruutuY + 2 < 8) {
		if (asema->lauta[lahtoruutuX + 1][lahtoruutuY + 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 2)));
		}
		else if (asema->lauta[lahtoruutuX + 1][lahtoruutuY + 2] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX + 1][lahtoruutuY + 2]->getVari();
			// jos oman v‰rinen niin lis‰t‰‰n tˆrmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 2)));
			}
		}
	}
	if (lahtoruutuX + 1 < 8 && lahtoruutuY - 2 >= 0) {
		if (asema->lauta[lahtoruutuX + 1][lahtoruutuY - 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 2)));
		}
		else if (asema->lauta[lahtoruutuX + 1][lahtoruutuY - 2] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX + 1][lahtoruutuY - 2]->getVari();
			// jos oman v‰rinen niin lis‰t‰‰n tˆrmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 2)));
			}
		}
	}
	if (lahtoruutuX - 1 >= 0 && lahtoruutuY + 2 < 8) {
		if (asema->lauta[lahtoruutuX - 1][lahtoruutuY + 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 2)));
		}
		else if (asema->lauta[lahtoruutuX - 1][lahtoruutuY + 2] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX - 1][lahtoruutuY + 2]->getVari();
			// jos oman v‰rinen niin lis‰t‰‰n tˆrmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 2)));
			}
		}
	}
	if (lahtoruutuX - 1 >= 0 && lahtoruutuY - 2 >= 0) {
		if (asema->lauta[lahtoruutuX - 1][lahtoruutuY - 2] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 2)));
		}
		else if (asema->lauta[lahtoruutuX - 1][lahtoruutuY - 2] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX - 1][lahtoruutuY - 2]->getVari();
			// jos oman v‰rinen niin lis‰t‰‰n tˆrmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 2)));
			}
		}
	}
	if (lahtoruutuX + 2 < 8 && lahtoruutuY + 1 < 8) {
		if (asema->lauta[lahtoruutuX + 2][lahtoruutuY + 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY + 1)));
		}
		else if (asema->lauta[lahtoruutuX + 2][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX + 2][lahtoruutuY + 1]->getVari();
			// jos oman v‰rinen niin lis‰t‰‰n tˆrmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY + 1)));
			}
		}
	}
	if (lahtoruutuX + 2 < 8 && lahtoruutuY - 1 >= 0) {
		if (asema->lauta[lahtoruutuX + 2][lahtoruutuY - 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY - 1)));
		}
		else if (asema->lauta[lahtoruutuX + 2][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX + 2][lahtoruutuY - 1]->getVari();
			// jos oman v‰rinen niin lis‰t‰‰n tˆrmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 2, lahtoruutuY - 1)));
			}
		}
	}
	if (lahtoruutuX - 2 >= 0 && lahtoruutuY + 1 < 8) {
		if (asema->lauta[lahtoruutuX - 2][lahtoruutuY + 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY + 1)));
		}
		else if (asema->lauta[lahtoruutuX - 2][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX - 2][lahtoruutuY + 1]->getVari();
			// jos oman v‰rinen niin lis‰t‰‰n tˆrmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY + 1)));
			}
		}
	}
	if (lahtoruutuX - 2 >= 0 && lahtoruutuY - 1 >= 0) {
		if (asema->lauta[lahtoruutuX - 2][lahtoruutuY - 1] == NULL) {
			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY - 1)));
		}
		else if (asema->lauta[lahtoruutuX - 2][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX - 2][lahtoruutuY - 1]->getVari();
			// jos oman v‰rinen niin lis‰t‰‰n tˆrmayslistaan
			if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
			}
			// jos vastujan nappula niin lis‰t‰‰n listaan
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 2, lahtoruutuY - 1)));
			}
		}
	}
	/*for (auto s : lista)
	{
		std::wcout << L"Ratsu";
		std::wcout << s.getAlkuruutu().getSarake();
		std::wcout << s.getAlkuruutu().getRivi() << "-";

		std::wcout << s.getLoppuruutu().getSarake();
		std::wcout << s.getLoppuruutu().getRivi() << "\n";
	}*/
}
void LaillisetSiirrot::annaKuninkaanLaillisetSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	/*perusidea on ett‰ kaikki viereiset ruudut ovat sallittuja. kuten tornilla ja l‰hetill‰,
	oman nappulan p‰‰lle ei voi menn‰ ja vastustajan nappulan voi syˆd‰.

	Kaikki muu kuninkaaseen liittyv‰ tarkistus tehd‰‰n eripaikassa*/


	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();

	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;

	lahtoruudunNappulanVari = asema->lauta[lahtoruutuX][lahtoruutuY]->getVari();


	// K‰yd‰‰n perussiirtojen tyhj‰t ruudut l‰pi 
	// Pit‰‰ tarkistaa ett‰ ehdokas ruutu viel‰ laudalla
	if (lahtoruutuX + 1 < 8) {
		if (asema->lauta[lahtoruutuX + 1][lahtoruutuY] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY)));


		}
		else if (asema->lauta[lahtoruutuX + 1][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX + 1][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY)));
			}


		}
	}

	if (lahtoruutuX + 1 < 8 && lahtoruutuY + 1 < 8) {
		if (asema->lauta[lahtoruutuX + 1][lahtoruutuY + 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));

		}
		else if (asema->lauta[lahtoruutuX + 1][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX + 1][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));

			}
		}
	}

	if (lahtoruutuX + 1 < 8 && lahtoruutuY - 1 >= 0) {
		if (asema->lauta[lahtoruutuX + 1][lahtoruutuY - 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));

		}
		else if (asema->lauta[lahtoruutuX + 1][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX + 1][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));

			}
		}
	}

	if (lahtoruutuX - 1 >= 0) {
		if (asema->lauta[lahtoruutuX - 1][lahtoruutuY] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY)));

		}
		else if (asema->lauta[lahtoruutuX - 1][lahtoruutuY] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX - 1][lahtoruutuY]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY)));

			}
		}
	}

	if (lahtoruutuX - 1 >= 0 && lahtoruutuY + 1 < 8) {
		if (asema->lauta[lahtoruutuX - 1][lahtoruutuY + 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)));

		}
		else if (asema->lauta[lahtoruutuX - 1][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX - 1][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)));

			}
		}
	}

	if (lahtoruutuX - 1 >= 0 && lahtoruutuY - 1 >= 0) {
		if (asema->lauta[lahtoruutuX - 1][lahtoruutuY - 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));

		}
		else if (asema->lauta[lahtoruutuX - 1][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX - 1][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));

			}
		}
	}

	if (lahtoruutuY + 1 < 8) {
		if (asema->lauta[lahtoruutuX][lahtoruutuY + 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));

		}
		else if (asema->lauta[lahtoruutuX][lahtoruutuY + 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX][lahtoruutuY + 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));

			}
		}
	}

	if (lahtoruutuY - 1 >= 0) {
		if (asema->lauta[lahtoruutuX][lahtoruutuY - 1] == NULL) {

			lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));

		}
		else if (asema->lauta[lahtoruutuX][lahtoruutuY - 1] != NULL) {
			tuloruudunNappulanVari = asema->lauta[lahtoruutuX][lahtoruutuY - 1]->getVari();
			if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {

				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));

			}
		}
	}
	
}
void LaillisetSiirrot::annaLinnoitusSiirrot(std::list<Siirto>& lista, Asema* asema, int vari) {

	//// Linnoituksien huomioiminen
	//// 1. Kuningas ei saa olla liikkunut
	//// 2. Torni ei saa olla liikkunut
	//// 3. Kuningas ei saa olla shakattuna
	//// 4. Ruutujen pit‰‰ olla tyhj‰t
	//// 5. Ruudut eiv‰t saa olla uhattuja
	if (vari == 0) {
		//valkean lyhyt linna
		if (!asema->getOnkoValkeaKuningasLiikkunut() && !asema->getOnkoValkeaKTliikkunut()
			&& onkoRuutuUhattu(&Ruutu(4, 0), asema, !vari)
			&& onkoRuutuUhattu(&Ruutu(5, 0), asema, !vari) && onkoRuutuUhattu(&Ruutu(6, 0), asema, !vari)
			&& asema->lauta[5][0] == NULL && asema->lauta[6][0] == NULL){
				//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(true, false)); // lis‰t‰‰n listaan lyhyt linna
		}
		//valkean pitk‰ linna
		if (!asema->getOnkoValkeaKuningasLiikkunut() && !asema->getOnkoValkeaDTliikkunut()
			&& onkoRuutuUhattu(&Ruutu(4, 0), asema, !vari)
			&& onkoRuutuUhattu(&Ruutu(3, 0), asema, !vari) && onkoRuutuUhattu(&Ruutu(3, 0), asema, !vari)
			&& asema->lauta[3][0] == NULL && asema->lauta[2][0] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(false, true)); // lis‰t‰‰n listaan lyhyt linna
		}
	}
	if (vari == 1) {
		//mustan lyhyt linna
		if (!asema->getOnkoMustaKuningasLiikkunut() && !asema->getOnkoMustaKTliikkunut()
			&& onkoRuutuUhattu(&Ruutu(4, 7), asema, !vari)
			&& onkoRuutuUhattu(&Ruutu(5, 7), asema, !vari) && onkoRuutuUhattu(&Ruutu(6, 7), asema, !vari)
			&& asema->lauta[5][7] == NULL && asema->lauta[6][7] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(true, false)); // lis‰t‰‰n listaan lyhyt linna
		}
		//mustan pitk‰ linna
		if (!asema->getOnkoMustaKuningasLiikkunut() && !asema->getOnkoMustaDTliikkunut()
			&& onkoRuutuUhattu(&Ruutu(4, 7), asema, !vari)
			&& onkoRuutuUhattu(&Ruutu(3, 7), asema, !vari) && onkoRuutuUhattu(&Ruutu(3, 7), asema, !vari)
			&& asema->lauta[3][7] == NULL && asema->lauta[2][7] == NULL) {
			//p‰ivitet‰‰n listaan lyhytlinna
			lista.push_back(Siirto(false, true)); // lis‰t‰‰n listaan lyhyt linna
		}
	}
}

void LaillisetSiirrot::annaSotilaanLaillisetSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	int lahtoruutuY = ruutu->getRivi();
	int lahtoruutuX = ruutu->getSarake();
	int lahtoruudunNappulanVari;
	int tuloruudunNappulanVari;
	lahtoruudunNappulanVari = asema->lauta[lahtoruutuX][lahtoruutuY]->getVari();

// jos sotilas rivill‰ 2 ja sotilas valkea tai sotilas rivill‰ 7 ja sotilas musta sill‰ on kaksois askel mahdollisuus
// muilla riveill‰ sotilaalla yksˆis aske
// sotilas voi myˆs syˆd‰ etuviistoon ruudustaan
// sotilas voi korottua jos se saavuttaa rivin 8 valkeilla ja vastaavasti rivin 1 mustilla

	// valkea rivill‰ 2
	if (lahtoruutuY == 1 && lahtoruudunNappulanVari == 0) {
		for (int i = lahtoruutuY + 1; i < lahtoruutuY + 3; i++) {
			// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
			if (asema->lauta[lahtoruutuX][i] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
			}
			else
				break;
		}
	}

	// musta rivill‰ 7
	if (lahtoruutuY == 6 && lahtoruudunNappulanVari == 1) {
		for (int i = lahtoruutuY - 1; i > lahtoruutuY - 3; i--) {
			// Jos tyhj‰ ruutu niin lis‰t‰‰n listaan
			if (asema->lauta[lahtoruutuX][i] == NULL) {
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, i)));
			}
			else
				break;
		}
	}
	// perusruudut valkeille 
	if ((lahtoruutuY == 2 || lahtoruutuY == 3 || lahtoruutuY == 4 || lahtoruutuY == 5 || lahtoruutuY == 6) && lahtoruudunNappulanVari == 0) {
		//siirtym‰t eteenp‰in
		if (asema->lauta[lahtoruutuX][lahtoruutuY + 1] == NULL) {
			if (lahtoruutuY < 6)
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)));
			else
				lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY + 1)), lista, asema);
		}
		//syˆnnit viistoon
		if (lahtoruutuX + 1 < 8) { // tarkastetaan ett‰ pysyt‰‰n laudalla
			if (asema->lauta[lahtoruutuX + 1][lahtoruutuY + 1] != NULL) {
				// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->lauta[lahtoruutuX +1][lahtoruutuY + 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
					if (lahtoruutuY < 6)
						lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)));
					else
						lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY + 1)), lista, asema);
				}
			}
		}
		if (lahtoruutuX - 1 >= 0) {
			if (asema->lauta[lahtoruutuX - 1][lahtoruutuY + 1] != NULL) {
				// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->lauta[lahtoruutuX - 1][lahtoruutuY + 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastustajan nappula niin lis‰t‰‰n listaan
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
					if (lahtoruutuY < 6)
						lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX -1 , lahtoruutuY + 1)));
					else
						lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY + 1)), lista, asema);
				}
			}
		}
	}
	// perusruudut mustille 
	if ((lahtoruutuY == 5 || lahtoruutuY == 4 || lahtoruutuY == 3 || lahtoruutuY == 2 || lahtoruutuY == 1) && lahtoruudunNappulanVari == 1) {
		//siirtym‰t eteenp‰in
		if (asema->lauta[lahtoruutuX][lahtoruutuY - 1] == NULL) {
			if (lahtoruutuY > 1)
				lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)));
			else
				lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX, lahtoruutuY - 1)), lista, asema);
		}
		//syˆnnit viistoon
		if (lahtoruutuX + 1 < 8) { // tarkastetaan ett‰ pysyt‰‰n laudalla
			if (asema->lauta[lahtoruutuX + 1][lahtoruutuY - 1] != NULL) {
				// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->lauta[lahtoruutuX + 1][lahtoruutuY -1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
					if (lahtoruutuY > 1)
						lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)));
					else
						lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX + 1, lahtoruutuY - 1)), lista, asema);
				}
			}
		}
		if (lahtoruutuX - 1 >= 0) {
			if (asema->lauta[lahtoruutuX - 1][lahtoruutuY - 1] != NULL) {
				// Tarkistetaan ett‰ jos l‰htˆruudussa olevan nappulan v‰ri on sama kuin tarkastelun alaisessa ruudussa, niin silloin on oma nappula
				tuloruudunNappulanVari = asema->lauta[lahtoruutuX - 1][lahtoruutuY - 1]->getVari();
				if (lahtoruudunNappulanVari == tuloruudunNappulanVari) {
				}
				// jos vastujan nappula niin poistutaan for silmukasta. Lis‰t‰‰n listaan
				if (lahtoruudunNappulanVari != tuloruudunNappulanVari) {
					if (lahtoruutuY > 1)
						lista.push_back(Siirto(*ruutu, Ruutu(lahtoruutuX - 1, lahtoruutuY - 1)));
					else
						lisaaSotilaanKorotukset(&Siirto(*ruutu, Ruutu(lahtoruutuX -1, lahtoruutuY - 1)), lista, asema);
				}
			}
		}
	}

	// Ohestalyˆnti on mahdollinen, jos jollain sarakkeella on viimeksi
	// tapahtunut sotilaan kaksoisaskel.
	if (asema->kaksoisaskelSarakkeella != -1)
	{
		if (vari == 0 && lahtoruutuY == 4)
		{
			if (asema->lauta[asema->kaksoisaskelSarakkeella][4] && asema->lauta[asema->kaksoisaskelSarakkeella][4]->getKoodi() == MS)
				lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 5)));
		}
		if (vari == 1 && lahtoruutuY == 3)
		{
			if (asema->lauta[asema->kaksoisaskelSarakkeella][3] && asema->lauta[asema->kaksoisaskelSarakkeella][3]->getKoodi() == VS)
				lista.push_back(Siirto(*ruutu, Ruutu(asema->kaksoisaskelSarakkeella, 2)));
		}
	}
}

//Palauttaa True jos ruutu on Ok eli ei uhattu
bool LaillisetSiirrot::onkoRuutuUhattu(Ruutu* ruutu, Asema* asema, int vastustajanVari) {
	std::list<Siirto> vastustajaSiirrotLista;
	//V‰reitt‰in k‰yd‰‰n l‰pi kaikki ruudut ja niiss‰ olevan nappulan siirrot ker‰t‰‰n vastustajan siirtolistaan
	if (vastustajanVari == 0) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (asema->lauta[i][j] == NULL) {
					continue;
				}
				if (asema->lauta[i][j]->getKoodi() == VK) {
					this->annaKuninkaanLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == VD) {
					this->annaDaaminLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == VT) {
					this->annaTorninLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == VL) {
					this->annaLahetinLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == VR) {
					this->annaRatsunLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == VS) {
					this->annaSotilaanLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
			}
		}
	}
	if (vastustajanVari == 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (asema->lauta[i][j] == NULL) {
					continue;
				}
				if (asema->lauta[i][j]->getKoodi() == MK) {
					this->annaKuninkaanLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == MD) {
					this->annaDaaminLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == MT) {
					this->annaTorninLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == ML) {
					this->annaLahetinLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == MR) {
					this->annaRatsunLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
				if (asema->lauta[i][j]->getKoodi() == MS) {
					this->annaSotilaanLaillisetSiirrot(vastustajaSiirrotLista, &Ruutu(i, j), asema, vastustajanVari);
				}
			}
		}
	}
	// K‰yd‰‰n vastustajaSiirtoLista l‰pi ja jos sielt‰ lˆytyy tarkasteltava ruutu niin tiedet‰‰n sen olevan uhattu
	bool ruutuOk = true;
	for (auto s : vastustajaSiirrotLista)
	{
		if (ruutu->getSarake() == s.getLoppuruutu().getSarake() && ruutu->getRivi() == s.getLoppuruutu().getRivi()) {
			ruutuOk = false;
			break;
		}
	}
	return ruutuOk;
}

void LaillisetSiirrot::huolehdiKuninkaanShakeista(std::list<Siirto>& lista, Asema* asema, int vari) {
	// k‰yd‰‰n saatua siirtolistaa l‰pi ja jos siell‰ oleva siirto asettaa kuninkaan shakkiin, niin siirto poistetaan listasta
	int kuninkaanX;
	int kuninkaanY;
	if (vari == 0) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (asema->lauta[i][j] == NULL)
					continue;
				if (asema->lauta[i][j]->getKoodi() == VK) {
					kuninkaanX = i;
					kuninkaanY = j;
					break;
				}
			}
		}
	}
	if (vari == 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (asema->lauta[i][j] == NULL)
					continue;
				if (asema->lauta[i][j]->getKoodi() == MK) {
					kuninkaanX = i;
					kuninkaanY = j;
					break;
				}
			}
		}
	}
	// Jotta ei jouduta perumaan oikeaan asemaan tehty‰ siirtoa
	Asema testiAsema;
	std::list<Siirto> siivottuSiirrotLista;
	for (auto s : lista) {
		testiAsema = *asema;
		testiAsema.paivitaAsema(&s);
		int x, y;

		// Kuninkaan siirto?
		if (s.onkoLyhytLinna())
		{
			x = 6;
			if (asema->getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else if (s.onkoPitk‰linna())
		{
			x = 2;
			if (asema->getSiirtovuoro() == 0)
				y = 0;
			else
				y = 7;
		}
		else
		{
			Nappula* siirtyva = asema->lauta[s.getAlkuruutu().getSarake()][s.getAlkuruutu().getRivi()];
			if (siirtyva->getKoodi() == VK || siirtyva->getKoodi() == MK)
			{
				x = s.getLoppuruutu().getSarake();
				y = s.getLoppuruutu().getRivi();
			}
			else
			{
				// Ei ole, kuninkaan sijainti sama kuin ennen siirron s kokeilua
				x = kuninkaanX;
				y = kuninkaanY;
			}
		}

		// huom !vari
		if (this->onkoRuutuUhattu(&Ruutu(x, y), &testiAsema, !vari) == true) {
			siivottuSiirrotLista.push_back(s);
		}
	}
	lista = siivottuSiirrotLista;
}
void LaillisetSiirrot::annaLaillisetSiirrot(Asema* asema, std::list<Siirto>& lista) {
	int vari = asema->getSiirtovuoro();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			//Ei kysele tyhjilt‰ ruuduilta nappulan nime‰
			if (asema->lauta[i][j] == NULL) {
				continue;
			}
			if (vari == 0) {
				if (asema->lauta[i][j]->getKoodi() == VK) {
					this->annaKuninkaanLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}

				if (asema->lauta[i][j]->getKoodi() == VD) {
					this->annaDaaminLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}

				if (asema->lauta[i][j]->getKoodi() == VT) {
					this->annaTorninLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}

				if (asema->lauta[i][j]->getKoodi() == VL) {
					this->annaLahetinLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}

				if (asema->lauta[i][j]->getKoodi() == VR) {
					this->annaRatsunLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}
				if (asema->lauta[i][j]->getKoodi() == VS) {
					this->annaSotilaanLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}
			}
		
			if (vari == 1) {

				if (asema->lauta[i][j]->getKoodi() == MK) {
					this->annaKuninkaanLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}
				if (asema->lauta[i][j]->getKoodi() == MD) {
					this->annaDaaminLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}
				if (asema->lauta[i][j]->getKoodi() == MT) {
					this->annaTorninLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}
				if (asema->lauta[i][j]->getKoodi() == ML) {
					this->annaLahetinLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}
				if (asema->lauta[i][j]->getKoodi() == MR) {
					this->annaRatsunLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}
				if (asema->lauta[i][j]->getKoodi() == MS) {
					this->annaSotilaanLaillisetSiirrot(lista, &Ruutu(i, j), asema, vari);
				}
			}
		}
	}
	annaLinnoitusSiirrot(lista, asema, vari);
	this->huolehdiKuninkaanShakeista(lista, asema, vari);
}

void LaillisetSiirrot::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	if (siirto->getLoppuruutu().getRivi() == 7) {
		// valkea korottaa
		siirto->miksikorotetaan = asema->vd;
		lista.push_back(*siirto);

		Siirto torniksi = *siirto;
		torniksi.miksikorotetaan = asema->vt;
		lista.push_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi.miksikorotetaan = asema->vl;
		lista.push_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi.miksikorotetaan = asema->vr;
		lista.push_back(ratsuksi);
	}
	else if (siirto->getLoppuruutu().getRivi() == 0) {
		// musta korottaa
		siirto->miksikorotetaan = asema->md;
		lista.push_back(*siirto);

		Siirto torniksi = *siirto;
		torniksi.miksikorotetaan = asema->mt;
		lista.push_back(torniksi);

		Siirto lahetiksi = *siirto;
		lahetiksi.miksikorotetaan = asema->ml;
		lista.push_back(lahetiksi);

		Siirto ratsuksi = *siirto;
		ratsuksi.miksikorotetaan = asema->mr;
		lista.push_back(ratsuksi);
	}
}