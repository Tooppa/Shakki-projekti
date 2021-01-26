#pragma once


// Shakkilaudan ruutu tietyssä (rivi, sarake) -koordinaatissa.
class Ruutu{
public:
	Ruutu(int, int);
	Ruutu() {}
	bool operator == (const Ruutu& r) const { return _sarake == r._sarake && _rivi == r._rivi; }
	bool operator != (const Ruutu& r) const { return !operator==(r); }
	int getRivi();
	int getSarake();
	void setRivi(int);
	void setSarake(int);

private:
	int _sarake;
	int _rivi;
};
