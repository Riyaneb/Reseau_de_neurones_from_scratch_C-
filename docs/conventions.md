# Conventions du projet

## Type scalaire
Le type réel utilisé dans tout le projet est un alias unique, défini dans
include/math/Types.hpp. Aucun fichier n'écrit "double" en dur : tout passe
par cet alias, pour pouvoir basculer vers une autre précision plus tard
sans toucher le reste du code.

## Type des indices et dimensions
Les indices, lignes, colonnes et tailles utilisent un type entier SIGNÉ
(pas le type non signé par défaut de la STL), défini lui aussi dans
Types.hpp. Raison : les calculs d'indices et de tailles font régulièrement
des soustractions (différence de dimensions, taille restante, décalage),
et un type non signé qui passe sous zéro ne lève aucune erreur, il boucle
sur une valeur énorme. Un type signé transforme ce genre de bug en un
nombre négatif visible immédiatement, au lieu d'un accès mémoire hors
limites silencieux.

## Stockage matriciel
Toute matrice stocke ses éléments dans un unique bloc contigu, en
ORDRE LIGNE PAR LIGNE (row-major). L'élément (i, j) se trouve à l'indice :

    indice = i * nombre_de_colonnes + j

Aucune classe du projet ne stocke de vecteur de vecteurs.

## Convention de batch
Un batch de données est TOUJOURS représenté par une matrice où :
- chaque LIGNE est un échantillon
- chaque COLONNE est une caractéristique (ou une sortie)

Un seul échantillon reste une matrice à une seule ligne. Il n'existe
aucune fonction ni surcharge "à un seul échantillon" distincte du cas
batch : c'est le même chemin de code pour N=1 et pour N=64.

## Réduction sur le batch
La division par la taille du batch (N) se fait UNIQUEMENT dans la
fonction de perte (Loss). Aucune autre classe ne divise par N.
La somme sur les échantillons, elle, se fait naturellement dans le
produit avec la transposée de l'entrée lors du calcul du gradient des
poids — elle n'a besoin d'aucun code spécifique.

## Nommage
- Identifiants publics (classes, méthodes, fichiers) : en anglais.
- Commentaires et documentation : au choix, cohérent dans un même fichier.
- Fichiers d'en-tête et d'implémentation : même nom que la classe
  qu'ils contiennent (DenseLayer.hpp / DenseLayer.cpp).

## Propriété des objets
Les couches d'un réseau sont possédées exclusivement par ce réseau,
via des pointeurs intelligents à propriété exclusive. Aucune couche
n'est jamais partagée entre deux réseaux ni possédée par plusieurs
objets à la fois.

## Const-correctness
Toute méthode qui n'altère pas l'état de l'objet est marquée constante.
Tout paramètre qui n'est pas modifié par une fonction est passé par
référence constante.

## Gestion des erreurs
- Les erreurs de programmation (dimensions incompatibles, accès hors
  bornes) sont vérifiées par des assertions actives uniquement en mode
  debug, désactivées en mode release pour ne pas coûter de performance.

## Tests
- Le gradient checking utilise une tolérance d'erreur relative de 1e-7
  avec un epsilon de perturbation entre 1e-4 et 1e-6, jamais en simple
  précision.