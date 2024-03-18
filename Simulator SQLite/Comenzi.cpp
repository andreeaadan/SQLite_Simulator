#include<iostream> 
#include<string>
#include<fstream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<iomanip>
#include "Comenzi.h"
#include "FunctiiAuxiliare.h"
#include "Exceptii.h"

using namespace std;

void procesareComandaCreateTable(char* p, char* next_token, vector<Tabel>& baza_de_date) {
	string mesajEroareSintaxa = "Comanda este incorecta.\nSintaxa pentru comanda CREATE TABLE este: \n"
    "CREATE TABLE nume_tabel((nume_coloana1, tip, dimensiune, valoare_implicta), (nume_coloana2, tip, dimensiune, valoare_implicta))\n";
	
	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL || !(strcmp("table", p) == 0 || strcmp("TABLE", p) == 0)) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	int nr_coloane = 0;
	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	string nume_tabel = p;
	if (tabelulAFostGasitInBazaDeDate(baza_de_date, nume_tabel)) {
		throw ExceptieTabelDuplicat(nume_tabel);
	}

	vector<string> nume_coloana;
	vector<string> tip;
	vector<string> dimensiune;
	vector<string> valoare_implicita;

	int index_vector_structura_tabel = -1;
	p = strtok_s(NULL, "(),; ", &next_token);

	while (p != NULL) {
		index_vector_structura_tabel++;

		if (index_vector_structura_tabel == 0) {
			nume_coloana.push_back(p);
		}
		else if (index_vector_structura_tabel == 1) {
			tip.push_back(p);
		}
		else if (index_vector_structura_tabel == 2) {
			dimensiune.push_back(p);
		}
		else if (index_vector_structura_tabel == 3) {
			valoare_implicita.push_back(p);
			nr_coloane++;
		}

		p = strtok_s(NULL, "(),; ", &next_token);

		if (p != NULL && index_vector_structura_tabel == 3) {
			index_vector_structura_tabel = -1;
		}
	}

	if (index_vector_structura_tabel != 3) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	vector<vector<string>> structura_tabel;
	structura_tabel.push_back(nume_coloana);
	structura_tabel.push_back(tip);
	structura_tabel.push_back(dimensiune);
	structura_tabel.push_back(valoare_implicita);

	Tabel t(nr_coloane, nume_tabel, structura_tabel);
	baza_de_date.push_back(t);
	cout << "Tabelul " << nume_tabel << " a fost creat cu succes.\n";
}

void procesareComandaDeleteFrom(char* p, char* next_token, vector<Tabel>& baza_de_date) {
	string mesajEroareSintaxa = "Comanda este incorecta.\nSintaxa pentru comanda DELETE FROM este:\n"
								"DELETE FROM nume_tabel WHERE nume_coloana = valoare\n";


	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL || !(strcmp("from", p) == 0 || strcmp("FROM", p) == 0)) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	string nume_tabel = p;
	if (!tabelulAFostGasitInBazaDeDate(baza_de_date, nume_tabel)) {
		throw ExceptieTabelInexistent(nume_tabel);
	}

	int index_tabel = determinareIndexTabelInBd(nume_tabel, baza_de_date);
	p = strtok_s(NULL, "=(),; ", &next_token);
	if (p == NULL || !(strcmp("where", p) == 0 || strcmp("WHERE", p) == 0)) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	p = strtok_s(NULL, "=(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	string nume_coloana = p;


	Tabel tabel = baza_de_date[index_tabel];
	if (!numeleColoaneiAFostGasitInTabel(nume_coloana, tabel)) {
		throw ExceptieNumeColoanaInexistent(nume_tabel, nume_coloana);
	}

	p = strtok_s(NULL, "=(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	string valoare = p;


	int index_coloana = determinareIndexColoanaInTabel(nume_coloana, tabel);
	if (!valoareaColoaneiAFostGasitaInTabel(valoare, index_coloana, tabel)) {
		throw ExceptieValoareColoanaInexistenta(nume_tabel, nume_coloana, valoare);
	}

	vector<int> indecsi_valori_care_indeplinesc_conditia;
	populareVectorIndecsi(indecsi_valori_care_indeplinesc_conditia, valoare, index_coloana, tabel);

	for (int i = indecsi_valori_care_indeplinesc_conditia.size() - 1; i >= 0; i--) {
		for (int j = 0; j < baza_de_date[index_tabel].nr_coloane; j++) {
			baza_de_date[index_tabel].date_tabel[j]
				.erase(baza_de_date[index_tabel].date_tabel[j].begin() + indecsi_valori_care_indeplinesc_conditia[i]);
		}
	}

	cout << "Datele au fost sterse cu succes." << endl;
}

void procesareComandaInsertInto(char* p, char* next_token, vector<Tabel>& baza_de_date) {
	string mesajEroareSintaxa = "Comanda este incorecta.\nSintaxa pentru comanda INSERT INTO este: "
							    "INSERT INTO nume_tabel VALUES(valoare_coloana1, valoare_coloana2)\n";
	
	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL || !(strcmp("into", p) == 0 || strcmp("INTO", p) == 0)) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieTabelNespecificat();
	}

	string nume_tabel = p;
	if (!tabelulAFostGasitInBazaDeDate(baza_de_date, nume_tabel)) {
		throw ExceptieTabelInexistent(nume_tabel);
	}

	int nr_coloane_tabel;
	for (int i = 0; i < baza_de_date.size(); i++) {
		if (nume_tabel == baza_de_date[i].nume_tabel) {
			nr_coloane_tabel = baza_de_date[i].nr_coloane;
			break;
		}
	}

	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL || !(strcmp("values", p) == 0 || strcmp("VALUES", p) == 0)) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	if (!coloaneleInserateSuntValide(next_token, nr_coloane_tabel)) {
		return;
	}

	p = strtok_s(NULL, "(),; ", &next_token);
	int nr_coloane_introduse = 0;
	int index_tabel = determinareIndexTabelInBd(nume_tabel, baza_de_date);
	while (p != NULL && nr_coloane_introduse < nr_coloane_tabel) {
		baza_de_date[index_tabel].date_tabel[nr_coloane_introduse].push_back(p);
		p = strtok_s(NULL, "(),; ", &next_token);
		nr_coloane_introduse++;
	}

	cout << "Datele au fost inserate cu succes." << endl;
}

void procesareComandaDropTable(char* p, char* next_token, vector<Tabel>& baza_de_date) {
	string mesajEroareSintaxa = "Comanda este incorecta.\nSintaxa pentru comanda DROP TABLE este:\nDROP TABLE nume_tabel\n";

	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL || !(strcmp("table", p) == 0 || strcmp("TABLE", p) == 0)) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieTabelNespecificat();
	}

	string nume_tabel = p;
	if (!tabelulAFostGasitInBazaDeDate(baza_de_date, nume_tabel)) {
		throw ExceptieTabelInexistent(nume_tabel);
	}

	for (int i = 0; i < baza_de_date.size(); i++) {
		if (baza_de_date[i].nume_tabel == nume_tabel) {
			baza_de_date.erase(baza_de_date.begin() + i);
			break;
		}
	}
	cout << "Tabelul " << nume_tabel << " a fost sters din baza de date.\n";
}

void procesareComandaUpdateTable(char* p, char* next_token, vector<Tabel>& baza_de_date) {
	string mesajEroareSintaxa = "Comanda este incorecta.\nSintaxa pentru comanda UPDATE TABLE este:"
								"UPDATE nume_tabel SET nume_coloana = valoare_noua WHERE nume_coloana = valoare_veche\n";

	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	string nume_tabel = p;
	if (!tabelulAFostGasitInBazaDeDate(baza_de_date, nume_tabel)) {
		throw ExceptieTabelInexistent(nume_tabel);
	}

	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL || !(strcmp("set", p) == 0 || strcmp("SET", p) == 0)) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	int index_tabel = determinareIndexTabelInBd(nume_tabel, baza_de_date);
	Tabel tabel = baza_de_date[index_tabel];

	p = strtok_s(NULL, "=(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	string nume_coloana_de_actualizat = p;

	if (!numeleColoaneiAFostGasitInTabel(nume_coloana_de_actualizat, tabel)) {
		throw ExceptieNumeColoanaInexistent(nume_tabel, nume_coloana_de_actualizat);
	}

	p = strtok_s(NULL, "=(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	string valoare_noua_coloana = p;

	p = strtok_s(NULL, "=(),; ", &next_token);
	if (p == NULL || !(strcmp("where", p) == 0 || strcmp("WHERE", p) == 0)) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	p = strtok_s(NULL, "=(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	string nume_coloana_conditie = p;

	if (!numeleColoaneiAFostGasitInTabel(nume_coloana_conditie, tabel)) {
		throw ExceptieNumeColoanaInexistent(nume_tabel, nume_coloana_conditie);
	}

	p = strtok_s(NULL, "=(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	string valoare_coloana_conditie = p;

	int index_nume_coloana_conditie = determinareIndexColoanaInTabel(nume_coloana_conditie, tabel);
	if (!valoareaColoaneiAFostGasitaInTabel(valoare_coloana_conditie, index_nume_coloana_conditie, tabel)) {
		throw ExceptieValoareColoanaInexistenta(nume_tabel, nume_coloana_conditie, valoare_coloana_conditie);
	}

	vector<int> indecsi_valori_care_indeplinesc_conditia;
	populareVectorIndecsi(indecsi_valori_care_indeplinesc_conditia, valoare_coloana_conditie, index_nume_coloana_conditie, tabel);

	int index_coloana_de_actualizat = determinareIndexColoanaInTabel(nume_coloana_de_actualizat, tabel);
	for (int i = 0; i < indecsi_valori_care_indeplinesc_conditia.size(); i++) {
		baza_de_date[index_tabel].date_tabel[index_coloana_de_actualizat][indecsi_valori_care_indeplinesc_conditia[i]] = valoare_noua_coloana;
	}

	cout << "Datele au fost actualizate cu succes.\n";
}

void procesareComandaSelectAll(char* p, char* next_token, vector<Tabel>& baza_de_date, string mesajEroareSintaxa) {
	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL || !(strcmp("from", p) == 0 || strcmp("FROM", p) == 0)) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	string nume_tabel = p;
	if (!tabelulAFostGasitInBazaDeDate(baza_de_date, nume_tabel)) {
		throw ExceptieTabelInexistent(nume_tabel);
	}

	afisareDateTabel(nume_tabel, baza_de_date);
}

void procesareComandaSelectColoana(char* p, char* next_token, vector<Tabel>& baza_de_date, string mesajEroareSintaxa) {
	vector<string> nume_coloane;
	while (!(strcmp(p, "from") == 0 || strcmp(p, "FROM") == 0)) {
		string nume_coloana = p;
		nume_coloane.push_back(nume_coloana);
		p = strtok_s(NULL, "(),; ", &next_token);
		if (p == NULL) {
			throw ExceptieSintaxa(mesajEroareSintaxa);
		}
	}

	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}

	string nume_tabel = p;
	if (!tabelulAFostGasitInBazaDeDate(baza_de_date, nume_tabel)) {
		throw ExceptieTabelInexistent(nume_tabel);
	}

	afisareSelectColoana(nume_coloane, nume_tabel, baza_de_date);
}

void procesareComandaSelectFrom(char* p, char* next_token, vector<Tabel>& baza_de_date) {
	string mesajEroareSintaxa = "Comanda este incorecta.\nSintaxa pentru comanda SELECT este:\n"
					"SELECT nume_coloana1, nume_coloana2 FROM nume_tabel sau SELECT * FROM nume_tabel / SELECT ALL FROM nume_tabel\n";
	
	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	if (strcmp("all", p) == 0 || strcmp("ALL", p) == 0 || strcmp("*", p) == 0) {
		procesareComandaSelectAll(p, next_token, baza_de_date, mesajEroareSintaxa);
	}
	else {
		procesareComandaSelectColoana(p, next_token, baza_de_date, mesajEroareSintaxa);
	}
}

void procesareComandaDisplayTable(char* p, char* next_token, vector<Tabel>& baza_de_date) {
	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieTabelNespecificat();
	}

	string nume_tabel = p;
	if (!tabelulAFostGasitInBazaDeDate(baza_de_date, nume_tabel)) {
		throw ExceptieTabelInexistent(nume_tabel);
	}

	cout << "\nStructura tabel:\n";
	afisareStructuraTabel(nume_tabel, baza_de_date);
	cout << "Date tabel:\n";
	afisareDateTabel(nume_tabel, baza_de_date);
}

void procesareComandaDisplayDatabase(vector<Tabel> baza_de_date) {
	if (baza_de_date.size() == 0) {
		cout << "Baza de date nu contine date.\n";
		return;
	}

	cout << "BAZA DE DATE\n";

	for (int index_tabel = 0; index_tabel < baza_de_date.size(); index_tabel++) {
		afisareDateTabel(baza_de_date[index_tabel].nume_tabel, baza_de_date);
	}
}

void procesareComandaDisplay(char* p, char* next_token, vector<Tabel>& baza_de_date) {
	string mesajEroareSintaxa = "Comanda este incorecta.\nSintaxa pentru comanda DISPLAY este:\n"
								"DISPLAY TABLE nume_tabel sau DISPLAY DATABASE.\n";
	p = strtok_s(NULL, "(),; ", &next_token);
	if (p == NULL) {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
	else if (strcmp("table", p) == 0 || strcmp("TABLE", p) == 0) {
		procesareComandaDisplayTable(p, next_token, baza_de_date);
	}
	else if (strcmp("database", p) == 0 || strcmp("DATABASE", p) == 0) {
		procesareComandaDisplayDatabase(baza_de_date);
	}
	else {
		throw ExceptieSintaxa(mesajEroareSintaxa);
	}
}

void identificareComanda(char* comanda, vector<Tabel>& baza_de_date) {
	char* next_token;
	char* p = strtok_s(comanda, "(),; ", &next_token);

	if (strcmp("create", p) == 0 || strcmp("CREATE", p) == 0) {
		procesareComandaCreateTable(p, next_token, baza_de_date);
	}
	else if (strcmp("drop", p) == 0 || strcmp("DROP", p) == 0) {
		procesareComandaDropTable(p, next_token, baza_de_date);
	}
	else if (strcmp("insert", p) == 0 || strcmp("INSERT", p) == 0) {
		procesareComandaInsertInto(p, next_token, baza_de_date);
	}
	else if (strcmp("delete", p) == 0 || strcmp("DELETE", p) == 0) {
		procesareComandaDeleteFrom(p, next_token, baza_de_date);
	}
	else if (strcmp("update", p) == 0 || strcmp("UPDATE", p) == 0) {
		procesareComandaUpdateTable(p, next_token, baza_de_date);
	}
	else if (strcmp("select", p) == 0 || strcmp("SELECT", p) == 0) {
		procesareComandaSelectFrom(p, next_token, baza_de_date);
	}
	else if (strcmp("display", p) == 0 || strcmp("DISPLAY", p) == 0) {
		procesareComandaDisplay(p, next_token, baza_de_date);
	}
	else {
		cout << "Comanda este incorecta.\n";
	}
}