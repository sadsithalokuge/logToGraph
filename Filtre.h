/*************************************************************************
								  Filtre
							 -------------------
	début                : 09/01/2019
	copyright            : (C) 2019 par Jacquot Pierre
										Villenave Sophie
*************************************************************************/

//---------- Interface de la classe <Filtre> (fichier Filtre.h) ----------
#if ! defined ( FILTRE_H )
#define FILTRE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Filtre> :
// Permet de créer des filtres applicables aux lignes d'un log Apache.
// On peut rajouter des filtres en ajoutant un héritier à la classe mère
// Filtre.
//------------------------------------------------------------------------

class Filtre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques

	virtual bool LigneEstConforme ( const std::vector<std::string> & infos ) const = 0;
	//Mode d'emploi :
	//	Retourne vrai si les infos de la ligne passées en paramètres sont
	//	correct du point de vue du filtre.


//-------------------------------------------------- Surchage d'opérateurs
//------------------------------------------- Constructeurs - Destructeurs

	Filtre ( );
	virtual ~Filtre ( );

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Methodes protégées
//----------------------------------------------------- Attributs protégés

};
//------------------------------- Autres définitions dépendantes de Filtre

class FiltreHeure : public Filtre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques

	virtual bool LigneEstConforme ( const std::vector<std::string> & infos ) const;

//------------------------------------------- Constructeurs - Destructeurs

	FiltreHeure ( int heure );
	virtual ~FiltreHeure ( );

//------------------------------------------------------------------ PRIVE

private:
	int Heure;
};


class FiltreExtensions : public Filtre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques

	virtual bool LigneEstConforme ( const std::vector<std::string> & infos ) const;

//------------------------------------------- Constructeurs - Destructeurs

	FiltreExtensions ( string * extensions , unsigned int length );
	// Mode d'emploi :
	// 	Construit un objet en copiant le contenu dans le tableau fourni
	// 	en paramètre dans ExtensionsInterdites.

	virtual ~FiltreExtensions ( );

//------------------------------------------------------------------ PRIVE

private:
	unsigned int NbExtensions;
	string * ExtensionsInterdites;
};
#endif // ! defined ( FILTRE_H )
