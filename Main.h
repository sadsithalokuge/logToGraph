/*************************************************************************
                           Main  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <Main> (fichier Main.h) -------------------
#if ! defined ( MAIN_H )
#define MAIN_H

//------------------------------------------------------------------------
// Rôle du module <Main>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "Graphe.h"
#include "Filtre.h"
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main(int argc, char * argv[]);

list<Filtre *> * insererFiltre(list<Filtre *> * liste, Filtre * f);
// Mode d'emploi :
// 	Insère un pointeur sur un filtre f dans la liste
// 	dont le pointeur est passé en paramètre.
// 	Si celui-ci vaut nullptr, l'espace mémoire nécessaire
// 	est alloué pour la liste.

void lireLog(string nomFichier, list<Filtre *> * filtres);
// Mode d'emploi :
// 	Analyse le contenu du fichier .log fourni en paramètre
// 	en fonction des filtres passés en paramètre.

#endif // MAIN_H

