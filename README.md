# Geant4-NaI
Codes utilisés dans la simulation du détecteur NaI, et l'analyse des données en Python et C++

Marche à suivre :
- étape 1 : Geant4 - télécharger le fichier Geant4-NaIDetector.zip dans le dossier Geant4. 
- étape 2 : Geant4 - modifier le fichier run_matt.mac du dossier B1/build/ en choisissant le nombre de coups désirés (deux modifications !)
- étape 3 : Geant4 - lancer run_matt.mac avec Geant4 depuis le dossier B1/build/ (après avoir cmake et build bien entendu). Geant4 va s'executer en mode console, et créer un fichier de sortie appelé B1/build/DataG4.txt
- étape 4 : C++ - récupérer le fichier ConsoleApplication1 dans le dossier C++/ et adapter le code (ligne 16) pour qu'il lise le fichier de sortie de l'étape précédente. Choisissez un nom et un emplacement pour le fichier de sortie (ligne 65). Executer le programme. Le programme va s'executer en mode console et produire un fichier de sortie.
- étape 5 : Python - récupérer le fichier de sortie de l'étape précédente, qui contient la fusion des run 1 et 2 de Geant4 (pour les deux énergies). Télécharger le script Python à l'emplacement suivant : Python/Analyse.py. Modifier le code (ligne 13) pour y indiquer le chemin vers le ficher de l'étape précédente.
- étape 6 : Python - télécharger le fichier Python/data_NaI.txt, et l'ajouter dans le dossier qui contient Python/Analyse.py
- étape 7 : Python - modifier les lignes 4-7 pour choisir les paramètres
- étape 8 : Python - lancer ensuite le script Python, qui vas créer 4 graphiques comparant les données de la simulation et du spectre réel.
Félicitaiton ! Vous avez réussi !
