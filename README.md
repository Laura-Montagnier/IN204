# IN204 : object-oriented ray tracing project

## Par Laura Montagnier et Nathan Champeil


Il s'agit d'un moteur de rendu 3D basé sur la technique du lancer de rayons, réalisé en C++.  

### Fonctionnalités :  

- Éclairage global : diffusion, reflexion, réfraction
- Primitives géométrique : sphères, plans, unions d'objets
- Sources de lumière
- Différents materiaux : couleur, propension à réfléchir et réfracter, luminosité
- Boîte de Cornell
- Réglages caméra
- Parallélisme OpenMP

Des exemples d'images obtenues à différents moments du développement se trouvent dans le dossier `images/`



### Pistes pour poursuivre le développement

- Bounding volumes
- Textures procedurales ou depuis une image, normal maps
- Profondeur de champ
- Primitives géométriques : cubes, maillage triangulaire...
- Sérialisation des scènes  

### Dépendances : 
- OpenMP
- SDL2
- SDL2_Image

Sous Ubuntu : `sudo apt install libsdl2-dev libsdl2-image-dev`

Faire `make` pour générer l'exécutable `ray_tracer`.
