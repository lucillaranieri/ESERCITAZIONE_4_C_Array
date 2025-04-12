#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "Utils.hpp"

using namespace std;

// Funzione che legge da file i dati di "data.txt":
//- capitale iniziale S,
//- numero di asset n,
//- due vettori w e r(relativi ai pesi e ai rendimenti)
//Dato che la dimensione dei vettori non è nota a tempo di compilazione, utilizzo l'allocazione dinamica per w e r.
//i puntatori vengono passati per riferimento per poter essere modificati all'interno della funzione

bool LetturaDati(const string& inputFilePath, size_t& n, double& S, double*& w, double*& r)
{
ifstream file(inputFilePath);
if(file.fail()) //Verifica che il file si possa leggere
{
cout << "File not found" << endl;
return false;
}

// Ignoro la parte testuale prima di ';'

std::string tmp;
getline( file, tmp,';');

// Memorizzo il valore del capitale iniziale(S)

file >> S;
file.ignore(); //Ignoro il carattere di newline

// Procedura analoga per leggere il numero di asset

getline(file, tmp,';');
file >> n;
file.ignore();
getline(file, tmp); // Pulisco la riga successiva

// Creo gli array di dimensione n per r e w

w = new double[n];
r = new double[n];
double pos;
for(unsigned int i = 0; i < n; i++)
{
getline(file, tmp);

// Trovo la posizione di ; nella riga

pos = tmp.find(';');

// Estrazione della sottostinga prima di ;(componenti di w) e conversione di queste in double (prima erano stringhe)

w[i] = stod(tmp.substr(0, pos));

// Procedura analoga per r

r[i] = stod(tmp.substr(pos + 1));
}
file.close();
return true;
}

// Calcolo il prodotto scalare tra i vettori w e r di dimensione n.
// Questo mi serve per avere il rendimento totale di tutto il capitale investito S.

double ProdottoScalare(const size_t& n, const double* const& w, const double* const& r) //I vettori sono passati per riferimento costante perchè non devono essere modificati
{
double Prod = 0;
for(unsigned int i = 0; i < n; i++)
{
Prod += w[i] * r[i];     //moltiplichi le componenti con i uguali e poi sommi tutto (definizione di prodotto scalare)
}
return Prod;
}
// Calcolo il valore finale del portafoglio, applicando la formula: V = (1 + rendimento) * capitale iniziale

double ValoreTot(const double &r, const double &S)
{
return (1 + r) * S;
}

// Questa funzione esporta i file su file e li stampa anche a terminale.

bool ScritturaRisultati(const string& outputFilePath, const size_t& n, const double* const& w, const double* const& r, const double& S, const double& rate, const double& V) //Tutti i parametri vengono passati per riferimento costante perchè non vengono modificati
{
ofstream file;
file.open(outputFilePath);

if (file.fail())
{
cerr << "File open failed" << endl;
return false;
}

// Scrittura su file
file << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;

// Ripristino il formato predefinito prima di scrivere rate
file.unsetf(ios::fixed); // Disattivo la notazione decimale forzata
file << setprecision(4); // Imposto la precisione totale significativa

// I vettori w e r vengono convertiti in stringhe tramite la funzione ArrayToString
file << "w = " << ArrayToString(n,w) << endl;
file << "r = " << ArrayToString(n,r) << endl;
file << "Rate of return of the portfolio: " << rate << endl;
file << "V: " << fixed << setprecision(2) << V << endl;

// Stampa sul terminale
cout << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;

// Ripristino anche sul cout
cout.unsetf(ios::fixed);
cout << setprecision(4);

cout << "w = " << ArrayToString(n,w ) << endl;
cout << "r = " << ArrayToString(n,r) << endl;
cout << "Rate of return of the portfolio: " << rate << endl;
cout << "V: " << fixed << setprecision(2) << V << endl; // Il valore finale viene stampato in notazione fissa con due cifre decimali
file.close();
return true;
}

// Converte un array di double in una stringa formattata            //questo mi serve per avere la stampa finale come richiesto dal pdf del tetso dell'esercizio 
string ArrayToString(const size_t& n, const double* const& v)
{
string str;
ostringstream toString;
toString << "[ ";
for (unsigned int i = 0; i < n; i++)
toString<< v[i]<< " ";
toString << "]";

return toString.str();
}
