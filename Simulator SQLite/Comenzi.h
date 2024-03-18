#pragma once
#include "Tabel.h"

void identificareComanda(char* comanda, vector<Tabel>& baza_de_date);
void procesareComandaCreateTable(char* p, char* next_token, vector<Tabel>& baza_de_date);
void procesareComandaDeleteFrom(char* p, char* next_token, vector<Tabel>& baza_de_date);
void procesareComandaInsertInto(char* p, char* next_token, vector<Tabel>& baza_de_date);
void procesareComandaDropTable(char* p, char* next_token, vector<Tabel>& baza_de_date);
void procesareComandaUpdateTable(char* p, char* next_token, vector<Tabel>& baza_de_date);
void procesareComandaSelectFrom(char* p, char* next_token, vector<Tabel>& baza_de_date);
void procesareComandaSelectAll(char* p, char* next_token, vector<Tabel>& baza_de_date, string mesajEroareSintaxa);
void procesareComandaSelectColoana(char* p, char* next_token, vector<Tabel>& baza_de_date, string mesajEroareSintaxa);
void procesareComandaDisplay(char* p, char* next_token, vector<Tabel>& baza_de_date);
void procesareComandaDisplayTable(char* p, char* next_token, vector<Tabel>& baza_de_date);
void procesareComandaDisplayDatabase(vector<Tabel> baza_de_date);