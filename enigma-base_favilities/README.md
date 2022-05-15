# Projet simulation Enigma part1

## bugs possibles
- en réalité, les rotations s'effectuent avant l'affichage, mais cet affichage
	correspond à la lettre encodée précédente (?)	càd on doit faire la rotation
	après l'affichage (??) mais du coup le programme en python3 est faux (???)

## BUG
 - si pour un rotor, on set un ground égal à son notch --> bug

## TODOs
- coder les paramètres manquants
	- rotor settings, etc
- avoir l'alphabet dispo dans un fichier
- réadapter le code
- verifications des valeurs en entrée
- pouvoir parametrer la machine avec une clé
- stocker les caractères encodés
- pouvoir faire un graphe avec les stats
- avoir une interface de commandes

## Etapes
- entrée de la lettre c
- rotation des rotors
- passage de c dans les permutateurs
- passage dans les rotors (de droite à gauche)
- passage dans le reflecteur
- passage dans les rotors (de gauche à droite)
- passage dans les permutateurs
- sortie de la nouvelle lettre

## divers
- sens de rotation --> tq 'A' puis 'B', ...
