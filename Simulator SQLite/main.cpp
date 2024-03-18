#include<iostream> 
#include<string>
#include<fstream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<iomanip>
#include "FileHandler.h"
#include "Comenzi.h"

using namespace std;

int main() {

	vector<Tabel> baza_de_date;
	preluareBazaDeDateDinFisiere(baza_de_date);
	procesareComandaDisplayDatabase(baza_de_date);

	cout << "Alegeti o comanda:\n\n"
		<< "CREATE TABLE nume_tabel((nume_coloana1, tip, dimensiune, valoare_implicta), (nume_coloana2, tip, dimensiune, valoare_implicta))\n"
		<< "SELECT nume_coloana1, nume_coloana2 FROM nume_tabel sau SELECT * FROM nume_tabel / SELECT ALL FROM nume_tabel\n"
		<< "DISPLAY TABLE nume_tabel\n"
		<< "INSERT INTO nume_tabel VALUES(valoare_coloana1, valoare_coloana2)\n"
		<< "UPDATE nume_tabel SET nume_coloana = valoare_noua WHERE nume_coloana = valoare_veche\n"
		<< "sau UPDATE nume_tabel SET nume_coloana = valoare_noua WHERE nume_coloana2 = valoare_coloana2\n"
		<< "DELETE FROM nume_tabel WHERE nume_coloana = valoare\n"
		<< "DROP TABLE nume_tabel\n"
		<< "EXIT pentru a iesi\n\n";

	char* comanda = new char[2000];

	while (true) {
		cin.getline(comanda, 2000);

		if (strlen(comanda) == 0 || all_of(comanda, comanda + strlen(comanda), isspace)) {
			cout << "Comanda este incorecta. Daca doriti sa parasiti programul, introduceti 'EXIT'\n";
		}
		else if (strcmp(comanda, "exit") == 0 || strcmp(comanda, "EXIT") == 0) {
			actualizareBazaDeDateInFisiere(baza_de_date);
			break;
		}
		else {
			try {
				identificareComanda(comanda, baza_de_date);
			}
			catch(const exception& e){
				cout << e.what();
			}
			actualizareBazaDeDateInFisiere(baza_de_date);
			cout << "\nIntroduceti comanda sau 'EXIT' pentru a iesi:\n";
		}
	}
}