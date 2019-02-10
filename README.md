# logToGraph
Analyseur de logs apache pour créer des graphes.

#Utilisation :

Voici la syntaxe d'utilisation du programme :
./analog [args] <fichier.log>

Utiliser la commande sans spécifier d'arguments affichera une aide d'utilisation.

#Liste des arguments :

-e 	: Les requêtes portant sur des fichiers images (.png, .jpeg, .gif...) ne seront pas analysées.

-t <heure> 	: Seules les lignes dont la requête a été reçue entre [heure, heure+1[ seront prises en compte.
		  ATTENTION : heure doit être un nombre entre 0 et 23.

-g <fichier.dot> 	: exporte le résultat de l'éxécution du programme dans un fichier .dot utilisable par GraphViz.
