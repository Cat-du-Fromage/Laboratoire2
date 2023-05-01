/*
-----------------------------------------------------------------------------------
Nom du fichier : Utilitaires.h
Auteur(s) : Florian Duruz
Date creation : 01/05/2023
Description : <à compléter>
Remarque(s) : <à compléter>
Compilateur : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

//
// Created by Florian Duruz on 01/05/2023.
//

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
 * @param liste
 */
void metNullEnteteEnqueue(Liste *liste);
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * Utilitaire pour l'ajout d'un élément dans une liste vide
 * @param liste
 * @param element
 * @return
 */
void ajoutAUneListeVide(Liste *liste, Element *element);
// ------------------------------------------------------------------------------

/**
 *
 * @param liste
 * @param info
 */
void memcpyInfoSiPossible(Info *destination, const Info* source);


#endif //LABORATOIRE2_UTILITAIRES_H
