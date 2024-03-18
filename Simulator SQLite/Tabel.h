#pragma once
#include<string>
#include<vector>

using namespace std;

class Tabel {
public:
	int nr_coloane;
	string nume_tabel;
	vector<vector<string>> structura_tabel;
	vector<vector<string>> date_tabel;

	Tabel();

	Tabel(int nr_coloane, string nume_tabel, vector<vector<string>> structura_tabel);
	~Tabel();
};