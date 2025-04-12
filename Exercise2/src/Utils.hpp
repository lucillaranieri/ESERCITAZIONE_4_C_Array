
#pragma once
#include <iostream>
#include <string>

using namespace std;

// Definisco tutte le funzioni, queste funzioni verranno richiamate

bool LetturaDati(const string& inputFilePath, size_t& n, double& S, double*& w, double*& r);

double ProdottoScalare(const size_t& n, const double* const& w, const double* const& r);

bool ScritturaRisultati(const string& outputFilePath, const size_t& n, const double* const& w, const double* const& r,const double& S, const double& rate, const double& V);

double ValoreTot(const double &r, const double &S);   //r non è r di ScritturaRisultati è una nuova per questa funzione ValoreTot

string ArrayToString(const size_t& n, const double* const& v);

