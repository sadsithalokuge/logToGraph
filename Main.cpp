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
int main(int argc, char * argv[])
{
	bool exclureImg = false;
	bool avecGraph = false;
	bool selecHeure = false;
	bool fichierLogConnu = false;
	string nomGraph;
	string fichierLog;
	int heure;

	int i = 1;
	while(i < argc)
	{
		string arg(argv[i]);
		if(arg == "-g")
		{
			++i;
			cout << "Nom du fichier à charger : " << argv[i] << endl;
			avecGraph = true;
			nomGraph = argv[i];
		}
		else if(arg == "-e")
		{
			//cout << "Il faut exclure les images." << endl;
			exclureImg = true;
		}
		else if(arg == "-t")
		{
			++i;
			//cout << "A l'heure : " << argv[i] << endl;
			selecHeure = true;
			heure = atoi(argv[i]);

		}
		else
		{
			fichierLogConnu = true;
			fichierLog = argv[i];
		}
		++i;
	}

	fichierLogConnu = true;

	if(fichierLogConnu)
	{
		Graphe g;
		Decoupeur d(fichierLog);
		while(d.EstOK())
		{
			d.LigneSuivante();
			//cout << *(d.DecouperReferer()) << " : " << *(d.DecouperRequete()) << endl;
			g.Ajouter(d.DecouperRequete(), d.DecouperReferer());
			if(d.EstOK())
				g.Ajouter(d.DecouperRequete(), d.DecouperReferer());
		}
		g.Afficher();
	}
} //----- fin de Nom

