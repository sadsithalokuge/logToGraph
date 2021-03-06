/*************************************************************************
								    Main
							 -------------------
	début                : 15/01/2019
	copyright            : (C) 2019 par Jacquot Pierre
										Villenave Sophie
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

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( int argc , char * argv [ ] )
{
	string nomGraph ( "" );
	string fichierLog ( "" );

	int heure;
	list<Filtre *> * filtres = nullptr;

	int i = 1;
	while ( i < argc )
	{
		string arg ( argv [ i ] );
		if ( arg == "-g" )
		{
			nomGraph = argv [ ++i ];
		}
		else if ( arg == "-e" )
		{
			string extensions [ ] = { ".js", ".jpg", ".jpeg", ".css", ".bmp", ".png", ".gif", ".ico" };
			unsigned int length = 8;
			Filtre * f = new FiltreExtensions ( extensions , length );
			filtres = insererFiltre ( filtres , f );

			cout << "Exclusion des images et fichiers web." << endl;
		}
		else if ( arg == "-t" )
		{
			try
			{
				heure = stoi ( argv [ ++i ] );
				if ( heure >= 0 && heure <= 23 )
				{
					Filtre * f = new FiltreHeure ( heure );
					filtres = insererFiltre ( filtres , f );
				}
				else
				{
					cerr << "ERREUR : Heure non comprise entre 0h et 23h :" << heure << endl
						 << "Merci de prendre connaissance de la syntaxe :" << endl;
					afficherSyntaxe ( );
					return 0;
				}
			}
			catch ( std::invalid_argument& e )
			{
				cerr << "ERREUR : " << argv [ i ] << " n'a pas le format exigé pour une heure." << endl;
				cerr << "Merci de prendre connaissance de la syntaxe :" << endl;
				afficherSyntaxe ( );
				return 0;
			}
		}
		else
		{
			fichierLog = argv [ i ];
			if ( fichierLog.find ( ".log" ) == string::npos )
			{
				cerr << "ATTENTION : Le fichier spécifié n'est pas au format .log" << endl
					 << "Il est possible que le programme ne fonctionne pas correctement." << endl;
			}
		}

		++i;
	}

	if ( fichierLog != "" )
	{
		lireLog ( fichierLog , filtres , nomGraph );
	}
	else
	{
		cerr << "Aucun fichier de log fournis. Consultez la syntaxe :" << endl;
		afficherSyntaxe ( );
	}

	return 0;
} //----- fin de Main

list<Filtre *> * insererFiltre ( list<Filtre *> * liste , Filtre * f )
{
	if ( liste == nullptr )
		liste = new list<Filtre *> ( );

	liste->insert ( liste->begin ( ) , f );
	return liste;
}

void lireLog ( string nomFichier , list<Filtre *> * filtres , string nomGraphe )
{
	Graphe g;
	Decoupeur d ( nomFichier , filtres );
	if ( d.EstOK ( ) )
	{
		while ( d.LigneSuivante ( ) )
		{
			g.Ajouter ( d.DecouperRequete ( ) , d.DecouperReferer ( ) );
		}
		g.afficherTop ( );
		if ( nomGraphe != "" && !g.GenererFichierGraphe ( nomGraphe ) )
		{
			cerr << "Erreur lors de l'écriture dans le fichier " << nomGraphe << endl
				<< "La création du fichier n'a pas pu avoir lieu." << endl;
		}
	}
	else
	{
		cerr << "Erreur lors de l'ouverture du fichier " << nomFichier << endl;
	}
}

void afficherSyntaxe ( )
{
	cout << "LogToGraph, TP C++ n°4." << endl;
	cout << "Voici les synthaxes possibles :" << endl;
	cout << "./analog nomLog.log" << endl;
	cout << "./analog -t xx nomLog.log (avec xx entre 00 et 23)" << endl;
	cout << "./analog -g nomGraph.dot nomLog.log" << endl;
	cout << "./analog -e nomLog.log" << endl;
}
