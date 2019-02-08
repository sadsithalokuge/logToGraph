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
	int h = atoi(infos[0].c_str());
	return (h == Heure);	
}

bool FiltreExtensions::LigneEstConforme(const vector<string> infos) const
{
	bool conforme = true;
	for(unsigned int i = 0; i < NbExtensions; ++i)
	{
		
		if(infos[2].find(ExtensionsInterdites[i]) != string::npos)
		{
			conforme = false;
			break;
		}
	}

	return conforme;
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

FiltreExtensions::FiltreExtensions(string * extensions, unsigned int length)
	: Filtre(), NbExtensions(length)
{
#ifdef MAP
	cout << "Appel du constructeur de <FiltreExtensions>." << endl;
#endif
	ExtensionsInterdites = new string[NbExtensions];
	for(unsigned int i = 0; i < NbExtensions; ++i)
	{
		ExtensionsInterdites[i] = extensions[i];
	}
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

FiltreExtensions::~FiltreExtensions()
{
#ifdef MAP
	cout << "Appel du destructeur de <FiltreHeure>." << endl;
#endif
	delete [] ExtensionsInterdites;
}
//------------- Methodes protégées ---------------------------------------------------------
