/*************************************************************************
								    Main
							 -------------------
	début                : 15/01/2019
	copyright            : (C) 2019 par Jacquot Pierre
										Villenave Sophie
*************************************************************************/

//---------- Interface du module <Main> (fichier Main.h) -------------------
#if ! defined ( MAIN_H )
#define MAIN_H

//------------------------------------------------------------------------
// Rôle du module <Main>
// Point d'entrée du programme LogToGraph.
// Gestion de l'interface utilisateur.
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
int main ( int argc , char * argv [ ] );

list<Filtre *> * insererFiltre ( list<Filtre *> * liste , Filtre * f );
// Mode d'emploi :
// 	Insère un pointeur sur un filtre f dans la liste
// 	dont le pointeur est passé en paramètre.
// 	Si celui-ci vaut nullptr, l'espace mémoire nécessaire
// 	est alloué pour la liste.

void lireLog ( string nomFichier , list<Filtre *> * filtres , string nomGraphe = "" );
// Mode d'emploi :
// 	Analyse le contenu du fichier .log fourni en paramètre
// 	en fonction des filtres passés en paramètre.

void afficherSyntaxe ( );
// Mode d'emploi :
// 	Affiche l'aide d'utilisation du programme, en particulier la
// 	liste des arguments possibles.
#endif // MAIN_H

