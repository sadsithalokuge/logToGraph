/******************************************************************
Créé le : 06 février 2019
par : pierre
e-mail :
******************************************************************/

//-------------- Interface de la classe <Filtre> (fichier Filtre.h) ---------------------
#if ! defined ( FILTRE_H )
#define FILTRE_H

//-------------- Interfaces utilisées -----------------------------
#include <string>
#include <vector>
//-------------- Constantes ---------------------------------------
//-------------- Types --------------------------------------------

//-----------------------------------------------------------------
//Rôle de la classe <Filtre>:
//
//-----------------------------------------------------------------

class Filtre
{
	public:
		//----- Methodes publiques -----
		virtual bool LigneEstConforme(const std::vector<std::string> infos) const = 0;
		//Mode d'emploi :
		//	Retourne vrai si les infos de la ligne passées en paramètres sont
		//	correct du point de vue du filtre.


		//---- Surchage d'opérateurs ----
		//--- Constructeurs - Destructeurs ---
		Filtre();
		virtual ~Filtre();

	protected:
		//----- Methodes protégées -----
		//----- Attributs protégés -----

};
//------------ Autres définitions dépendantes de Filtre ----------

class FiltreHeure : public Filtre
{
	public:
		//----- Methodes publiques -----
		virtual bool LigneEstConforme(const std::vector<std::string> infos) const;
		
		// --- Constructeurs - Destructeurs ---
		FiltreHeure(int heure);
		virtual ~FiltreHeure();
	
	private:
		int Heure;
};


class FiltreExtensions : public Filtre
{
	public:
		//----- Methodes publiques -----
		virtual bool LigneEstConforme(const std::vector<std::string> infos) const;

		//--- Constructeurs - Destructeurs ---
		FiltreExtensions(string * extensions, unsigned int length);
		// Mode d'emploi :
		// 	Construit un objet en copiant le contenu dans le tableau fourni
		// 	en paramètre dans ExtensionsInterdites.

		virtual ~FiltreExtensions();

	private:
		unsigned int NbExtensions;
		string * ExtensionsInterdites;
};
#endif // ! defined ( FILTRE_H )
