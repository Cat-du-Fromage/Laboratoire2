/*
-----------------------------------------------------------------------------------
Nom du fichier : Utilitaires.h
Auteur(s) : Johan Voland, Florian Duruz, Guillaume Dunant
Date creation : 01/05/2023
Description : fonctions communes à plusieurs implémentations de liste_dynamiques.c
Remarque(s) : -
Compilateur : Mingw-w64 gcc 12.2.0
-----------------------------------------------------------------------------------
*/

#ifndef LABORATOIRE2_UTILITAIRES_H

#define LABORATOIRE2_UTILITAIRES_H
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "listes_dynamiques.h"


// ------------------------------------------------------------------------------
/**
 * @brief Met la queue et tete de liste à NULL
 * @param liste liste à modifier
 */
void metNullEnteteEnqueue(Liste *liste);
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
/**
 * @brief Utilitaire pour l'ajout d'un élément dans une liste vide
 * @param liste liste actuellement vide à modifier
 * @param element élément à ajouter
 */
void ajoutAUneListeVide(Liste *liste, Element *element);
// ------------------------------------------------------------------------------

/**
 * @brief fait un memcpy de l'info si cela est possible
 * @param destination destination
 * @param source source
 */
void memcpyInfoSiPossible(Info *destination, const Info* source);

/**
 * @brief vérifie si la position entrée est impair
 * @param position position dans la liste
 * @param info inutilisé mais demandé dans le cadre du test unitaire
 * @return true si pair, false si impair
 */
bool estImpair(size_t position, const Info *info);

/**
 * @brief vérifie si l'Info est égal à 6
 * @param position position dans la liste(inutilisé, mais demandé dans le cadre d'un test unitaire)
 * @param info info à comparer
 * @return true si égal à 6, false sinon
 */
bool egalA6(size_t position, const Info *info);


#endif //LABORATOIRE2_UTILITAIRES_H
