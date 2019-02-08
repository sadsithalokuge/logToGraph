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
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main(int argc, char * argv[]);

void opeSansArg (string nomFichier, Graphe & graphAModifier);

void opeHeure ( string nomFichier , Graphe & graphMod , int heure );

void opeExclu (string nomFichier , Graphe & graphAModifier);

#endif // MAIN_H

