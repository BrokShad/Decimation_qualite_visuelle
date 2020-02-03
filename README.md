# Decimation qualite visuelle
 
 **Sprint**  
 
 _17/01/2020 - 27/01/2020_ : 
 - Dans ce sprint nous allons essayer de déterminer quels éléments font varier le score de qualité visuelle
 - Remaillage des nuages de point de "77" et "statue3" 
 - Décimation en 4 maillages différents (differents threshold et deux méthodes) 
 
 _27/01/2020 - 04/02/2020_ : 
 - Génération de plusieurs maillages issus de la décimation de "missVN" via plusieurs méthodes.
 -- MC Edge Collapse, une méthode optimisée pour la décimation de maillage issus de marching cubes.
 -- Clustering, une méthode effectuant des collapses en discrétisant des sections du maillages à l'aide d'une grille 3D régulière.
 -- Quadric Based Edge Collapse
