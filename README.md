# IMA'GALAXY


<img height="200" src="./images/imagalaxy-readme.png">

Projet de synthèse d'image, programmation, et architecture logicielle lors du semestre 3 à l'IMAC, inspiré du jeu Temple Run.

### **Par Clément Bourhis, Sirine Bradai, Sacha Chouvin, et Estelle Thouvenin**

## Librairies
Pour pouvoir compiler correctement le projet, les librairies SDL, OpenGL, et GLEW sont nécessaires. Doxygen est optionnel pour la documentation.

## Compiler le projet
Créer un dossier build à l'emplacement désiré
```
mkdir build
cd build
```

Build le projet depuis le dossier build, penser à mettre le chemin relatif vers le dossier du projet
```
cmake [chemin vers la racine du dossier du projet]
```

Compiler le projet depuis le dossier build
```
make
```

Exécuter le jeu
```
./Jeu/Jeu_Temple_Run
```

Optionnel : générer la documentation Doxygen
```
doxygen
```
(exécuter la commande doxygen depuis le dossier du projet)

## Commandes
### ***Déplacements***
- **Q** : tourner à gauche
- **D** : tourner à droite
- **Z** : sauter

### ***Caméra***
- **clic gauche** : tourner la caméra
- **flèche haut** : avancer la caméra *(depuis la vue centrée sur l'explorateur)*
- **flèche bas** : reculer la caméra *(depuis la vue centrée sur l'explorateur)*
- **molette souris** : avancer ou reculer la caméra *(depuis la vue centrée sur l'explorateur)*
- **C** : changer le type de caméra *(caméra centrée sur l'explorateur ou voir à travers les yeux de l’explorateur)*
- **L** : bloquer la caméra

### ***Divers***
- **U** : sauvegarder la partie en cours
- **Suppr** : depuis le menu, permet de fermer l'application
- **REPLAY** : lancer la partie sauvegardée


## Documentation Doxygen
Pour plus d'informations, ouvrir la documentation Doxygen dans un navigateur : `DocHTML/index.html`