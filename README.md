# 42sh

![42sh](ressources/42sh.gif)

pour compiler faite la commande :
 - make
 - ./42sh

Création d'un shell à 4 avec pour objectif:  
- Analyse lexicale ("Lexing")  
- Analyse syntaxique ("Parsing")  
- Evaluation d'un AST
- Gestion de l'environnement  
- Gestion du PATH
- Gestion des processus et de leurs interactions
- Gestion de la ligne de commande et du terminal
- Gestion des fichiers

## Features

- Exécution de commande
 - Gestion du job control (`jobs`, `fg`, `bg` et `&`)
 - Édition de ligne en utilisant les termcaps (voir Raccourcis)
 - Gestion des redirections: `>`, `>>`, `<`, `<<`, `>&` et `<&`.
 - Séparateur de commandes (`;`).
 - Opérateurs logiques (`|`, `||` et `&&`)
 - Builtins à la norme POSIX:
	 - `cd`
	 - `echo`
	 - `type`
	 - `exit`
	 - `alias`
	 - `hash`
 - Gestion des variables internes au shell avec les builtins suivants:
	 - `set`
	 - `export`
	 - `<clef>=<valeur>`
	 - `unset`
- Gestions de signaux
- Gestion de l'historique
- Les inhibiteurs: `'`, `"`, `\`

avec comme équipe : @AntoineDemy @leonart92 @Dessidrigami @HPE-EPITECH
