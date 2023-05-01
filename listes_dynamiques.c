/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : Johan Voland, Florian Duruz, Guillaume Dunant
 Date creation  : 26.04.2023

 Description    : Implémentation des fonctions de la librairie permettant la
 						gestion de listes doublement chaînées non circulaires.

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 12.2.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include "utilitaires.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------------------------------------------------------
/**
 * @brief Initialisation de la liste.
 *
 * @return Liste construite ou NULL en cas de mémoire insuffisante.
 */
Liste *initialiser(void) {
   //Allocation de la mémoire
   Liste *list = (Liste *) malloc(sizeof(Liste));

   //Retourne NULL si la mémoire n'a pas pu être initialisée
   if (list == NULL) return NULL;

   //Initialise les pointeurs à NULL
   metNullEnteteEnqueue(list);

   //Retourne le pointeur sur la list initialisée
   return list;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Test si la liste est vide.
 *
 * @param liste Liste à tester.
 * @return True si la liste est vide, False sinon.
 */
bool estVide(const Liste *liste) {
   return liste->tete == NULL && liste->queue == NULL;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Renvoie combien il y a d'élément dans liste.
 *
 * @param liste Liste à parcourir.
 * @return Nombre d'éléments dans la liste.
 */
size_t longueur(const Liste *liste) {
   size_t compteur = 0;
   Element *actuel = liste->tete;

   //Incrémente le compteur tant que l'élément actuel n'est pas un pointeur NULL
   while (actuel) {
      ++compteur;
      actuel = actuel->suivant;
   }

   return compteur;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Affiche le contenu intégral de liste.
 *
 * @param liste Liste à afficher.
 * @param mode Si FORWARD, l'affichage se fait du début à la fin de la liste sinon il
 * 				se fait dans le sens inverse.
 */
void afficher(const Liste *liste, Mode mode) {
   //Initialise le pointeur qui parcourira la liste
   Element *actuel = mode == FORWARD ? liste->tete : liste->queue;

   //Affiche les valeurs du tableau
   printf("[");
   while (actuel) {
      printf("%d", actuel->info);
      actuel = mode == FORWARD ? actuel->suivant : actuel->precedent;
      if (!actuel) break;
      printf(",");
   }
   printf("]\n");
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Insère un nouvel élément en tête de liste.
 *
 * @param liste Liste où on doit insérer l'élément.
 * @param info Information contenue dans le nouvel élément.
 * @return OK si l'insertion s'est déroulée avec succès ou MEMOIRE_INSUFFISANTE
 * 		  s'il n'y a pas assez de mémoire pour créer l'élément.
 */
Status insererEnTete(Liste *liste, const Info *info) {

   //Alloue la mémoire pour le nouvel élément
   Element *element = (Element *) malloc(sizeof(Element));
   if (!element) return MEMOIRE_INSUFFISANTE;

   //Copie la valeur de info
   memcpyInfoSiPossible(&element->info, info);

   //Si la liste est vide, met l'élément en tant que tête et queue de la liste
   if (estVide(liste)) {
      ajoutAUneListeVide(liste, element);
   } else {
      //Lie le nouvel élément avec l'ancienne tête de liste
      element->suivant = liste->tete;
      element->precedent = NULL;
      liste->tete->precedent = element;
      liste->tete = element;
   }

   return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Insère un nouvel élément en fin de liste.
 *
 * @param liste Liste où on doit insérer l'élément.
 * @param info Information contenue dans le nouvel élément.
 * @return OK si l'insertion s'est déroulée avec succès ou MEMOIRE_INSUFFISANTE
 * 		  s'il n'y a pas assez de mémoire pour créer l'élément.
 */
Status insererEnQueue(Liste *liste, const Info *info) {

   //Alloue la mémoire pour le nouvel élément
   Element *element = (Element *) malloc(sizeof(Element));
   if (!element) return MEMOIRE_INSUFFISANTE;

   //Copie la valeur de info
   memcpyInfoSiPossible(&element->info, info);

   //Si la liste est vide, met l'élément en tant que tête et queue de la liste
   if (estVide(liste)) {
      ajoutAUneListeVide(liste, element);
   } else {
      //Lie le nouvel élément avec l'ancienne queue de liste
      element->suivant = NULL;
      element->precedent = liste->queue;
      liste->queue->suivant = element;
      liste->queue = element;
   }
   return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Supression de l'élément en tête de liste.
 *
 * @param liste Liste contenant l'élément à supprimer.
 * @param info Info stockée en tête de liste.
 * @return LISTE_VIDE si la liste est vide, OK sinon.
 */
Status supprimerEnTete(Liste *liste, Info *info) {
   //Vérifie que la liste n'est pas vide
   if (estVide(liste)) return LISTE_VIDE;

   //Copie la valeur de info en tête
   memcpyInfoSiPossible(info, &liste->tete->info);

   //S'il n'y a qu'un élément
   if (!liste->tete->suivant) {
      free(liste->tete);
      metNullEnteteEnqueue(liste);
   } else {
      //Place le second élément en tête et supprime l'actuel premier
      liste->tete = liste->tete->suivant;
      free(liste->tete->precedent);
      liste->tete->precedent = NULL;
   }

   return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Supression de l'élément en queue de liste.
 *
 * @param liste Liste contenant l'élément à supprimer.
 * @param info Info stockée en queue de liste.
 * @return LISTE_VIDE si la liste est vide, OK sinon.
 */
Status supprimerEnQueue(Liste *liste, Info *info) {
   //Vérifie que la liste n'est pas vide
   if (estVide(liste)) return LISTE_VIDE;

   //Copie la valeur de info en queue
   memcpyInfoSiPossible(info, &liste->queue->info);

   //S'il n'y a qu'un élément
   if (!liste->queue->precedent) {
      free(liste->queue);
      metNullEnteteEnqueue(liste);
   } else {
      //Place l'avant-dernier élément en queue et supprime l'actuel dernier
      liste->queue = liste->queue->precedent;
      free(liste->queue->suivant);
      liste->queue->suivant = NULL;
   }

   return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Supression des éléments de la liste vérifant le paramètre critere.
 *
 * @param liste Liste contentant les éléments à supprimer.
 * @param critere Fonction définissant le critère des éléments à supprimer.
 */
void supprimerSelonCritere(Liste *liste, bool (*critere)(size_t position, const Info *info)) {
   size_t compteur = 1;
   Element *element = liste->tete;

   while (element) {
      //Si le critère pour l'élément est rempli
      if (critere(compteur, &element->info)) {
         //Supprime l'élément de liste
         if (element->precedent && element->suivant) {
            element->precedent->suivant = element->suivant;
            element->suivant->precedent = element->precedent;
         } else if (element == liste->tete && element == liste->queue) {
            metNullEnteteEnqueue(liste);
         } else if (element == liste->tete) {
            liste->tete = element->suivant;
            liste->tete->precedent = NULL;
         } else if (element == liste->queue) {
            liste->queue = element->precedent;
            liste->queue->suivant = NULL;
         }

         //Passe à l'élément suivant et libère la mémoire
         Element *tmp = element;
         element = element->suivant;
         free(tmp);

      } else {
         //Passe à l'élément suivant
         element = element->suivant;
      }

      //Incrémente le compteur
      ++compteur;
   }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Suppression des éléments de la liste à partir d'une position.
 *
 * @param liste Liste contenant les éléments à supprimer.
 * @param position Position à partir de laquelle il faut supprimer les éléments.
 */
void vider(Liste *liste, size_t position) {
   //Obtient le dernier élément à ne pas supprimer
   Element *elementAGarder = liste->tete;
   for (size_t i = 1; i < position - 1; i++) {
      if (elementAGarder == NULL) break;
      elementAGarder = elementAGarder->suivant;
   }

   //Si le dernier élément à garder ne dépasse pas la taille max (et donc vaut NULL)
   //ou si on supprime tout
   if (elementAGarder != NULL || position == 0) {
      Status status = OK;
      //Supprime l'élément en fin tant qu'on atteint pas le dernier élément à grader
      while (liste->queue != elementAGarder || (status == OK && position == 0)) {
         status = supprimerEnQueue(liste, NULL);
      }
   }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Vérifie que deux listes sont égales.
 *
 * @param liste1 Première liste à tester.
 * @param liste2 Seconde liste à tester.
 * @return True si les deux liste sont égales, false sinon.
 */
bool sontEgales(const Liste *liste1, const Liste *liste2) {
   Element *el1 = liste1->tete;
   Element *el2 = liste2->tete;

   //Retourne true si les deux listes sont vides
   if (el1 == NULL && el2 == NULL) return true;

   //Vérifie que les 2 listes ont la même longueur
   if (longueur(liste1) == longueur(liste2)) {
      //Tant que les deux infos sont identiques
      while (el1->info == el2->info) {
         //Passe aux éléments suivants
         el1 = el1->suivant;
         el2 = el2->suivant;

         //Renvoie true s'il n'y a plus d'élément dans les deux listes
         if (el1 == NULL && el2 == NULL) return true;
      }
   }
   return false;
}
// ------------------------------------------------------------------------------
