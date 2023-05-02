/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Johan Voland, Florian Duruz, Guillaume Dunant
 Date creation  : 30.04.2023

 Description    : Programme permettant de tester l'implémentation de la liste
 						doublement chaînée.

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 12.2.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include "testUnitaire.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
   // insererEnTete
   testInsererEntete();

   // insererEnQueue
   testInsererEnqueue();

   // longueur
   testLongueur();

   // supprimerEntete
   testSupprimerEntete();

   // supprimerEnqueue
   testSupprimerEnqueue();

   // supprimerSelonCritere
   testSupprimerSelonCritere();

   // Vider
   testVider();

   // ===============================================

   Liste* l0 = construireTestListe(8);
   //Affichage dans l'ordre
   {
      printf("Affichage de la liste l1");
      afficher(l0, FORWARD);
   }

   //Affichage à l'envers
   {
      printf("Affichage de la liste l1 a l'envers");
      afficher(l0, BACKWARD);
   }
   libererListe(l0);

   return EXIT_SUCCESS;
}