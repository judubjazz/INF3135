# TP1: `pandemi.c`

## Description

Décrivez ici le projet. Commencez d'abord par une description générale, puis
donnez ensuite des détails. Indiquez le contexte dans lequel ce travail est
accompli (cours, sigle, enseignant, université).

## Auteur

Indiquez ici votre prénom, nom et code permanent.

## Fonctionnement

Expliquez d'abord en mots comment faire fonctionner le projet (imaginez que la
personne qui l'utilisera ne connaît rien du projet et souhaite seulement
l'exécuter). En particulier, indiquez les commandes qui doivent être entrées
pour la compilation et l'exécution.

## Tests

En tout temps, il est possible de tester le programme en lançant la commande

```sh
./tests.sh
```

ou à l'aide de la cible `check` du Makefile

```sh
make check
```

**Remarque:** Vous devez d'abord implémenter la cible `bin/pandemic` dans le
fichier Makefile pour utiliser le script de tests.

### Format des tests

Le script de tests s'occupe de compiler le programme `pandemic` en utilisant le
Makefile puis de l'exécuter avec les tests trouvés dans le répertoire `tests/`.

Le format des cas de tests est le suivant:

* `test_XX.args` nombre de jour à simuler à passer en argument au programme
* `test_XX.in` carte à saisir dans `stdin`
* `test_XX.res` sortie attendue (`stdout` et `stderr` confondus)

### Générateur de cartes

Le programme `generator` permet de générer des cartes de configuration aléatoirement.
Il est très pratique pour tester votre programme.

Usage:
```sh
Usage: generator <lignes> <colonnes>
```

Exemple d'utilisation:
```sh
make bin/generator
bin/generator 5 10
```

Affiche:
```sh
..X...HX..
Q.XXX...HQ
H..XQ.H...
.XHXXXXX..
...HXXQ.X.
```

## Références

Indiquez ici les références que vous avez utilisé pour compléter le projet.

## État du projet

Indiquez toutes les tâches qui ont été complétés en insérant un `X` entre les
crochets. Si une tâche n'a pas été complétée, expliquez pourquoi.

* [ ] Le nom du dépôt GitLab est exactement `inf3135-hiver2018-tp1` (Pénalité de
  **50%**).
* [ ] L'URL du dépôt GitLab est exactement (remplacer `utilisateur` par votre
  nom identifiant GitLab) `https://gitlab.com/utilisateur/inf3135-hiver2018-tp1`
  (Pénalité de **50%**).
* [ ] Les utilisateurs `kadouche`, `rmTheZ` et `sim590` doivent avoir accès au
  projet en mode *Developer* (Pénalité de **50%**).
* [ ] Le dépôt GitLab est privé (Pénalité de **50%**).
* [ ] Le fichier `.gitignore` a été mis à jour.
* [ ] Le fichier `pandemi.c` a été implémenté.
* [ ] La cible `bin/pandemic` a été ajoutée dans le Makefile.
* [ ] Aucun test exécuté avec la commande `make check` n'échoue.
* [ ] Les sections incomplètes du fichier `README.md` ont été complétées.
