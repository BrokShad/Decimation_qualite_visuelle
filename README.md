# Decimation qualite visuelle

**Related work :**

https://hal.archives-ouvertes.fr/hal-02155733/document   
Anass Nouri, Christophe Charrier, Olivier Lezoray   
Calcul de la saillance globale d'un objet (prise en compte de la saillance visuel et de la saillance géométrique)   
 
https://www.google.com/url?sa=t&source=web&rct=j&url=https://hal.archives-ouvertes.fr/tel-01418334/file/These_finale2016_AnasNouri.pdf&ved=2ahUKEwiT4cri24bnAhXpxoUKHUmYCAEQFjABegQIBhAQ&usg=AOvVaw0iWDuqVTfaxCKjrfLiw6lF   
Anass Nouri   
Saillance visuelle des maillages 3D non colorés par patchs locaux adapatatifs   

https://www.cs.cmu.edu/~./garland/Papers/quadrics.pdf   
M. Garland, P. S. Heckbert   
Simplification par mesur d'erreur quadratique   

http://hhoppe.com/newqem.pdf   
H. Hoppe   
Simplification par mesur de la ""métrique quadrique"   

Differentes implémentations de simplification par mesur de l'erreur quadrique :   
https://github.com/YuxingZhang/meshsimplification   
https://github.com/ataber/mesh-simplify   
https://github.com/sp4cerat/Fast-Quadric-Mesh-Simplification   

**Resultats**  

77 Remeshing Poisson :  
 - Nombre de face : 294116
 - Nombre sommets : 147061
 - Score de qualité visuelle :  

Statue Remeshing Poisson :  
 - Nombre de face : 361336
 - Nombre sommets : 182743
 - Score de qualité visuelle :  
 
77 Remeshing Poisson Decimation fast Quadric 0.1 Threshold 0.8 :  
 - Nombre de face : 29412
 - Nombre sommets : 14709
 - Score de qualité visuelle :  
 
Statue Remeshing Poisson Decimation fast Quadric 0.1 Threshold 0.2 :  
 - Nombre de face : 36134
 - Nombre sommets : 18267
 - Score de qualité visuelle :  
 
 77 Remeshing Poisson Decimation Meshlab Quadric 0.1 Threshold 0.8 :  
 - Nombre de face : 29410
 - Nombre sommets : 14708
 - Score de qualité visuelle :  
 
 Statue Remeshing Poisson Decimation Meshlab Quadric 0.1 Threshold 0.2 :  
 - Nombre de face : 36133
 - Nombre sommets : 18628
 - Score de qualité visuelle :  
 
 **Sprint**  
 
 _17/01/2020 - 27/01/2020_ : 
 - Dans ce sprint nous allons essayer de déterminer quels éléments font varier le score de qualité visuelle
 - Remaillage des nuages de point de "77" et "statue3" 
 - Décimation en 4 maillages différents (differents threshold et deux méthodes) 
 
