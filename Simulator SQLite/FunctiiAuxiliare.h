#pragma once
#include "Tabel.h"

bool tabelulAFostGasitInBazaDeDate(vector<Tabel> baza_de_date, string nume_tabel);
bool numeleColoaneiAFostGasitInTabel(string nume_coloana, Tabel tabel);
bool valoareaColoaneiAFostGasitaInTabel(string valoare_coloana, int index_nume_coloana, Tabel tabel);
bool coloaneleInserateSuntValide(char* next_token, int nr_coloane_tabel);	
int determinareIndexTabelInBd(string nume_tabel, vector<Tabel> baza_de_date);
int determinareIndexColoanaInTabel(string nume_coloana, Tabel tabel);
void populareVectorIndecsi(vector<int>& vector, string valoare, int index_coloana, Tabel tabel);
void afisareMargineaDeSus(vector<string> vector, string nume_tabel);
void afisareMargineaDeJos(vector<string> vector);
void afisareDate(int index_tabel, vector<Tabel> baza_de_date);
void afisareDateStructuraTabel(int index_tabel, vector<Tabel> baza_de_date);
void afisareStructuraTabel(string nume_tabel, vector<Tabel> baza_de_date);
void afisareDateTabel(string nume_tabel, vector<Tabel> baza_de_date);
void afisareSelectColoana_Date(vector<string> nume_coloane, string nume_tabel, vector<Tabel> baza_de_date);
void afisareSelectColoana(vector<string> nume_coloane, string nume_tabel, vector<Tabel> baza_de_date);