#include<iostream> 
#include<fstream>
#include "FileHandler.h"

void preluareStructuraTabeleDinFisier(vector<Tabel>& baza_de_date) {
	int nr_tabele;
	int nr_coloane;
	string linie;
	string nume_tabel;
	fstream fisier;
	fisier.open("structura.txt", ios::in);

	if (fisier.peek() != EOF) {
		getline(fisier, linie);
		nr_tabele = stoi(linie);

		while (getline(fisier, linie)) {
			vector<string> nume_coloana;
			vector<string> tip;
			vector<string> dimensiune;
			vector<string> valoare_implicita;
			vector<vector<string>> vectori_date;

			nume_tabel = linie;
			getline(fisier, linie);
			nr_coloane = stoi(linie);
			for (int index_coloana_din_tabel = 0; index_coloana_din_tabel < nr_coloane; index_coloana_din_tabel++) {
				getline(fisier, linie);
				nume_coloana.push_back(linie);

				getline(fisier, linie);
				tip.push_back(linie);

				getline(fisier, linie);
				dimensiune.push_back(linie);

				getline(fisier, linie);
				valoare_implicita.push_back(linie);
			}

			vectori_date.push_back(nume_coloana);
			vectori_date.push_back(tip);
			vectori_date.push_back(dimensiune);
			vectori_date.push_back(valoare_implicita);

			Tabel t(nr_coloane, nume_tabel, vectori_date);
			baza_de_date.push_back(t);
		}
		fisier.close();
	}
}

void preluareDateTabeleDinFisier(vector<Tabel>& baza_de_date) {
	string linie;
	string nume_tabel;
	fstream fisier;

	fisier.open("date.txt", ios::in);
	if (fisier.peek() != EOF) {
		while (getline(fisier, linie)) {
			int index_tabel;
			nume_tabel = linie;
			for (index_tabel = 0; index_tabel < baza_de_date.size(); index_tabel++) {
				if (nume_tabel == baza_de_date[index_tabel].nume_tabel) {
					int nr_coloane = baza_de_date[index_tabel].nr_coloane;
					break;
				}
			}
			for (int index_coloana_din_tabel = 0; index_coloana_din_tabel < baza_de_date[index_tabel].nr_coloane; index_coloana_din_tabel++) {
				getline(fisier, linie);
				baza_de_date[index_tabel].date_tabel[index_coloana_din_tabel].push_back(linie);
			}
		}
		cout << endl;
		fisier.close();
	}
}


void actualizareStructuraTabelInFisier(vector<Tabel>& baza_de_date) {
	fstream fisier;
	fisier.open("structura.txt", ios::out | ios::trunc);

	if (baza_de_date.size()) {
		fisier << baza_de_date.size() << endl;
	}

	for (int index_tabel = 0; index_tabel < baza_de_date.size(); index_tabel++) {
		fisier << baza_de_date[index_tabel].nume_tabel << endl;
		fisier << baza_de_date[index_tabel].nr_coloane << endl;
		for (int index_coloana_din_tabel = 0; index_coloana_din_tabel < baza_de_date[index_tabel].nr_coloane; index_coloana_din_tabel++) {
			fisier << baza_de_date[index_tabel].structura_tabel[0][index_coloana_din_tabel] << endl;
			fisier << baza_de_date[index_tabel].structura_tabel[1][index_coloana_din_tabel] << endl;
			fisier << baza_de_date[index_tabel].structura_tabel[2][index_coloana_din_tabel] << endl;
			fisier << baza_de_date[index_tabel].structura_tabel[3][index_coloana_din_tabel];

			if (!(index_tabel == baza_de_date.size() - 1 && index_coloana_din_tabel == baza_de_date[index_tabel].nr_coloane - 1)) {
				fisier << endl;
			}
		}
	}

	fisier.close();
}

void actualizareDateTabelInFisier(vector<Tabel>& baza_de_date) {
	fstream fisier;
	fisier.open("date.txt", std::ios::out | std::ios::trunc);

	int nr_tabele_goale = 0;
	for (int index_tabel = 0; index_tabel < baza_de_date.size(); index_tabel++) {
		if (baza_de_date[index_tabel].date_tabel[0].size() == 0) {
			nr_tabele_goale++;
		}
	}

	for (int index_tabel = 0; index_tabel < baza_de_date.size(); index_tabel++) {
		for (int index_coloana_din_tabel = 0; index_coloana_din_tabel < baza_de_date[index_tabel].date_tabel[0].size(); index_coloana_din_tabel++) { //nrColoane
			fisier << baza_de_date[index_tabel].nume_tabel << endl;
			for (int index_coloana_de_la_tastatura = 0; index_coloana_de_la_tastatura < baza_de_date[index_tabel].nr_coloane; index_coloana_de_la_tastatura++) { //nrLinii
				fisier << baza_de_date[index_tabel].date_tabel[index_coloana_de_la_tastatura][index_coloana_din_tabel];

				if (!(index_tabel == baza_de_date.size() - 1 - nr_tabele_goale && index_coloana_din_tabel == baza_de_date[index_tabel].date_tabel[0].size() - 1
					&& index_coloana_de_la_tastatura == baza_de_date[index_tabel].nr_coloane - 1)) {
					fisier << endl;
				}
			}
		}
	}
	fisier.close();
}


void preluareBazaDeDateDinFisiere(vector<Tabel>& baza_de_date) {
	preluareStructuraTabeleDinFisier(baza_de_date);
	preluareDateTabeleDinFisier(baza_de_date);
}

void actualizareBazaDeDateInFisiere(vector<Tabel>& baza_de_date) {
	actualizareStructuraTabelInFisier(baza_de_date);
	actualizareDateTabelInFisier(baza_de_date);
}