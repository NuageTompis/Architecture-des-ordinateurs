# Compte-rendu séance 2

## Exercice 1
  **a)** En exécutant la fonction main d’un script c la machine de Simon peut allouer au maximum environ **8370000** octets dans la pile correspondante (script ReachStackLimit.c)
Le programme retourne l’erreur Segmentation fault si on essaie d’allouer trop d’octets dans la pile (par exemple **8380000**)

>**Notes :** *L’arithmétique des pointeurs*, c’est la façon dont on incrémente les pointeurs. Par exemple en c, si on déclare la variable p comme un pointeur vers un tableau d’entiers, alors lorsqu’on appelle p++ cela incrémente p de 4 car c’est la taille en octets d’un entier.

  **b)** C’est donc 10^7
  
  **c)** Sur la machine de Simon il est par exemple possible d’allouer 10^10 octets sur le tas mais pas 10^11.

  **d)** Chacune de nos machine utlise la convention little-endian
  
  **e)** 
