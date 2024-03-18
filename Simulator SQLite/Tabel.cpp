#include "Tabel.h"

using namespace std;

Tabel::	Tabel()	{}

Tabel::Tabel(int nr_coloane, string nume_tabel, vector<vector<string>> structura_tabel) {
		this->nr_coloane = nr_coloane;
		this->nume_tabel = nume_tabel;
		for (int i = 0; i < 4; i++) {
			this->structura_tabel.push_back(structura_tabel[i]);
		}
		vector<string> gol;
		for (int i = 0; i < nr_coloane; i++) {
			this->date_tabel.push_back(gol);
		}
}

Tabel::~Tabel() {}