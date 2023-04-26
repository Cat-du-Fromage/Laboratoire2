/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.h
 Auteur(s)      : Johan Voland, Florian Duruz, Guillaume Dunant
 Date creation  : 26.04.2023

 Description    : Librairie permettant la gestion de listes doublement chaînées
                  non circulaires

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 12.2.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------------------------------------------------------
// Initialisation de la liste.
// N.B. Cette fonction doit obligatoirement être utilisée pour se créer une liste
// car elle garantit la mise à NULL des champs tete et queue de la liste
// Renvoie NULL en cas de mémoire insuffisante
Liste* initialiser(void){
   //Allocation de la mémoire
   Liste* list = (Liste*) malloc(sizeof(Liste));

   //Retourne NULL si la mémoire n'a pas pu être initialisé
   if(list == NULL){
      return NULL;
   }

   //Initialise les pointeurs à NULL
   list->queue = NULL;
   list->tete = NULL;

   //Retourne le pointeur sur la list initialisée
   return list;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste est vide, false sinon.
bool estVide(const Liste* liste){
   return liste->tete == NULL && liste->queue == NULL;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie combien il y a d'éléments dans liste.
size_t longueur(const Liste* liste){

}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Affiche le contenu intégral de liste sous la forme : [info_1,info_2,...]
// Dans le cas d'une liste vide, affiche : []
// En mode FORWARD, resp. BACKWARD, l'affichage se fait en parcourant liste
// dans le sens tete -> queue, resp. queue -> tete.
void afficher(const Liste* liste, Mode mode){}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en tête de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnTete(Liste* liste, const Info* info){
   Element* element =(Element*) malloc(sizeof(Element));

   if(element == NULL){
      return MEMOIRE_INSUFFISANTE;
   }

   Info* infoTmp = malloc(sizeof(Info));
   if( memcpy(infoTmp, info, sizeof(Info)) == NULL){
      return MEMOIRE_INSUFFISANTE;
   }

   element->info = *infoTmp;

   if(estVide(liste)){
      liste->tete = element;
      liste->queue = element;
      element->precedent = NULL;
      element->suivant = NULL;

   } else{
      element->suivant = liste->tete;
      element->precedent = NULL;
      liste->tete->precedent = element;
      liste->tete = element;
   }

   return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en queue de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnQueue(Liste* liste, const Info* info){
   Element* element =(Element*) malloc(sizeof(Element));

   if(element == NULL){
      return MEMOIRE_INSUFFISANTE;
   }

   Info* infoTmp = malloc(sizeof(Info));
   if( memcpy(infoTmp, info, sizeof(Info)) == NULL){
      return MEMOIRE_INSUFFISANTE;
   }

   element->info = *infoTmp;

   if(estVide(liste)){
      liste->tete = element;
      liste->queue = element;
      element->precedent = NULL;
      element->suivant = NULL;

   } else{
      element->suivant = NULL;
      element->precedent = liste->queue;
      liste->queue->suivant = element;
      liste->queue = element;
   }

}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en tête de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnTete(Liste* liste, Info* info) {
   if (estVide(liste))
      return LISTE_VIDE;
};
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en queue de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnQueue(Liste* liste, Info* info);
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste qui
// vérifient le critère passé en second paramètre.
// Exemple: on souhaite supprimer de la liste tous les éléments dont la position est
// impaire et pour lesquels info est compris dans un certain intervalle de valeurs
void supprimerSelonCritere(Liste* liste, bool (*critere)(size_t position, const Info* info));
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste
// à partir de la position position
// N.B. Vider à partir de la position 0 signifie vider toute la liste.
void vider(Liste* liste, size_t position);
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste1 et liste2 sont égales (au sens mêmes infos et infos
// apparaissant dans le même ordre), false sinon.
// N.B. 2 listes vides sont considérées comme égales.
bool sontEgales(const Liste* liste1, const Liste* liste2);
// ------------------------------------------------------------------------------


int main() {
   Liste* l = initialiser();
   const Info i4 = 4;
   const Info i5 = 5;
   const Info i6 = 6;
   insererEnTete(l, &i4);
   insererEnTete(l, &i5);
   insererEnQueue(l,&i6);
   return 0;
}
