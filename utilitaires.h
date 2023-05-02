/*
-----------------------------------------------------------------------------------
Nom du fichier : Utilitaires.h
Auteur(s) : Florian Duruz
Date creation : 01/05/2023
Description : fonctions communes à plusieurs implémentations de liste_dynamiques.c
Remarque(s) : <à compléter>
Compilateur : Mingw-w64 gcc 12.2.0
-----------------------------------------------------------------------------------
*/

#ifndef LABORATOIRE2_UTILITAIRES_H
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define LABORATOIRE2_UTILITAIRES_H

#include "listes_dynamiques.h"


// ------------------------------------------------------------------------------
/**
 * Met la queue et tete de liste à NULL
 * @param liste liste à modifier
 */
void metNullEnteteEnqueue(Liste *liste);
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * Utilitaire pour l'ajout d'un élément dans une liste vide
 * @param liste liste à modifier
 * @param element élément à ajouter
 */
void ajoutAUneListeVide(Liste *liste, Element *element);
// ------------------------------------------------------------------------------

/**
 * fait un memcpy de l'info si cela est possible
 * @param destination destination
 * @param source source
 */
void memcpyInfoSiPossible(Info *destination, const Info* source);


#endif //LABORATOIRE2_UTILITAIRES_H
