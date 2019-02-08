/*******************************************************************************************
Créé le : 06 février 2019
par : pierre
e-mail :
*******************************************************************************************/

//------------- Realisation de la classe <Filtre> ( fichier Filtre.cpp ) -----------------

//------------- Include système ------------------------------------------------------------
#include <cstring>
#include <iostream>
using namespace std;

//------------- Include personnel ----------------------------------------------------------
#include "Filtre.h"

//------------- Constantes -----------------------------------------------------------------


//------------- Methodes publiques ---------------------------------------------------------

bool FiltreHeure::LigneEstConforme(const vector<string> infos) const
{
	int h = atoi(infos[0].substr(12, 2).c_str());
	return (h == Heure);	
}

//------------- Surcharge d'opérateurs -----------------------------------------------------

//------------- Constructeurs - Destructeur ------------------------------------------------
Filtre::Filtre()
{ 
#ifdef MAP
	cout << "Appel du constructeur de <Filtre>." << endl;
#endif
}

FiltreHeure::FiltreHeure(int heure) : Filtre(), Heure(heure)
{
#ifdef MAP
	cout << "Appel du constructeur de <FiltreHeure>." << endl;
#endif
}

Filtre::~Filtre()
{
#ifdef MAP
	cout << "Appel du destructeur de <Filtre>." << endl;
#endif 
}

FiltreHeure::~FiltreHeure()
{
#ifdef MAP
	cout << "Appel du destructeur de <FiltreHeure>." << endl;
#endif
}
//------------- Methodes protégées ---------------------------------------------------------
