# Ricochet Robots
## Logo
	    ____  ______________  ________  ______________
	   / __ \/  _/ ____/ __ \/ ____/ / / / ____/_  __/
	  / /_/ // // /   / / / / /   / /_/ / __/   / /
	 / _, _// // /___/ /_/ / /___/ __  / /___  / /
	/_/ ||||__||||__||||__||||__|||_|||||||_/ /_/
	   / __ \/ __ \/ __ )/ __ \/_  __/ ___/
	  / /_/ / / / / __  / / / / / /  \__ 
	 / _, _/ /_/ / /_/ / /_/ / / /  ___/ /
	/_/ |_|\____/_____/\____/ /_/  /____/


Projet de 1ère année de DUT Info par Baptiste Candellier.

## Description
On se propose dans un premier temps de réaliser une variante du jeu Ricochets Robots : https://fr.wikipedia.org/wiki/Ricochet_Robots. La variante que l’on veut réaliser se joue jeul.  

### Spécifications
Le jeu se joue sur une grille fermée de 16 par 16 cellules avec 4 robots de couleurs différentes (rouge, vert, bleu, gris), un ensemble d’obstacles (murs) et une cible qui se trouve dans une cellule de la grille.

Pour déplacer un robot, le joueur choisit une direction (Nord, Sud, Est, Ouest) et le robot se déplace en ligne droite jusqu’à rencontrer un obstacle ou un robot. Le but du jeu est de déplacer chacun à leur tour les 4 robots afin d’atteindre la cible. Il faut pour cela éventuellement déplacer un autre robot.

Une fois que les 4 robots auront tous atteint au moins une fois la cible, on déterminera le score du joueur par le nombre de déplacements nécessaires à la résolution du problème.

Les grilles seront construites de manière aléatoire, éditées par un utilisateur ou bien prédéfinies. Trois grilles grilles prédéfinies seront proposées par votre programme. On trouvera des exemples de grilles de jeu ici : http://jeux.prise2tete.fr/p2t-ricochet/p2t-ricochet.php5.

Les positions initiales des robots seront tirées aléatoirement pour une grille aléatoire, ou bien choisies si il s’agit d’une grille éditée par l’utilisateur ou encore déterminées à priori lors de grilles prédéfinies.

Une fois que la version mono-joueur fonctionne, on réalisera dans un deuxième temps, une version multi-joueurs. Le programme final devra permettre de jouer à ces deux versions.

Dans la version multi-joueurs, il y a 4 robots et 4 cibles (de même couleur que les robots). A chaque tou, on tire au hasard une couleur. Chaque joueur indiquent le nombre de déplacements qu’il envisage pour déplacer le robot de la couleur tirée sur la cible de même couleur. Celui qui a trouvé la solution avec le moins de mouvements, déroule sa solution. S’il échoue à résoudre le problème dans le nombre de déplacements qu’il a indiqué préalablement, le joueur qui avait proposé une solution avec un nombre de mouvement immédiatement inférieur, tente sa chance à son tour et ainsi de suite. Le jeu se joueura en 4 tours (un tour pour chaque couleur). A la fin du jeu, on compte le nombre d’objectifs qu’a atteint des joueurs pour déterminer le gagnant. Comme dans la version mono-joueur, durant le tour les joueurs peuvent utiliser les quatre robots comme ils le souhaitent.

Votre programme devra permettre de visualiser une séquence de jeu en affichant à chaque tour : le plateau de jeu, qui doit jouer (dans le cas de la version à plusieurs joueurs), le score courant du joueur (ou des joueurs).

Pour ceux qui veulent aller plus loin, vous pouvez réaliser au choix : des graphiques avec animation, une version en 3D, une version pour jouer à plusieurs en réseau, une version pour jouer à plusieurs sur Internet.