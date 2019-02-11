/*************************************************************************
								  Decoupeur
							 -------------------
	début                : 15/01/2019
	copyright            : (C) 2019 par Jacquot Pierre
										Villenave Sophie
*************************************************************************/

//----- Réalisation de la classe <Decoupeur> (fichier Decoupeur.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Decoupeur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Decoupeur::LigneSuivante ( )
{
	if ( fichier )
	{
		do
		{
			getline ( fichier , ligneActuelle );
			DecouperLigne ( );
		} while ( fichier && !FiltresOK ( ) );
	}
	return EstOK ( );
} //----- Fin de Méthode

string * Decoupeur::DecouperDate ( ) const
{
	return new string ( infos [ 0 ] );
}

string * Decoupeur::DecouperRequete ( ) const
{
	return SansArguments ( infos [ 2 ] );
}

string * Decoupeur::DecouperReferer ( ) const
{
	string * p;
	if ( infos [ 4 ].find ( "http://intranet-if.insa-lyon.fr" ) != string::npos )
		p = SansArguments ( infos [ 4 ].substr ( 31 , infos [ 4 ].size ( ) ) );
	else
		p = SansArguments ( infos [ 4 ] );
	return p;
}

string * Decoupeur::DecouperNavigateur ( ) const
{
	return new string ( infos [ 5 ] );
}

bool Decoupeur::EstOK ( ) const
{
	return fichier.good ( );
}

bool Decoupeur::FiltresOK ( ) const
{
	bool conforme = true;
	if ( ListeFiltres != nullptr )
	{
		for ( list<Filtre *>::iterator it = ListeFiltres->begin ( ); it != ListeFiltres->end ( ); ++it )
		{
			if ( !( *it )->LigneEstConforme ( infos ) )
			{
				conforme = false;
				break;
			}
		}
	}
	return conforme;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Decoupeur::Decoupeur ( string nomFichier , list<Filtre *> * liste ) : fichier ( nomFichier ) , ligneActuelle ( "" ) , ListeFiltres ( liste )
{
#ifdef MAP
	cout << "Appel au constructeur de <Decoupeur>" << endl;
#endif
}


Decoupeur::~Decoupeur ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <Decoupeur>" << endl;
#endif
	fichier.close ( );
	if ( ListeFiltres != nullptr )
	{
		for ( list<Filtre*>::iterator it = ListeFiltres->begin ( ); it != ListeFiltres->end ( ); ++it )
		{
			delete ( *it );
		}
		delete ListeFiltres;
	}
} //----- Fin de ~Decoupeur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Decoupeur::DecouperLigne ( )
{
	char separateurs [ ] = { ':', ':', ' ', '"', ' ', ' ', '"', ' ', '"', '"', '"', '"' };
	int indexSep = 0;
	char tampon;
	string motTampon;
	bool enregistrer = false;
	int indexString = 0;
	string stringTampon = "";

	infos.clear ( );

	while ( indexSep < 10 )
	{
		tampon = ligneActuelle [ indexString ];
		if ( tampon == separateurs [ indexSep ] )
		{
			++indexSep;
			if ( enregistrer )
			{
				infos.push_back ( motTampon );
				motTampon = "";
			}
			enregistrer = !enregistrer;
		}
		else if ( enregistrer )
		{
			motTampon += tampon;
		}
		++indexString;
	}
}

string * Decoupeur::SansArguments ( const string & url ) const
{
	//Suppression des valeurs envoyées au serveur par methode GET
	//et des jsession.
	//on se focalise sur la ressource demandée.
	string * p;
	unsigned int posGET = url.find ( "?" );
	unsigned int posJSession = url.find ( ";jsession" );
	if ( posGET == string::npos && posJSession == string::npos )
		p = new string ( url );
	else
	{
		unsigned int posMin = min ( posGET , posJSession );
		p = new string ( url.substr ( 0 , posMin ) );
	}

	return p;
}
