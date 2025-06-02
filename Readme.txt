# README — Simulateur de déplacement de fourmis dans une fourmilière

## Présentation

Ce programme simule le déplacement de plusieurs fourmis à travers une fourmilière modélisée comme un graphe de salles reliées par des tunnels. Chaque fourmi doit rejoindre le dortoir (salle d’arrivée) en partant du vestibule (salle de départ), tout en respectant la capacité maximale de chaque salle. Le programme répartit intelligemment les fourmis sur les différents chemins les plus courts disponibles et affiche étape par étape leurs déplacements.

---

## Fonctionnalités principales

- **Définition flexible de la fourmilière** : Ajout de salles avec des capacités personnalisées et création de tunnels entre elles.
- **Simulation multi-fourmis** : Gestion simultanée de dizaines de fourmis avec suivi individuel de leur progression.
- **Respect des contraintes physiques** : Chaque salle a une capacité maximale, évitant les embouteillages et reflétant une contrainte réaliste.
- **Recherche automatique de chemins optimaux** : Calcul de tous les chemins les plus courts entre le point de départ et d’arrivée, puis répartition des fourmis sur ces chemins.
- **Affichage étape par étape** : Visualisation claire des mouvements de chaque fourmi à chaque étape de la simulation.

---

## Avantages

- **Simplicité et clarté** : Le code est structuré de façon lisible et modulaire, facilitant la compréhension et la modification.
- **Réalisme des contraintes** : La gestion des capacités de salles modélise fidèlement les limitations physiques d’une vraie fourmilière[5].
- **Répartition intelligente** : Les fourmis sont automatiquement réparties sur plusieurs chemins pour éviter les blocages.
- **Extensible** : Il est facile d’ajouter de nouvelles salles, tunnels ou de modifier les paramètres de la simulation.
- **Didactique** : Permet de comprendre le fonctionnement d’un graphe, du BFS, et des systèmes multi-agents simples.

---

## Inconvénients

- **Modèle simplifié** : Le comportement des fourmis est déterministe et ne prend pas en compte des phénomènes biologiques complexes comme les phéromones, la prise de décision individuelle, ou la communication indirecte (stigmergie)[5][7].
- **Pas d’aléatoire ni d’adaptation** : Les fourmis suivent des chemins prédéterminés, sans adaptation dynamique à l’environnement ou aux autres agents.
- **Pas d’optimisation avancée** : Le programme n’implémente pas d’algorithmes inspirés de l’intelligence collective comme l’Ant Colony Optimization (ACO)[2][3], ni d’heuristique de type A*.
- **Pas de visualisation graphique** : L’affichage se fait uniquement en console, ce qui limite l’intuitivité pour des configurations complexes.
- **Scalabilité limitée** : Pour des fourmilières très grandes ou un nombre massif de fourmis, la gestion des états et des chemins pourrait devenir coûteuse en mémoire et en temps.

---

## Conclusion

Ce simulateur est un outil pédagogique efficace pour illustrer les déplacements collectifs sous contraintes dans un graphe, mais il reste volontairement simple et n’intègre pas la richesse des comportements observés dans les vraies colonies de fourmis ou dans les algorithmes d’optimisation bio-inspirés. Pour aller plus loin, il serait intéressant d’ajouter des éléments d’aléatoire, de communication indirecte ou d’optimisation collective.