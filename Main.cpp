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
	string nomGraph("");
	string fichierLog("");

	int heure;
	list<Filtre *> * filtres = nullptr;

	if ( argc == 1 )
	{
		afficherSyntaxe();
		return 0;
	}

	int i = 1;
	while ( i < argc )
	{
		string arg ( argv [ i ] );
		if ( arg == "-g" && i < argc)
		{
			nomGraph = argv [ ++i ];
		}
		else if ( arg == "-e" )
		{
			string extensions[] = { ".js", ".jpg", ".jpeg", ".css", ".bmp", ".png", ".gif", ".ico" };
			unsigned int length = 8;
			Filtre * f = new FiltreExtensions(extensions, length);
			filtres = insererFiltre(filtres, f);

			cout << "Exclusion des images et fichiers web." << endl;
		}
		else if ( arg == "-t")
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
					cout << "ERREUR : L'heure est mal formatée." << endl;
					cout << "Merci de prendre connaissance de la syntaxe :" << endl;
					afficherSyntaxe();
					return 0;	
				}
			}
		}
		else
		{
			fichierLog = argv[i];
			if ( fichierLog.find ( ".log" ) == string::npos )
			{
				cout << "ATTENTION : Le fichier spécifié n'est pas au format .log" << endl
					<< "Il est possible que le programme ne fonctionne pas correctement." << endl;
			}
		}

		++i;
	}

	if(fichierLog != "")
		lireLog(fichierLog, filtres, nomGraph);
	return 0;
} //----- fin de Main

list<Filtre *> * insererFiltre(list<Filtre *> * liste, Filtre * f)
{
	if(liste == nullptr)
		liste = new list<Filtre *>();
	
	liste->insert(liste->begin(), f);
	return liste;
}

void lireLog(string nomFichier, list<Filtre *> * filtres, string nomGraphe)
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

	if(nomGraphe != "")
		g.GenererFichierGraphe(nomGraphe);
}

void afficherSyntaxe()
{
	cout << "L'execution de ce programme nécessite des arguments" << endl;
	cout << "Voici les synthaxes possibles :" << endl;
	cout << "./main nomLog.log" << endl;
	cout << "./main -t xx nomLog.log (avec xx entre 00 et 23)" << endl;
	cout << "./main -g nomGraph.dot nomLog.log" << endl;
	cout << "./main -e nomLog.log" << endl;
}
