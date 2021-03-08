#pragma once


// Shakkilaudan ruutu tietyssä (rivi, sarake) -koordinaatissa.
class Ruutu {
public:
	Ruutu(short int, short  int);
	Ruutu() {
		_sarake = -1; _rivi = -1;
	}
	bool operator == (const Ruutu& r) const { return _sarake == r._sarake && _rivi == r._rivi; }
	bool operator != (const Ruutu& r) const { return !operator==(r); }
	short int getRivi();
	short int getSarake();
	void setRivi(short int);
	void setSarake(short int);

private:
	short int _sarake;
	short int _rivi;
};
