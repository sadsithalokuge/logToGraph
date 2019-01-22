/*************************************************************************
                           Decoupeur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Decoupeur> (fichier Decoupeur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Decoupeur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Decoupeur::LigneSuivante() 
{//TODO: rajouter des filtres pour la selection.
	if(fichier)
	{
		getline(fichier, ligneActuelle);
		DecouperLigne();
	}
} //----- Fin de Méthode

string Decoupeur::DecouperDate() const
{

	/*string date;
	if(fichier)
	{
		int i;
		for(i = 17; i < 28; ++i)
	       		date += ligneActuelle[i];
	}
	return date;*/
	return infos[0];	
}


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Decoupeur::Decoupeur(string nomFichier) : fichier(nomFichier), ligneActuelle("")
{
#ifdef MAP
    cout << "Appel au constructeur de <Decoupeur>" << endl;
#endif
     infos[0] = string("");
     infos[1] = string("");
     infos[2] = string(""); 
} //----- Fin de Decoupeur


Decoupeur::~Decoupeur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Decoupeur>" << endl;
#endif
    fichier.close();
} //----- Fin de ~Decoupeur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Decoupeur::DecouperLigne()
{
	char separateurs [] = { '[', ']', '"', '"', '"', '"', '"', '"' };
	int indexSep = 0;
	char tampon;
	bool enregistrer = false;
	int indexMot = -1;
	int indexString = 0;

	while(indexSep < 8)
	{
		tampon = ligneActuelle[indexString];
		if( tampon == separateurs[indexSep])
		{
			++indexSep;
			enregistrer = !enregistrer;
			if(enregistrer)
				++indexMot;
		}
		else if(enregistrer)
		{
			infos[indexMot] += tampon;
		}
		++indexString;
	}
}
