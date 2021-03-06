/*************************************************************************
						Graphe  -  Structure de Données
							 -------------------
	début                : 15/01/2019
	copyright            : (C) 2019 par Jacquot Pierre
										Villenave Sophie
*************************************************************************/

//------- Réalisation de la classe <Graphe> (fichier Graphe.cpp) ---------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Graphe.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Graphe::Afficher ( ) const
{
	for ( catArc::const_iterator it = mapArc.begin ( ); it != mapArc.end ( ); ++it )
	{
		cout << *( it->first ) << " : " << it->second.nbVisites << endl;
		for ( catNode::const_iterator itRef = it->second.donneesNoeud.begin ( );
			  itRef != it->second.donneesNoeud.end ( ); ++itRef )
		{
			cout << " Référence : " << *( itRef->first ) << " : " << itRef->second << endl;
		}
	}
}

void Graphe::Ajouter ( string * cible , string * ref )
{
	cible = InsererString ( cible );
	ref = InsererString ( ref );
	catArc::iterator it = mapArc.find ( cible );
	if ( it == mapArc.end ( ) )
	{
		noeud n;
		n.nbVisites = 1;
		n.donneesNoeud.insert ( pair<string * , int> ( ref , 1 ) );
		pair<string * , noeud> p ( cible , n );
		mapArc.insert ( p );
	}
	else
	{
		it->second.nbVisites++;
		catNode::iterator itRef = it->second.donneesNoeud.find ( ref );
		if ( itRef == it->second.donneesNoeud.end ( ) )
		{
			pair<string * , int> pRef ( ref , 1 );
			it->second.donneesNoeud.insert ( pRef );
		}
		else
		{
			itRef->second++;
		}
	}

}

void Graphe::afficherTop ( )
{
	catTop top;
	int size = 10;

	for ( auto&& item : mapArc )
	{
		top.emplace ( item.second.nbVisites , item.first );
	}

	if ( top.size ( ) < 10 )
	{
		size = top.size ( );
	}

	cout << "Top " << size << " : " << endl;

	int i = 0;
	for ( catTop::iterator it = top.end ( ); i < size; ++i )
	{
		--it;
		cout << *( it->second ) << " : " << it->first << endl;
	}
}

void ecrireDonneesNoeud ( ofstream & fdot , const catArc::const_iterator & it , const catNode & donneesNoeud )
{
	for ( catNode::const_iterator itNode = donneesNoeud.begin ( ); itNode != donneesNoeud.end ( ); ++itNode )
	{
		fdot << "\t\""
			<< *( itNode->first )
			<< "\" -> \""
			<< *( it->first )
			<< "\" [label=\""
			<< itNode->second
			<< "\"];\n";
	}
}

bool Graphe::GenererFichierGraphe ( string nomFichier ) const
{
	bool reussite;
	ofstream fdot ( nomFichier , ofstream::out );
	ofstream ftmp ( "tmp" , ofstream::out );
	if ( fdot )
	{
		fdot << "digraph {" << endl;
		for ( catArc::const_iterator it = mapArc.begin ( ); it != mapArc.end ( ); ++it )
		{
			fdot << "\t\"" << *( it->first ) << "\";\n";
			ecrireDonneesNoeud ( ftmp , it , ( it->second ).donneesNoeud );
		}


		ftmp.close ( );

		ifstream itmp ( "tmp" );
		string tampon;
		while ( itmp )
		{
			getline ( itmp , tampon );
			fdot << tampon << "\n";
		}
		fdot << "}";
		fdot.close ( );
		remove ( "tmp" );
		reussite = true;
	}
	else
	{
		reussite = false;
		fdot.close ( );
		ftmp.close ( );
		remove ( "tmp" );
	}

	return reussite;
}


//------------------------------------------------- Surcharge d'opérateurs
//-------------------------------------------- Constructeurs - destructeur

Graphe::Graphe ( )
{
#ifdef MAP
	cout << "Appel au constructeur de <Graphe>" << endl;
#endif
} //----- Fin de Graphe


Graphe::~Graphe ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <Graphe>" << endl;
#endif
	for ( catAdresse::iterator it = adresses.begin ( ); it != adresses.end ( ); ++it )
	{
		delete ( it->second );
	}
} //----- Fin de ~Graphe


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

string * Graphe::InsererString ( string * value )
{
	string * pointer;
	catAdresse::iterator it = adresses.find ( *value );
	if ( it == adresses.end ( ) )
	{
		pair<string , string *> p ( *value , value );
		adresses.insert ( p );
		pointer = value;
	}
	else
	{
		delete value;
		pointer = it->second;
	}
	return pointer;
}
