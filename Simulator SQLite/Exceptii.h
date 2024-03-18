#pragma once
#include <exception>
#include <string>

using namespace std;

class ExceptieSintaxa : public exception {
public:
    string mesajEroare;
    ExceptieSintaxa(string mesaj);
    const char* what() const override;
};

class ExceptieTabelNespecificat : public exception {
public:
    ExceptieTabelNespecificat();
    const char* what() const override;
};

class ExceptieTabelDuplicat : public exception {
public:
    mutable string mesajEroare;
    string nume_tabel;
    ExceptieTabelDuplicat(string nume_tabel);
    const char* what() const override;
};

class ExceptieTabelInexistent : public exception {
public:
    mutable string mesajEroare;
    string nume_tabel;
    ExceptieTabelInexistent(string nume_tabel);
    const char* what() const override;
};

class ExceptieNumeColoanaInexistent : public exception {
public:
    mutable string mesajEroare;
    string nume_tabel;
    string nume_coloana;
    ExceptieNumeColoanaInexistent(string nume_tabel, string nume_coloana);
    const char* what() const override;
};

class ExceptieValoareColoanaInexistenta : public exception {
public:
    mutable string mesajEroare;
    string nume_tabel;
    string nume_coloana;
    string valoare_coloana;
    ExceptieValoareColoanaInexistenta(string nume_tabel, string nume_coloana, string valoare_coloana);
    const char* what() const override;
};