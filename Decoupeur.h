/*************************************************************************
                           Decoupeur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Decoupeur> (fichier Decoupeur.h) ----------------
#if ! defined ( DECOUPEUR_H )
#define DECOUPEUR_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include <fstream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Decoupeur>
//
//
//------------------------------------------------------------------------

class Decoupeur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    
    void LigneSuivante();
    // Mode d'emploi :
    // 		Passe à la ligne suivante du fichier lu.

    string DecouperDate() const;
    // Mode d'emploi :
    //		Retourne un string contenant la requête 
    //		HTPP de la ligne actuellement lue par le découpeur.

    string DecouperRequete() const;
    // Mode d'emploi :
    // 		Retourne un string contenant la requête
    // 		HTTP de la ligne actuellement lue par le découpeur.

	string DecouperReferer ( ) const;
	// Mode d'emploi :
	// 		Retourne un string contenant la requête
	// 		HTTP de la ligne actuellement lue par le découpeur.
    
    //int DecouperStatut() const;
    // Mode d'emploi :
    // 		Retourne le code que le serveur a retourné à la requête 
    // 		écrite sur la ligne actuelle du log.

    //int DecouperQuantiteDonnees() const;
    // Mode d'emploi :
    // 		Retourne la quantite de données (en octets) qui a été
    // 		transférée au serveur.
    
    //string DecouperNavigateur() const;
    // Mode d'emploi :
    // 		Retourne un string contenant l'identifiant du 
    // 		navigateur utilisé pour effectuer la requête de 
    // 		la ligne actuelle du log.


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

    Decoupeur(string nomFichier);

    virtual ~Decoupeur();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	void DecouperLigne();	
//----------------------------------------------------- Attributs protégés
	ifstream fichier;
	string ligneActuelle;
	vector<string> infos;
};

//-------------------------------- Autres définitions dépendantes de <Decoupeur>

#endif // DECOUPEUR_H

