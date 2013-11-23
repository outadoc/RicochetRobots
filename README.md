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
Le jeu se joue sur une grille fermée de 16 par 16 cellules avec 4 robots de couleurs différentes (rouge, vert, bleu, gris), un ensemble d’obstacles (murs) et un objectif qui se trouve dans une cellule de la grille.

Pour déplacer un robot, le joueur choisit une direction (Nord, Sud, Est, Ouest) et le robot se déplace en ligne droite jusqu’à rencontrer un obstacle ou un robot. Le but du jeu est de déplacer chacun à leur tour les 4 robots afin d’atteindre l’objectif en s’aidant éventuellement des autres robots. Une fois la mission des 4 robots réalisée, on déterminera le score du joueur par le nombre de déplacements nécessaires.

Les grilles seront construites de manière aléatoire, éditées par un utilisateur ou bien prédéfinies. Trois grilles grilles prédéfinies seront proposées par votre programme. On trouvera des exemples de grilles de jeu ici : http://jeux.prise2tete.fr/p2t-ricochet/p2t-ricochet.php5.

Les positions initiales des robots seront tirées aléatoirement pour une grille aléatoire, ou bien choisies si il s’agit d’une grille éditée par l’utilisateur ou encore déterminées à priori lors de grilles prédéfinies.

Une fois que la version solitaire fonctionne, on réalisera une version multi-joueurs à partir de la description du jeu ici : https://fr.wikipedia.org/wiki/Ricochet_Robots. Le programme final devra permettre de jouer à ces deux versions. Dans la version multi-joueurs, les joueurs utilisent 4 robots et un objectif. Les joueurs jouent simultanément en disant quel est le nombre de déplacements qu’ils envisagent. A la fin du jeu, on compte le nombre d’objectifs de chacun des joueurs pour déterminer le gagnant.

> À chaque tour, un des joueurs retourne une tuile objectif. Le but est alors d'amener le robot de la couleur de la tuile sur la case objectif dont le symbole est identique à celui de la tuile. Si c'est la tuile multicolore qui est tirée, l'objectif est alors d'amener n'importe quel robot sur la case multicolore du plateau.
> Les joueurs jouent simultanément, chacun réfléchissant sur le moyen d'amener le robot en utilisant les règles de déplacement. Lorsque l'un d'entre eux pense avoir trouvé une solution, il annonce en combien de mouvements il compte réaliser l'objectif puis il retourne le sablier. Les autres joueurs ont jusqu'à la fin du sablier pour proposer de meilleures solutions, utilisant moins de mouvements.
> Après l'écoulement du sablier, le joueur qui a la solution comptant le moins de mouvement montre sa solution et remporte la tuile. S'il échoue dans sa démonstration, le joueur qui proposait le nombre de mouvements immédiatement supérieur montre sa solution, etc. jusqu'àce qu'une solution soit valide.

Votre programme devra permettre de visualiser une séquence de jeu en affichant à chaque tour : le plateau de jeu, qui doit jouer (dans le cas de la version à plusieurs joueurs), le score courant du joueur (ou des joueurs).

Pour ceux qui veulent aller plus loin, vous pouvez réaliser au choix : des graphiques avec animation, une version en 3D, une version pour jouer à plusieurs en réseau, une version pour jouer à plusieurs sur Internet.  