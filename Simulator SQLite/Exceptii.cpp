#include "Exceptii.h"

using namespace std;

ExceptieSintaxa::ExceptieSintaxa(string mesajEroare) : mesajEroare(mesajEroare) {}
const char* ExceptieSintaxa::what() const {
    return mesajEroare.c_str();
}

ExceptieTabelNespecificat::ExceptieTabelNespecificat() {}
const char* ExceptieTabelNespecificat::what() const {
    return "Comanda este incorecta.Nu a fost specificat numele tabelului.\n";
}


ExceptieTabelDuplicat::ExceptieTabelDuplicat(string nume_tabel) : nume_tabel(nume_tabel) {
    mesajEroare = "Comanda este incorecta. Un tabel cu numele " + nume_tabel + " exista deja in baza de date.\n";
}
const char* ExceptieTabelDuplicat::what() const {
    return mesajEroare.c_str();
}

ExceptieTabelInexistent::ExceptieTabelInexistent(string nume_tabel) : nume_tabel(nume_tabel) {}
const char* ExceptieTabelInexistent::what() const {
    mesajEroare = "Comanda este incorecta. Tabelul " + nume_tabel + " nu a fost gasit in baza de date.\n";
    return mesajEroare.c_str();
}

ExceptieNumeColoanaInexistent::ExceptieNumeColoanaInexistent(string nume_tabel, string nume_coloana)
    : nume_tabel(nume_tabel), nume_coloana(nume_coloana) {}
const char* ExceptieNumeColoanaInexistent::what() const {
    mesajEroare = "Coloana " + nume_coloana + " nu a fost gasita in tabelul " + nume_tabel + ".\n";
    return mesajEroare.c_str();
}

ExceptieValoareColoanaInexistenta::ExceptieValoareColoanaInexistenta(string nume_tabel, string nume_coloana, string valoare_coloana)
    : nume_tabel(nume_tabel), nume_coloana(nume_coloana), valoare_coloana(valoare_coloana) {}
const char* ExceptieValoareColoanaInexistenta::what() const {
    mesajEroare = "Nu au fost gasite date in tabelul " + nume_tabel + ", unde " + nume_coloana + " = " + valoare_coloana + ".\n";
    return mesajEroare.c_str();
}