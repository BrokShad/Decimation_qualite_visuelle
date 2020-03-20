# Decimation qualite visuelle

Pour executer un build si la librairie libOpenMesh est manquante:
$ LD_LIBRARY_PATH=/home/$user$/Decimation_qualite_visuelle/OpenMesh/liblinux/
$ export LD_LIBRARY_PATH
 
 **Sprint**  
 
 _17/01/2020 - 27/01/2020_ : 
 - Dans ce sprint nous allons essayer de déterminer quels éléments font varier le score de qualité visuelle
 - Remaillage des nuages de point de "77" et "statue3" 
 - Décimation en 4 maillages différents (differents threshold et deux méthodes)  

reference reduite extrait caracteristiques (courbures, angles, saillance visuelle) 
=> par la nouvelle qualité mini est la qualité du maillage originel
 
 _27/01/2020 - 04/02/2020_ : 
 - Génération de plusieurs maillages issus de la décimation de "missVN" via plusieurs méthodes.
 - MC Edge Collapse, une méthode optimisée pour la décimation de maillage issus de marching cubes.
 - Clustering, une méthode effectuant des collapses en discrétisant des sections du maillages à l'aide d'une grille 3D régulière.
 - Quadric Based Edge Collapse
