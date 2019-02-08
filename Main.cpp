/*************************************************************************
						   Main  -  description
							 -------------------
	début                : $DATE$
	copyright            : (C) $YEAR$ par $AUTHOR$
	e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Main> (fichier Main.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <cstring>
#include <list>
using namespace std;
//------------------------------------------------------ Include personnel
#include "Main.h"
#include "Decoupeur.h"
#include "Graphe.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc , char * argv [ ] )
{
	bool fichierLogConnu = false;
	bool avecGraph;
	string nomGraph;
	string fichierLog;

	int heure;
	Graphe g;
	list<Filtre *> * filtres = nullptr;

	if ( argc == 1 )
	{
		cout << "L'execution de ce programme nécessite des arguments" << endl;
		cout << "Voici les synthaxes possibles :" << endl;
		cout << "./main nomLog.log" << endl;
		cout << "./main -t xx nomLog.log (avec xx entre 00 et 23)" << endl;
		cout << "./main -g nomGraph.dot nomLog.log" << endl;
		cout << "./main -e nomLog.log" << endl;

		return 0;
	}

	int i = 1;
	while ( i < argc )
	{
		string arg ( argv [ i ] );
		if ( arg == "-g" ) //TODO : vérifier qu'on a le droit d'écrire 
		{
			if ( i < argc ) //TODO : Idiot Proof s'il oublie le nom...
			{
				nomGraph = argv [ ++i ];
			}
			avecGraph = true;
		}
		else if ( arg == "-e" )
		{
			string extensions[] = { ".js", ".jpg", ".jpeg", ".css", ".bmp", ".png", ".gif", ".ico" };
			unsigned int length = 8;
			Filtre * f = new FiltreExtensions(extensions, length);
			filtres = insererFiltre(filtres, f);

			cout << "Les images et les fichiers web seront exclus." << endl;
		}
		else if ( arg == "-t" )
		{
			if ( i < argc )
			{
				try
				{
					heure = stoi ( argv [ ++i ] );
					Filtre * f = new FiltreHeure(heure);
					filtres = insererFiltre(filtres, f);
				}
				catch ( std::invalid_argument& e )
				{
					cout << "L'heure est mal formatée." << endl;
					cout << "Ce paramètre a été ignoré." << endl;
					--i;
				}
			}
		}
		else
		{
			cout << "Votre fichier est en cours d'analyse." << endl;
			fichierLogConnu = true;
			fichierLog = argv[i];
			if ( fichierLog.find ( ".log" ) == string::npos )
			{
				cout << "Le fichier log ne possède pas le bon format (.log exigé)" << endl;
				cout << "Veuillez reessayer" << endl;
				return 0;
			}
		}

		++i;
	}

	if(fichierLogConnu)
		lireLog(fichierLog, filtres);
	return 0;
} //----- fin de Main

list<Filtre *> * insererFiltre(list<Filtre *> * liste, Filtre * f)
{
	if(liste == nullptr)
		liste = new list<Filtre *>();
	
	liste->insert(liste->begin(), f);
	return liste;
}

void lireLog(string nomFichier, list<Filtre *> * filtres)
{
	Graphe g;
	Decoupeur d(nomFichier, filtres);
	while(d.EstOK())
	{
		d.LigneSuivante();
		if(d.EstOK())
			g.Ajouter(d.DecouperRequete(), d.DecouperReferer());
	}
	g.afficherTop();
}
