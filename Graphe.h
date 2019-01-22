/*************************************************************************
                           Graphe  -  Structure de Données
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Graphe> (fichier Graphe.h) ----------------
#if ! defined ( GRAPHE_H )
#define GRAPHE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>;
#include <vector>;
#include <unordered_map>;
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

typedef struct
{
	int nbVisites;
	unordered_map<int,int> donneesNoeud;
}noeud;

//------------------------------------------------------------------------
// Rôle de la classe <Graphe>
//
//
//------------------------------------------------------------------------

class Graphe : public Ancetre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    Graphe & operator = ( const Graphe & unGraphe );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Graphe ( const Graphe & unGraphe );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Graphe ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Graphe ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	unordered_map<int,noeud> mapArc;
	vector<string> adresses;
};

//-------------------------------- Autres définitions dépendantes de <Graphe>

#endif // GRAPHE_H

