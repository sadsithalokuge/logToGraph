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
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

typedef struct
{
	int nbVisites;
	unordered_map<string*,int> donneesNoeud;
}noeud;

//------------------------------------------------------------------------
// Rôle de la classe <Graphe>
//
//
//------------------------------------------------------------------------

class Graphe
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void Afficher() const;
    // Mode d'emploi :
    // 		Affiche le contenu du Graphe. Chaque couple clé/valeur est
    // 		affiché.
   

    void Ajouter(string * cible, string * ref); 
    // Mode d'emploi :
    //		Ajoute la chaîne de caractère pointée par cible dans la
    //		structure de données. Si celle ci est déja présente, son
    //		compteur de visite sera juste incrémenté.
    //		De même, la référence de la cible sera insérée dans la
    //		structure de données du Noeud si elle n'est pas présente.
    //		Sinon, son compteur sera lui aussi incrémenté.
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
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
	unordered_map<string*,noeud> mapArc;
	vector<string*> adresses;
};

//-------------------------------- Autres définitions dépendantes de <Graphe>

#endif // GRAPHE_H

