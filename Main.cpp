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
	bool avecArg = false;
	bool exclureImg = false;
	bool avecGraph = false;
	bool selecHeure = false;
	bool fichierLogConnu = false;

	string nomGraph;
	string fichierLog;

	int heure;
	Graphe g;

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
			cout << "Les images et les fichiers web seront exclus." << endl;
			exclureImg = true;
		}
		else if ( arg == "-t" )
		{
			selecHeure = true;
			if ( i < argc )
			{
				try
				{
					heure = stoi ( argv [ ++i ] );
				}
				catch ( std::invalid_argument& e )
				{
					cout << "L'heure est mal formatée." << endl;
					cout << "Ce paramètre a été ignoré." << endl;
					--i;
					selecHeure = false;
				}
			}
		}
		else
		{
			cout << "Votre fichier est en cours d'analyse." << endl;
			fichierLogConnu = true;
			fichierLog = argv[i];
			if ( fichierLog.find ( ".log" ) != string::npos )
			{
				fichierLog = argv [ i ];
			}
			else
			{
				cout << "Le fichier log ne possède pas le bon format (.log exigé)" << endl;
				cout << "Veuillez reessayer" << endl;
				return 0;
			}
		}

		++i;
	}

	if ( exclureImg && fichierLogConnu )
	{
		opeExclu ( fichierLog , g );
		avecArg = true;
	}

	if ( selecHeure && fichierLogConnu )
	{
		opeHeure ( fichierLog , g, heure );
		avecArg = true;
	}

	if ( fichierLogConnu && !avecArg )
	{
		opeSansArg ( fichierLog , g );
	}

	g.afficherTop ( );

	return 0;
} //----- fin de Main


void opeSansArg ( string nomFichier , Graphe & graphMod )
{
	Decoupeur d ( nomFichier );
	while ( d.EstOK ( ) )
	{
		d.LigneSuivante ( );
		if ( d.EstOK ( ) )
		{
			graphMod.Ajouter ( d.DecouperRequete ( ) , d.DecouperReferer ( ) );
		}
	}

}

void opeHeure ( string nomFichier , Graphe & graphMod, int heure )
{
	Decoupeur d ( nomFichier );
	while ( d.EstOK ( ) )
	{
		d.LigneSuivante ( );
		if ( d.EstOK ( ) )
		{
			int heureLigne = stoi ( *(d.DecouperDate ( )) );
			if (heure == heureLigne)
			{
				graphMod.Ajouter ( d.DecouperRequete ( ) , d.DecouperReferer ( ) );
			}
		}
	}

}

void opeExclu ( string nomFichier , Graphe & graphMod )
{
	string requete;
	Decoupeur d ( nomFichier );
	while ( d.EstOK ( ) )
	{
		d.LigneSuivante ( );
		if ( d.EstOK ( ) )
		{
			requete = *( d.DecouperRequete ( ) );
			if ( strlen ( &requete [ 0 ] ) > 5 )
			{
				requete = requete.substr ( strlen ( &requete [ 0 ] ) - 5 , 5 );
			}

			if ( requete.find ( ".js" ) == string::npos && requete.find ( ".jpg" ) == string::npos
				 && requete.find ( ".jpeg" ) == string::npos && requete.find ( ".css" ) == string::npos
				 && requete.find ( ".bmp" ) == string::npos && requete.find ( ".png" ) == string::npos
				 && requete.find ( ".gif" ) == string::npos && requete.find ( ".ico" ) == string::npos )
			{
				graphMod.Ajouter ( d.DecouperRequete ( ) , d.DecouperReferer ( ) );
			}
		}
	}

}
