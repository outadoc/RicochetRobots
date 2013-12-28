Ricochet Robots
===============

Projet de 1ère année de DUT Informatique par Baptiste Candellier.

Ricochet Robots est une implémentation en C du jeu de plateau créé par Alex Randolph. L'interface du jeu repose sur ncurses et il est donc jouable en console.


Fonctionnalités
---------------

Ricochet Robots propose un mode solo, un mode multijoueur et un tableau des high-scores, le tout dans une interface textuelle.


Règles globales
---------------

Le jeu se déroule avec 4 robots rouge, vert, bleu, gris sur un plateau de 16 * 16 cases. Le joueur peut déplacer chaque robot comme il le souhaite : le robot se déplace alors dans la direction choisie et jusqu'à ce qu'il rencontre un obstacle (un mur ou un autre robot).

Deux modes de jeu sont disponibles : solo et multijoueur.


* Mode solo

Le but du mode solo est de diriger tour à tour chaque robot sur son objectif correspondant. Le score du joueur correspond au nombre de coups qu'il aura fallu pour que chaque robot capture au moins une fois son objectif.

* Mode multi

Le mode multi se déroule en 4 manches, une pour chaque couleur. Au début de chaque partie, on choisit une couleur au hasard, puis on la retire des choix possibles pour les manches suivantes.

Le but du jeu est alors d'amener le robot de la couleur tirée sur l'objectif correspondant. Au début de chaque manche, on demande à chaque joueur en combien de coups il pense pouvoir atteindre l'objectif.

Le joueur avec le plus petit nombre de coups prévus commence. S'il réussit à atteindre l'objectif sans dépasser le nombre de coups prévus, il gagne la manche. Sinon, c'est au tour du joueur avec le nombre de coups prévus directement supérieur de jouer, et ainsi de suite.

Après les 4 manches, on compte le nombre de victoires de chaque joueur. Celui qui en a le plus gagne la partie.


Chargement des plateaux
-----------------------

Ricochet Robots propose trois méthodes de chargement de plateaux.

* Plateaux prédéfinis

Trois plateaux prédéfinis sont à votre disposition dans le jeu.

* Plateaux aléatoires

Vous pouvez générer facilement de nouveaux plateaux aléatoires depuis le menu de séléction de plateau afin d'étendre la durée de vie du jeu tout en gardant la surprise d'une disposition aléatoire.

* Plateaux chargés depuis un fichier

Il est possible pour l'utilisateur de créer ou télécharger facilement de nouveaux plateaux grâce à un système de chargement de fichiers. Ils sont éditables avec n'importe quel éditeur de texte et donc faciles à partager par la suite.

Vous trouverez un exemple du plateau prédéfini n°1 sous forme de fichier niveau commenté dans level/example.rr, ainsi que d'autres fichiers niveau.
