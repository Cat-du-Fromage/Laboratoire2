/*
-----------------------------------------------------------------------------------
Nom du fichier : testUnitaire.h
Auteur(s) : Johan Voland, Florian Duruz, Guillaume Dunant
Date creation : 02/05/2023
Description : Tests unitaires des fonctions implémentées dans le de ce laboratoire.
Remarque(s) : Certains cas limites n'ont pas pu être étudié comme les
              taille maximale des types dû à un manque de RAM et probablement d'optimization
Compilateur : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#ifndef LABORATOIRE2_TESTUNITAIRE_H
#define LABORATOIRE2_TESTUNITAIRE_H
#include <stdio.h>
#include <stdlib.h>
#include "listes_dynamiques.h"
#include "utilitaires.h"

#define btoa(x) ((x)?"true":"false")

/**
 * @brief Nettoye la mémoire et les pointeurs
 * @param liste liste à supprimer
 */
void libererListe(Liste* liste);

/**
 * @brief Construction d'une liste d'une taille donnée et avec les valeurs initialisé commençant par 0 et s'incrémentant de 1
 * @param numElement nombre d'élément souhaité
 * @return liste avec contenu initialisé
 */
Liste* construireTestListe(size_t numElement);

/**
 * @brief Construit une liste initialisant les valeurs selon un tableau (utilise enqueue)
 * @param valeurs valeurs à initialiser dans la liste
 * @param numvaleur taille du tableau donné
 * @return liste avec objets initialisés selon les valeurs données
 */
Liste* construireListeAvecValeurs(const int valeurs[], size_t numvaleur);

/**
 * @brief Test la méthode longueur selon les cas suivants:
 * liste initialisée mais sans objet entré
 * Liste contenant 42 objets
 * REMARQUE: nous souhaitions tester le comportement avec une liste avec une taille allant au-dela
 * de la valeur maximale de size_t malheureusement le temps pour construire la liste
 * et la mémoire demandé ont coupé court à la tentative (mémoire RAM saturé après quelques secondes)
 */
void testLongueur(void);

/**
 * @brief Test l'insertion d'objet en en tête dans les cas suivants
 * liste vide
 * liste contenant des éléments
 * (la comparaison est faites avec une liste fixe)
 */
void testInsererEntete(void);

/**
 * @brief Test l'insertion d'objet en queue dans les cas suivants
 * liste vide
 * liste contenant des éléments
 * (la comparaison est faites avec une liste fixe)
 */
void testInsererEnqueue(void);

/**
 * @brief Test la suppression d'objet en tête dans les cas suivants
 * liste vide
 * liste contenant des éléments
 * (la comparaison est faites avec une liste fixe)
 */
void testSupprimerEntete(void);

/**
 * @brief Test la suppression d'objet en queue dans les cas suivants
 * liste vide
 * liste contenant des éléments
 * (la comparaison est faites avec une liste fixe)
 */
void testSupprimerEnqueue(void);

void testSupprimerSelonCritere(void);

#endif //LABORATOIRE2_TESTUNITAIRE_H
