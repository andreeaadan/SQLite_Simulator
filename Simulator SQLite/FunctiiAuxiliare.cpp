#include<iostream>
#include<iomanip>
#include "FunctiiAuxiliare.h"

bool tabelulAFostGasitInBazaDeDate(vector<Tabel> baza_de_date, string nume_tabel) {
	for (int i = 0; i < baza_de_date.size(); i++) {
		if (baza_de_date[i].nume_tabel == nume_tabel) {
			return true;
		}
	}
	return false;
}

bool numeleColoaneiAFostGasitInTabel(string nume_coloana, Tabel tabel) {
	for (int i = 0; i < tabel.nr_coloane; i++) {
		if (tabel.structura_tabel[0][i] == nume_coloana) {
			return true;
		}
	}
	return false;
}

bool valoareaColoaneiAFostGasitaInTabel(string valoare_coloana, int index_nume_coloana, Tabel tabel) {
	bool minim_o_valoare_a_fost_gasita = false;
	for (int index_valoare_coloana = 0; index_valoare_coloana < tabel.date_tabel[0].size(); index_valoare_coloana++) {
		if (tabel.date_tabel[index_nume_coloana][index_valoare_coloana] == valoare_coloana) {
			minim_o_valoare_a_fost_gasita = true;
			break;
		}
	}
	if (minim_o_valoare_a_fost_gasita) {
		return true;
	}
	else {
		return false;
	}

}

bool coloaneleInserateSuntValide(char* next_token, int nr_coloane_tabel) {
	char* aux_p = _strdup(next_token);
	int nr_coloane_introduse = 0;
	char* aux_next_token;
	aux_p = strtok_s(aux_p, "(),; ", &aux_next_token);
	if (aux_p == NULL) {
		cout << "Comanda este incorecta." << endl
			<< "Sintaxa pentru comanda INSERT INTO este: " << endl
			<< "INSERT INTO nume_tabel VALUES(valoare_coloana1, valoare_coloana2)\n";
		return false;
	}
	while (aux_p != NULL) {
		nr_coloane_introduse++;
		aux_p = strtok_s(NULL, "(),; ", &aux_next_token);
	}

	if (nr_coloane_introduse != nr_coloane_tabel) {
		cout << "Comanda este incorecta." << endl
			<< "Numarul de coloane introduse nu corespunde cu numarul de coloane al tabelului. "
			<< "Acesta trebuie sa fie " << nr_coloane_tabel << ".\n";
		return false;
	}

	return true;
}

int determinareIndexTabelInBd(string nume_tabel, vector<Tabel> baza_de_date) {
	int index_tabel;
	for (index_tabel = 0; index_tabel < baza_de_date.size(); index_tabel++) {
		if (baza_de_date[index_tabel].nume_tabel == nume_tabel) {
			break;
		}
	}
	return index_tabel;
}

int determinareIndexColoanaInTabel(string nume_coloana, Tabel tabel) {
	int index_coloana;
	for (index_coloana = 0; index_coloana < tabel.structura_tabel[0].size(); index_coloana++) {
		if (tabel.structura_tabel[0][index_coloana] == nume_coloana) {
			break;
		}
	}
	return index_coloana;
}

void populareVectorIndecsi(vector<int>& vector, string valoare, int index_coloana, Tabel tabel) {
	for (int index_valoare = 0; index_valoare < tabel.date_tabel[index_coloana].size(); index_valoare++) {
		if (valoare == tabel.date_tabel[index_coloana][index_valoare]) {
			vector.push_back(index_valoare);
		}
	}
}

void afisareMargineaDeSus(vector<string> vector, string nume_tabel) {
	cout << nume_tabel << endl;
	cout << "+";
	for (int a = 0; a < vector.size(); a++) {
		cout << setw(12) << setfill('-') << "+";
	}
	cout << endl;

	for (int b = 0; b < vector.size(); b++) {
		cout << "|" << setw(11) << setfill(' ') << vector[b];
	}
	cout << "|" << endl;

	cout << "+";
	for (int a = 0; a < vector.size(); a++) {
		cout << setw(12) << setfill('-') << "+";
	}
	cout << endl;
}

void afisareMargineaDeJos(vector<string> vector) {
	cout << "+";
	for (int c = 0; c < vector.size(); c++) {
		cout << setw(12) << setfill('-') << "+";
	}
	cout << endl << endl;

}

void afisareDate(int index_tabel, vector<Tabel> baza_de_date) {
	for (int linie = 0; linie < baza_de_date[index_tabel].date_tabel[0].size(); linie++) {
		for (int coloana = 0; coloana < baza_de_date[index_tabel].date_tabel.size(); coloana++) {
			cout << "|" << setw(11) << setfill(' ') << baza_de_date[index_tabel].date_tabel[coloana][linie];
		}
		cout << "|" << endl;
	}
}

void afisareDateStructuraTabel(int index_tabel, vector<Tabel> baza_de_date) {
	for (int index_coloana_din_tabel = 1; index_coloana_din_tabel < 4; index_coloana_din_tabel++) {
		for (int index_coloana_de_la_tastatura = 0; index_coloana_de_la_tastatura < baza_de_date[index_tabel].nr_coloane; index_coloana_de_la_tastatura++) {
			cout << "|" << setw(11) << setfill(' ') << baza_de_date[index_tabel].structura_tabel[index_coloana_din_tabel][index_coloana_de_la_tastatura];
		}
		cout << "|" << endl;
	}
}

void afisareStructuraTabel(string nume_tabel, vector<Tabel> baza_de_date) {
	int index_tabel = determinareIndexTabelInBd(nume_tabel, baza_de_date);
	vector<string> vectorul_de_afisat = baza_de_date[index_tabel].structura_tabel[0];
	afisareMargineaDeSus(vectorul_de_afisat, nume_tabel);
	afisareDateStructuraTabel(index_tabel, baza_de_date);
	afisareMargineaDeJos(vectorul_de_afisat);
	cout << endl;

}

void afisareDateTabel(string nume_tabel, vector<Tabel> baza_de_date) {
	int index_tabel = determinareIndexTabelInBd(nume_tabel, baza_de_date);
	vector<string> vectorul_de_afisat = baza_de_date[index_tabel].structura_tabel[0];
	afisareMargineaDeSus(vectorul_de_afisat, nume_tabel);
	afisareDate(index_tabel, baza_de_date);
	afisareMargineaDeJos(vectorul_de_afisat);
}

void afisareSelectColoana_Date(vector<string> nume_coloane, string nume_tabel, vector<Tabel> baza_de_date) {
	int index_tabel = determinareIndexTabelInBd(nume_tabel, baza_de_date);
	int nr_valori_din_coloane = baza_de_date[index_tabel].date_tabel[0].size();
	int nr_coloane_de_afisat = nume_coloane.size();
	int nr_coloane = baza_de_date[index_tabel].structura_tabel[0].size();
	for (int i = 0; i < nr_valori_din_coloane; i++) {
		cout << "|";
		for (int a = 0; a < nr_coloane_de_afisat; a++) {
			bool coloana_a_fost_gasita = false;
			for (int j = 0; j < nr_coloane; j++) {
				if (baza_de_date[index_tabel].structura_tabel[0][j] == nume_coloane[a]) {
					cout << setw(11) << setfill(' ') << baza_de_date[index_tabel].date_tabel[j][i];
					coloana_a_fost_gasita = true;
					break;
				}
			}
			if (!coloana_a_fost_gasita) {
				cout << setw(11) << setfill(' ') << " ";
			}
			cout << "|";
		}
		cout << endl;
	}
}

void afisareSelectColoana(vector<string> nume_coloane, string nume_tabel, vector<Tabel> baza_de_date) {
	afisareMargineaDeSus(nume_coloane, nume_tabel);
	afisareSelectColoana_Date(nume_coloane, nume_tabel, baza_de_date);
	afisareMargineaDeJos(nume_coloane);
}
