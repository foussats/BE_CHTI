# BE_CHTI
__Auteurs :__ Léonie GALLOIS, Morgane FOUSSATS, Groupe E1

## Détails
Afin d'observer l'évolution des scores joueur par joueur, on peut mettre un point d'arrêt à la ligne occurences[i]++;  
Afin d'observer le tableau des socres ainsi que le tableau d'occurences on peut regarder l'évolution des ces variables dans le watch window en regardant les valeurs des variables score et occurences.  
Il est également possible de changer le signal envoyé, ce qui change le taux de bruit dans le signal.   
Pour ceci il suffit de changer l'arguement dans la lagine Init_TimingADC_ActiveADC_ff( ADC1, 0x33 );  
Les argumetns possibles sont : 0x33, 0x52, 0x3E, 0x3C, 0x31  
0x3C et 0x31 sont des cas limites c'est-à-dire qu'aucun signal n'est détecté.
               
## Conclusion
Objectif 2 terminé : on a un tableau de score qui est mis à jour lorsque la fréquence du joueur est détectée 
