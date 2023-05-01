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
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Vérifie que l'info entrée est égale à 6.
 *
 * @param position Position à tester.
 * @param info Info à tester.
 * @return True si info est égal à 6, False sinon.
 */
bool checkIf6(size_t position, const Info *info);

/**
 * @brief Test si la position est impaire ou que la valeur est comprise entre 2
 * 		 nombres.
 *
 * @param position Position à tester.
 * @param info Info à tester.
 * @return True si la position est impaire ou que info est compris entre deux
 * 		  valeurs, False sinon.
 */
bool checkPositionImpaire(size_t position, const Info *info);



/**
 * Retourne vrais ou faux en text selon la valeur de b
 * @param b Valeur booléene à regarder
 * @return const char*
 */
const char *boolalpha(bool b) {
   return b ? "vrais" : "faux";
}



int main(void) {

   //Déclaration Info constantes
   const Info i1 = 1;
   const Info i2 = 2;
   const Info i3 = 3;
   const Info i4 = 4;
   const Info i5 = 5;
   const Info i6 = 6;

   //Initialisation
   printf("Initialisation de la liste l1\n");
   Liste *l1 = initialiser();

   //Insertion des éléments en tête et en queue
   printf("Insere %d en queue : ", i3);
   insererEnQueue(l1, &i3);
   afficher(l1, FORWARD);

   printf("Insere %d en tete : ", i2);
   insererEnTete(l1, &i2);
   afficher(l1, FORWARD);

   printf("Insere %d en queue : ", i4);
   insererEnQueue(l1, &i4);
   afficher(l1, FORWARD);

   printf("Insere %d en tete : ", i1);
   insererEnTete(l1, &i1);
   afficher(l1, FORWARD);

   printf("Insere %d en queue : ", i5);
   insererEnQueue(l1, &i5);
   afficher(l1, FORWARD);

   printf("Insere %d en queue : ", i6);
   insererEnQueue(l1, &i6);
   afficher(l1, FORWARD);

   //Affichage de la longueur
   printf("\nLongueur de la liste l1 : %lld\n", longueur(l1));

   //Affichage à l1'envers
   printf("Affichage de la liste l1 a l'envers");
   afficher(l1, BACKWARD);

   //Ajout d'autres valeur puis suppression selon conditions
   printf("Ajout de quelques valeurs : ");
   insererEnQueue(l1, &i6);
   insererEnQueue(l1, &i3);
   insererEnQueue(l1, &i6);
   insererEnTete(l1, &i6);
   afficher(l1, FORWARD);

   printf("Suppresion des valeurs 6 : ");
   supprimerSelonCritere(l1, &checkIf6);
   afficher(l1, FORWARD);

   printf("Suppresion des valeurs aux positions impaires : ");
   supprimerSelonCritere(l1, &checkPositionImpaire);
   afficher(l1, FORWARD);

   //Création d'une nouvelle liste
   Liste *l2 = initialiser();
   insererEnTete(l2, &i1);
   insererEnTete(l2, &i3);
   insererEnTete(l2, &i4);
   printf("\nCreation d'une nouvelle liste : ");
   afficher(l2, FORWARD);

   //Test de l'égalité entre les deux listes et la suppression en tête et en queue
   printf("Les listes sont egales? : %s\n", boolalpha(sontEgales(l1, l2)));

   Info infoSuppr = 0;
   supprimerEnTete(l1, &infoSuppr);
   printf("Suppression en tete dans l1 (info = %d) : ", infoSuppr);
   afficher(l1, FORWARD);

   supprimerEnQueue(l2, &infoSuppr);
   printf("Suppression en queue dans l2 (info = %d) : ", infoSuppr);
   afficher(l2, FORWARD);

   printf("Les listes sont egales? : %s\n", boolalpha(sontEgales(l1, l2)));

   //Suppression du contenu des listes
   printf("Suppression du contenu de l1 : ");
   vider(l1, 0);
   afficher(l1, FORWARD);
   printf("l1 est vide? : %s\n", boolalpha(estVide(l1)));

   size_t pos = 2;
   printf("Suppresion de l2 depuis l'indice %lld : ", pos);
   vider(l2, pos);
   afficher(l2, FORWARD);
   printf("l2 est vide? : %s\n", boolalpha(estVide(l2)));

   pos = 0;
   printf("Suppresion de l2 depuis l'indice %lld : ", pos);
   vider(l2, pos);
   afficher(l2, FORWARD);
   printf("l2 est vide? : %s\n", boolalpha(estVide(l2)));

   //libération de la mémoire
   free(l1);
   free(l2);

   return EXIT_SUCCESS;
}



bool checkIf6(size_t position, const Info *info) {
   (void) position; //Evite le warning "variable unused"
   return *info == 6;
}



bool checkPositionImpaire(size_t position, const Info *info) {
   (void) info;//Evite le warning "variable unused"
   return position % 2;
}
