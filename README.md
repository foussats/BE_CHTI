# BE_CHTI
__Auteurs :__ Léonie GALLOIS, Morgane FOUSSATS, Groupe E1

## Détails
* Activité 1 : Emission d'un signal carré, possibilité de changer la période avec la variable Période_en_tick
               Pour visualiser le signal, utiliser le Logic Analyzer
* Activité 2 : Calcul de la somme du cosinus au carré et du sinus au carré
               cos²+sin² = 1 pour vérifier ceci on regarde dnoc dans le watch window les valeurs des variables min et max
               Pour ceci mettre un point d'arrêt à la ligne CLOCK_Configure();
               Valeur minimale = 0x3FFF0001 / Valeur maximale = 0x40006114
* Activité 3 : Codage de la DFT
               Vérification des résultats grâce aux tests fournis
               Pour ceci, mettre dans la ligne tab_res[i]=dft(&TabSig2,i); le nom de la table d'échantillons à laquelle on veut appliquer                  la dft
               Pour visualiser les valeurs on observe la varoable tab_res dans le watch window
               
## Conclusion
Objectif 1 terminé : on a une DFT qui fonctionne et qui a été testée.
