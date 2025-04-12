#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Utils.hpp"

using namespace std;

int main()
{
// Specifico il nome del file di input contenente i dati del portafoglio
string inputFile = "data.txt";

// Variabile che conta il numero di asset nel portafoglio
size_t numAsset;

// Capitale iniziale investito
double CapitaleIn;

// Puntatori a memoria dinamica per i vettori dei pesi e dei rendimenti degli asset
double* pesi = nullptr;
double* rendimenti = nullptr;

// Variabili che conterranno i risultati delle elaborazioni
double rendimentoTot; //Valore del rendimento totale
double SFinale; //Valore finale del portafoglio

// Chiamo la funzione che importa i dati da file e riempio le variabili
LetturaDati(inputFile, numAsset, CapitaleIn, pesi, rendimenti);

// Calcolo il rendimento portafoglio come prodotto scalare tra il vettore dei pesi e quello dei rendimenti
rendimentoTot = ProdottoScalare(numAsset, pesi, rendimenti);

// Applico la formula per il valore finale del portafoglio: V = S * ( 1 + r)
SFinale = ValoreTot(rendimentoTot, CapitaleIn);

// Esporto i risultati su file e li stampo a schermo: questa funzione fa entrambe le cose
ScritturaRisultati("result.txt", numAsset, pesi, rendimenti, CapitaleIn, rendimentoTot, SFinale);

// libero la memoria dinamica allocata per i vettori , per evitare memory leak

delete [] pesi;
delete [] rendimenti;
return 0;
}

