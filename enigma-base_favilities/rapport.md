1) présentation d'enigma
	1.1) petit rappels historique
	1.2) la machine dans sont ensemble
		1.1.1) les versions
		1.1.2) fonctionnement global
		1.1.3) utilisation de la machine
	1.3) les rotors
	1.4) le reflecteur
	1.5) le plugboard

2) Les mathématiques du chiffrement d'Enigma
    2.1) la théorie des permutations
    2.2) le caractère involutif de l'Enigma
    2.3) la combinatoire d'enigma
        2.3.1) le systèmes de rotors
        2.3.3) la complexité du tableau de connexions
        2.3.4) combien de clé en tout ?

3) simulation
	3.1) la version choisie
	3.2) le langage
	3.3) quelle organisation (uml)
	3.4) les rotors
	3.5) le reflecteur
	3.6) le plugboard
	
4) casser enigme
	4.1) la solution polonaise : diviser le pb en 2
	4.2) trouver le plugboard
		4.2.1) on connait eps_j et eps_j+3
		4.2.2) on a un texte chiffré
		4.2.3) on a un texte chiffré et son claire
	4.3) trouver l'organisation des rotors
	4.4) les méthodes modernes
		4.4.1) l'indice de coincidence
		4.4.2) les chaines de markov cachées

5) améliorer enigma
	5.1) comment tendre vers le chiffrement de vernam ?
    5.2) d'autre méthode de déchiffrement


##########################################################################################


1.1) petit rappels historique
Enigma est une machine électromécanique* portable servant au chiffrement et au déchiffrement de l'information. Elle fut inventée par l'Allemand Arthur Scherbius, reprenant un brevet du Néerlandais Hugo Koch, datant de 1919. 
Ces machines fonctionnent sur le principe des rotors et des contacts électriques, afin de réaliser des formes de substitution polyalphabétique dont la clef a une longueur gigantesque de l'ordre de centaines de millions de lettres, au lieu de quelques dizaines dans les méthodes artisanales. Elle permet donc une automatisation du chiffrement par substitution.

[photo de la machine]

Son utilisation la plus célèbre fut celle faite par l'Allemagne nazie et ses alliés, avant et pendant la Seconde Guerre mondiale, la machine étant réputée inviolable selon ses concepteurs. Néanmoins un nombre important de messages Enigma ont pu être décryptés. 




1.1.1) les versions
Le terme Enigma désigne en fait toute une famille de machines, car il en a existé de nombreuses et subtiles variantes, commercialisées en Europe et dans le reste du monde à partir de 1923. Elle fut aussi adoptée par les services militaires et diplomatiques de nombreuses nations. 

La machine Enigma standard:Il s’agit de la machine employée par les armées de terre et de l’air allemandes, qui était la plus courante (cf. FIG.2.1). Elle était dans son fonctionnement presque identique à la machine Enigma D vendue dans le commerce. Trois rotors étaient alignés dans le brouilleur.

La machine Enigma M3 :La marine allemande (ReichsmarinedevenueKriegsmarine)employait cette machine à partir de 1933. Elle était sensiblement plus difficile àdécrypter que la machine standard, car bien qu’elle disposait du même nombrede rotors alignés simultanément dans le brouilleur, ceux-ci étaient choisi parmiun lot plus grand, proposant deux rotors en plus des trois initiaux.

La machine Enigma M4 :Cette machine remplaça la machine Enigma M3 en 1942dans les sous-marins et dans les stations sur la côte, et était beaucoup plus com-plexe d’un point de vue cryptographique : quatre rotors étaient alignés simul-tanément dans le brouilleur de celle-ci, les trois premiers étant choisis parmi unlot de huit rotors, et le dernier étant choisi parmi deux autres.

La machine Enigma GouAbwehr Enigma: elle était utilisée par les services secretsallemand. Il s’agit également d’une version à quatre rotors, mais démunie d’untableau de fiches. La rotation des rotors a été choisie rapide, ce qui était perçucomme un difficulté supplémentaire pour d’éventuels cryptanalystes. Mais il s’avèreque cette particularité a ajouté une faille supplémentaire à la machine, une aubainepour les décrypteurs de Bletchley Park.

La machine Enigma des chemins de fer allemandsouRaildienst Enigma: celle-ci dif-férait peu de la machine vendue dans le commerce, elle était utilisée par les ser-vices ferroviaires allemands.
...


1.1.2) fonctionnement global
La machine ressemble à une machine à écrire. Quand on presse sur une touche, deux choses se passent. Premièrement, une lettre s'allume sur un panneau lumineux: c'est la lettre chiffrée. Deuxièmement, un mécanisme fait tourner le rotor de droite d'un cran; toutes les 26 frappes, le deuxième rotor tourne d'un cran, toutes les 676 frappes (26 au carré), c'est le troisième rotor qui tourne d'un cran. Certaines Enigmas avaient 3 rotors, celles de la Kriegsmarine en avaient 4 ou 5 (on peut apercevoir ces 4 cylindres gris sur le dessus de la machine ci-contre). Ces rotors tournants modifient les connexions électriques dans la machine, ce qui fait que la touche "A" allumera peut-être le "B" la première fois, mais le "X" la deuxième, le "E" la troisième, etc. Un "tableau de connexions" et un "réflecteur" complique encore le système.
...


1.1.3) utilisation de la machine
La mise en œuvre est effectuée par deux chiffreurs. La procédure est entièrement manuelle. (Cette procédure ne s'applique qu'à l'Enigma standard de la Heer (armée de terre) et de la Luftwaffe. La Kriegsmarine emploie des variantes plus complexes avec une autre version d'Enigma)

la machine est dabord mise en place : (mise en place des réglages interne et externe)
[photo d'un livre de combinaison de réglages]
    1) Ordre des rotors (Walzenlage) : choix et positionnement des trois rotors prescrits par les instructions (ex : I-V-III).
    2) Disposition de la bague (Ringstellung) des rotors gauche, milieu et droit (ex: 06-20-24 affichés FTX) prescrite par les instructions.
    3) Permutations des fiches du tableau de connexions (Steckerverbindungen) (ex : UA PF, etc.) prescrites par les instructions.
    Un des chiffreurs dispose la machine en conséquence. La procédure continue avec les réglages externes.
    4) Le premier chiffreur dispose les trois rotors sur la position initiale (Grundstellung) définie par les instructions quotidiennes, ex : JCM (c'est la source du « Herivel Tip » qui réduit les spéculations des cryptanalystes à quelques dizaines de combinaisons).
    5) Le premier chiffreur choisit au hasard un réglage initial de rotors et le frappe deux fois, ex : BGZBGZ. C'est la clef brute du message (et la source des fameuses « cillies »).
    6) Le second chiffreur note le résultat affiché par les voyants ; c'est l'indicateur ou clef chiffrée (ex. : TNUFDQ).
    7) Le premier chiffreur dispose ses rotors sur BGZ puis entre au clavier le texte du message en clair, lettre par lettre ; le second chiffreur note les lettres signalées par l'allumage des voyants.



Le message est formaté de la façon suivante, avant émission :
    1) Préambule, en clair, avant le message proprement dit : indicatif radio, groupe date-heure et nombre de lettres du message, plus le Grundstellung (ex. : JCM)
    2) Groupe de cinq lettres comprenant deux lettres-tampons (Füllbuchstaben) suivies du discriminant (Kenngruppe), ex. : JEU, qui distingue les différents réseaux de trafic Enigma et identifie le dossier d'instructions utilisé pour la mise en position initiale (Grundstellung) journalière. Les Britanniques désignent ces réseaux par des mots-codes : exemples Red (trafic général de la Luftwaffe), Yellow (liaisons Heer/Luftwaffe mais en Norvège seulement), etc.
    3) Les six lettres de l'indicateur ou clef chiffrée (ex. : TNUFDQ).
    4) Le message chiffré, en groupes de cinq lettres. Au maximum, 50 groupes de 5 lettres. Les messages plus longs sont découpés en plusieurs messages transmis séparément. Il existe des manuels expliquant comment préparer des messages les plus courts possibles.

Les états-majors allemands multiplient les astuces, certains mots ou expressions sont codés, les alphabets et les nombres sont manipulés, les coordonnées topographiques sont transposées. Le tout aggravé par les erreurs de manipulation et de lecture du morse, la mauvaise qualité de réception des transmissions, l'état de fatigue des personnes impliquées, etc. 


Reception et déchiffrement :
À l'autre bout du réseau, le destinataire capte le message au moyen d'un autre poste radio. Le message est noté noir sur blanc. Il est remis à un chiffreur dont la machine Enigma est déjà réglée en fonction des mêmes instructions quotidiennes (1-2-3) que l'autorité émettrice. Le chiffreur dispose ses rotors sur JCM (4), frappe TNUFDQ (6) et note le résultat, BGZBGZ (5). Ensuite, le chiffreur dispose ses rotors sur BGZ. Le texte est déchiffré lettre par lettre, le second chiffreur note à mesure. 




1.3) les rotors
Les rotors (Walzen en allemand) forment le cœur de la machine Enigma. D'un diamètre d'environ 10 cm, chaque rotor est un disque fabriqué à partir de caoutchouc dur. Sur une face sont disposés en cercle des contacts électriques à aiguilles, équipés de ressorts. Sur l'autre face, le même nombre de contacts plats sont disposés. Les contacts plats et à aiguilles représentent l'alphabet (généralement les 26 lettres)
Une fois les rotors assemblés, les contacts à aiguilles d'un rotor se positionnent en face des contacts plats du rotor voisin, formant ainsi la connexion électrique. À l'intérieur du rotor, un ensemble de 26 câbles électriques assurent les connexions entre les contacts à aiguilles et les contacts plats suivant un schéma compliqué, qui permet le chiffrement des lettres.

[photo + schéma du cablage d'un rotor]

Le rotor utilisé tout seul ne réalise en fait qu'un chiffrement très simple : le chiffrement par substitution.  La complexité de la machine Enigma provient de l'utilisation de plusieurs rotors en série, généralement trois ou quatre, ainsi que le mouvement régulier de ces rotors (à chaque frappe de touche pour le premier). Lorsque 26 lettres ont été pressées, une came entraîne le rotor de la fente suivante et le fait tourner. L'alphabet de substitution est ainsi modifié à chaque pression de touche.



1.4) le reflecteur
À l'exception des machines Enigma modèles A et B, le dernier rotor était suivi d'un réflecteur (Umkehrwalze en allemand). Le réflecteur connecte les sorties du dernier rotor par paire, redirigeant le courant dans les rotors selon un chemin différent. C'est ce réflecteur qui garantit le caractère involutif de l'Enigma : chiffrer est identique à déchiffrer (comme pour le chiffrement par masque jetable). Cependant, le réflecteur empêche également l'Enigma de substituer une lettre à elle-même dans le texte chiffré. C'est une faille majeure qui a été utilisée par les cryptanalystes.

Dans la version commerciale qu'est le modèle C, le réflecteur pouvait être inséré dans deux positions. Dans le modèle D, il pouvait l'être dans 26 positions, mais restait fixe. Dans la version utilisée par l'Abwehr, il était entraîné par un mécanisme semblable à celui des rotors.

Dans les versions pour l'Armée de terre et Armée de l'air, le réflecteur était fixe. Le réflecteur existait en quatre versions. La version d'origine, dite A, fut remplacée par l' Umkehrwalze B le 1er novembre 1937. Une troisième version, l’Umkehrwalze C, fut brièvement utilisée en 1940, peut-être par erreur, et fut cassée par la Hutte 6 de Bletchley Park. La quatrième version, détectée pour la première fois le 2 janvier 1944, avait un réflecteur reconfigurable dénommé l’Umkehrwalze D permettant à un opérateur de modifier les connexions pour la mise à la clef. 



1.5) le plugboard
Les machines des armées, et non les machines commerciales, avaient un tableau de connexion (Steckerbrett) à l'avant de la machine, composé de l'alphabet. Avec des simili-prise jack, des câbles se connectent face à un alphabet pour permuter les deux lettres interconnectés. Quand une touche est pressée, le courant électrique passe d'abord par le câble de la lettre échangé, avant de traverser les rotors, qui fonctionnèrent normalement. Dix paires de lettres sont ainsi permutées chaque jour. C'est la partie de la machine qui possédait les possibilités de connexions les plus élevés, bien plus que les rotors.


##########################################################################################


2) Les mathématiques du chiffrement d'Enigma


//TODO (mais pas dans un traitement de txt...)



##########################################################################################


3.1) la version choisie
La machine Enigma standard : 3 rotors parmi 5, 1 reflecteur fixe
pk ?
    - la machine la plus classique et la plus utilisée
    - la première à avoir été cassée par les alliers (polonais puis anglais)
    - 

3.2) le langage
c++
pk ?


3.3) quelle organisation (uml)



3.4) les rotors



3.5) le reflecteur



3.6) le plugboard



##########################################################################################

4.1) la solution polonaise : diviser le pb en 2
(bcp de formules... à expliciter mais pas sur un traitement de txt)



4.2) trouver le plugboard
	4.2.1) on connait eps_j et eps_j+3
redondant avec la methode polonaise...




	4.2.2) on a un texte chiffré
Cifertext only attack (statistique de Sinkov) : 

f_i = fréquence d'apparition des différentes lettres dans une langue standard fixée,
      i=A, ..., Z
n_i = fréquence d'apparition des différentes lettres dans un texte donné,
      i=A, ..., Z
s=S(i=A, ..., Z) n_i*f_i ; doit être élevée pour correspondre à une langue naturelle

on pose gamma_j l'approximation courrante de eps_j (pas de tableau de connexion initialement, évole au fil de l'algo)

on test toute les possibilités de tableau de connextion à 1 branchement (ie 1 paire de lettres échangées : 26*25/2=325 possibilités) -> les alpha_k. Puis on déchiffre le texte avec alpha_k.gamma_j.alpha_k

on obtient les m_k message possible (k=1...325), pour chacun on calcul la statistique de Sinkov s_k, on concerve le alpha_k tel que s_k est maximale et on calcul gamma_(j+1)=alpha_k.gamma_j.alpha_k

on itère jusqu'à ce qu'il n'y ait plus d'amélioration par la statistique de Sinkov





	4.2.3) on a un texte chiffré et son claire

technique 1 : 
on pose gamma_j l'approximation courrante de eps_j (pas de tableau de connexion initialement, évole au fil de l'algo)
on étudie chaque lettre fausse dans notre approximation courrante

pour chaque lettre fausse on sait que le tableau va contenir les réglages qui modifis la lettre claire en une autre et la lettre chiffrée en une autre

1ere lettre en claire = H
1ere lettre chiffrée = I
le tableau contient les réglages H<->p_H et I<->p_I tel que gamma_0(p_H)=p_I

pour chaque lettre du texte on a 
(p_claire)^gamma_i=p_chiffré, avec i la position dans le texte

on suppose connu le nombre de paire de lettres permutées, on obtient donc la probabilité qu'une lettre prise au hasard ait été échangée. 
puis on utilise le motif de permutation(?) des rotors



technique 2 : (moins de 13 paires)
on prend :
m le text en clair actuel
m' le text avec les reglage du tableau de connexion
t le nombre de branchement restant à trouver

pour chacune des lettres de l'alphabet
on se concentre sur toute les occurence dans m qui sont fausse
on pose x la lettre correspondant dans le texte chiffré
si x à un branchement inconnu
si x n'est pas branchée

For all letters A in the plaintext m compute the frequency of the corresponding letter in the approximate plaintext m'. The letter which has the highest frequency is highly likely to be the one which should be connect to A on the plugboard.
Indeed we expect this letter to occur for a proportion of the letters given by 1 − t/13, all other letters we expect to occur with a proportion of t/(13 · 26) each.







4.3) trouver l'organisation des rotors







4.4) les méthodes modernes
	4.4.1) l'indice de coincidence
	4.4.2) les chaines de markov cachées





##########################################################################################

5) améliorer enigma
	5.1) comment tendre vers le chiffrement de vernam ?
    5.2) d'autre méthode de déchiffrement





##########################################################################################

biblio/webo-graphie

Cryptography: An Introduction Nigel Smart

The Index of Coincidence and Its Application in Cryptonalysis William F Friedman

ars cryptographia (https://www.apprendre-en-ligne.net/crypto/activites/index.html)

les carnets de laboratoire de turing (http://www.turingarchive.org/browse.php/C/30)

https://webusers.imj-prg.fr/~razvan.barbaud/ImageDesMaths/enigma.html

http://users.telenet.be/d.rijmenants/en/enigmatech.htm#maths
