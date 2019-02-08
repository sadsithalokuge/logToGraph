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
#include <map>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

typedef unordered_map<string* , int> catNode;
typedef multimap<int , string*> catTop;
typedef unordered_map<string , string*> catAdresse;

typedef struct
{
	int nbVisites;
	catNode donneesNoeud;
}noeud;

typedef unordered_map<string* , noeud> catArc;



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

	void afficherTop ();
	// Mode d'emploi :
	//		Affiche les 10 cibles les plus utilisées.
	//		S'il y a moins de 10 cibles dans le log, alors seules ces cibles
	//		sont affichées.
	// Contrat :

    void GenererFichierGraphe(string nomFichier) const;
    // Mode d'emploi :
    // 		Génère un fichier .dot dont le nom est fourni en
    // 		paramètre.

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
	string * InsererString(string * value);
	// Mode d'emploi :
	// 	Teste si la string dont le pointeur est passé en paramètre
	// 	se trouve dans mapStrings. Si oui, elle libère la mémoire 
	// 	de la chaîne passée en paramètre, et retourne le pointeur
	// 	associé à la chaîne équivalente déjà stockée.
	// 	Si la chaîne n'est pas dans mapStrings, elle est insérée
	// 	dedans et la fonction retourne le même pointeur que celui
	// 	passé en paramètre.
	
//----------------------------------------------------- Attributs protégés
	catArc mapArc;
	catAdresse adresses;

};

//-------------------------------- Autres définitions dépendantes de <Graphe>

#endif // GRAPHE_H

