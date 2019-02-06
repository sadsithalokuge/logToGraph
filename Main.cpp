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

	int i = 1;
	while ( i < argc )
	{
		string arg ( argv [ i ] );
		if ( arg == "-g" )
		{
			avecGraph = true;
		}
		else if ( arg == "-e" )
		{
			cout << "Les images et les fichiers web sont exclus." << endl;
			exclureImg = true;
		}
		else if ( arg == "-t" )
		{
			selecHeure = true;
			if ( i < argc )
			{
				heure = stoi ( argv [ ++i ] );
			}
		}
		else
		{
			cout << "Votre fichier a bien été analysé." << endl;
			fichierLogConnu = true;
			fichierLog = argv [ i ];
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


Graphe opeSansArg ( string nomFichier , Graphe & graphMod )
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

	return graphMod;
}

Graphe opeHeure ( string nomFichier , Graphe & graphMod, int heure )
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

	return graphMod;
}

Graphe opeExclu ( string nomFichier , Graphe & graphMod )
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

	return graphMod;
}