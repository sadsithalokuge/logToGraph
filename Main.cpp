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

	int i = 1;
	while ( i < argc )
	{
		string arg ( argv [ i ] );
		if (arg == "-g")
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
		else if (arg == "-t")
		{
			try
			{
				heure = stoi ( argv [ ++i ] );
				Filtre * f = new FiltreHeure(heure);
				filtres = insererFiltre(filtres, f);
			}
			catch ( std::invalid_argument& e )
			{
				cerr << "ERREUR : " << argv[i] << " n'a pas le format exigé pour une heure." << endl;
				cerr << "Merci de prendre connaissance de la syntaxe :" << endl;
				afficherSyntaxe();
				return 0;	
			}
		}
		else
		{
			fichierLog = argv[i];
			if ( fichierLog.find ( ".log" ) == string::npos )
			{
				cerr << "ATTENTION : Le fichier spécifié n'est pas au format .log" << endl
					<< "Il est possible que le programme ne fonctionne pas correctement." << endl;
			}
		}

		++i;
	}

	if(fichierLog != "")
	{
		lireLog(fichierLog, filtres, nomGraph);
	}
	else
	{
		cerr << "Aucun fichier de log fournis. Consultez la syntaxe :" << endl;
		afficherSyntaxe();
	}
	
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
	while(d.LigneSuivante())
	{
		g.Ajouter(d.DecouperRequete(), d.DecouperReferer());
	}
	g.afficherTop();

	if(nomGraphe != "")
		g.GenererFichierGraphe(nomGraphe);
}

void afficherSyntaxe()
{
	cout << "LogToGraph, TP C++ n°4." << endl;
	cout << "Voici les synthaxes possibles :" << endl;
	cout << "./analog nomLog.log" << endl;
	cout << "./analog -t xx nomLog.log (avec xx entre 00 et 23)" << endl;
	cout << "./analog -g nomGraph.dot nomLog.log" << endl;
	cout << "./analog -e nomLog.log" << endl;
}
