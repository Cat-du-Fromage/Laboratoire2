/*
-----------------------------------------------------------------------------------
Nom du fichier : test.c
Auteur(s) : Johan Voland, Florian Duruz, Guillaume Dunant
Date creation : 02/05/2023
Description : Tests unitaires des fonctions implémentées dans ce laboratoire.
Remarque(s) : Certains cas limites n'ont pas pu être étudiés comme la
              taille maximale des types dû à un manque de RAM et probablement
              d'optimisation.
Compilateur : Mingw-w64 gcc 12.2.0
-----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define btoa(x) ((x)?"true":"false")
//===============================================================================
// ---- UTILITAIRE ----
//===============================================================================

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
 * @brief vérifie si la position entrée est impaire
 * @param position position dans la liste
 * @param info inutilisé mais demandé dans le cadre du test unitaire
 * @return true si pair, false si impair
 */
bool estImpair(size_t position, const Info *info);

/**
 * @brief vérifie si l'Info est égal à 6
 * @param position position dans la liste(inutilisé, mais demandé dans le cadre
 * 		 d'un test unitaire)
 * @param info info à comparer
 * @return true si égal à 6, false sinon
 */
bool egalA6(size_t position, const Info *info);


/**
 * @brief Nettoie la mémoire et les pointeurs
 * @param liste liste à supprimer
 */
void libererListe(Liste* liste);

/**
 * @brief Construction d'une liste d'une taille donnée et avec les valeurs
 * 		 initialisées à 0 et s'incrémentant de 1
 * @param numElement nombre d'éléments souhaités
 * @return liste avec contenu initialisé
 */
Liste* construireTestListe(int numElement);

/**
 * @brief Construit une liste initialisant les valeurs selon un tableau (utilise
 * 		 enqueue)
 * @param valeurs valeurs à initialiser dans la liste
 * @param numvaleur taille du tableau donné
 * @return liste avec objets initialisés selon les valeurs données
 */
Liste* construireListeAvecValeurs(const int valeurs[], size_t numValeur);

//===============================================================================
// ---- TESTS UNITAIRES ----
//===============================================================================
/**
 * @brief Test la méthode longueur selon les cas suivants:
 * 		 - liste initialisée mais sans objet entré
 * 		 - Liste contenant 42 objets
 * REMARQUE: nous souhaitions tester le comportement avec une liste ayant une taille
 * allant au-dela de la valeur maximale de size_t malheureusement le temps pour
 * construire la liste et la mémoire demandée ont coupé court à la tentative
 * (mémoire RAM saturée après quelques secondes)
 */
void testLongueur(void);

/**
 * @brief Test l'insertion d'objet en tête dans les cas suivants :
 * 		 - liste vide
 * 		 - liste contenant des éléments
 * 		 (la comparaison est faite avec une liste fixe)
 */
void testInsererEntete(void);

/**
 * @brief Test l'insertion d'objet en queue dans les cas suivants :
 * 		 - liste vide
 * 		 - liste contenant des éléments
 * 		 (la comparaison est faite avec une liste fixe)
 */
void testInsererEnqueue(void);

/**
 * @brief Test la suppression d'objet en tête dans les cas suivants :
 * 		 - liste vide
 * 		 - liste contenant des éléments
 * 		 (la comparaison est faite avec une liste fixe)
 */
void testSupprimerEntete(void);

/**
 * @brief Test la suppression d'objet en queue dans les cas suivants :
 * 		 - liste vide
 * 		 - liste contenant des éléments
 * 		 (la comparaison est faite avec une liste fixe)
 */
void testSupprimerEnqueue(void);

/**
 * @brief Test la suppression d'objet en queue dans les cas suivants :
 * 		 - positions impaires
 * 		 - liste contenant des éléments
 * 		 (la comparaison est faite avec une liste fixe)
 */
void testSupprimerSelonCritere(void);

/**
 * @brief Test la fonction vider
 * tout (depuis position 0)
 * depuis position 2
 * depuis position 4
 */
void testVider(void);

//===============================================================================
// ---- MAIN ----
//===============================================================================
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

   printf("---------- Affichage ----------\n");
   Liste* l0 = construireTestListe(8);
   //Affichage dans l'ordre
   {
      printf("Affichage de la liste l1: ");
      afficher(l0, FORWARD);
   }

   //Affichage à l'envers
   {
      printf("Affichage de la liste l1 a l'envers: ");
      afficher(l0, BACKWARD);
   }
   libererListe(l0);

   return EXIT_SUCCESS;
}

//===============================================================================
// ---- Implémentations Utilitaire ----
//===============================================================================
void metNullEnteteEnqueue(Liste *liste) {
   liste->tete = NULL;
   liste->queue = NULL;
}

void ajoutAUneListeVide(Liste *liste, Element *element) {
   liste->tete = element;
   liste->queue = element;
   element->precedent = NULL;
   element->suivant = NULL;
}

void memcpyInfoSiPossible(Info *destination, const Info* source)
{
   if (destination && source) memcpy(destination, source, sizeof(Info));
}

bool estImpair(size_t position, const Info *info) {
   (void) info;//Evite le warning "variable unused"
   return !(position % 2);
}

bool egalA6(size_t position, const Info *info)
{
   (void) position;//Evite le warning "variable unused"
   return *info == 6;
}

void libererListe(Liste* liste)
{
   free(liste);
   liste = NULL;
}

Liste* construireTestListe(int numElement)
{
   Liste* liste = initialiser();
   for (int i = 0; i < numElement; ++i) {
      Info info = i;
      insererEnQueue(liste, &info);
   }
   return liste;
}

Liste* construireListeAvecValeurs(const int valeurs[], size_t numValeur)
{
   Liste* liste = initialiser();
   for (size_t i = 0; i < numValeur; ++i) {
      Info info = valeurs[i];
      insererEnQueue(liste, &info);
   }
   return liste;
}
//===============================================================================
// ---- Implémentations Tests Unitaires ----
//===============================================================================
void testInsererEntete(void)
{
   printf("---------- insererEnTete ----------\n");
   const int attendu[4] = {9,2,0,1};
   Liste* valeursAttendues = construireListeAvecValeurs(attendu, 4);
   //contient de base 0,1
   Liste* testListe = construireTestListe(2);
   Info i1 = 2;
   Info i2 = 9;
   insererEnTete(testListe, &i1);
   insererEnTete(testListe, &i2);
   bool resultat = sontEgales(valeursAttendues, testListe);
   printf("resultat : testInsererEntete = %s\n", btoa(resultat));
   libererListe(valeursAttendues);
   libererListe(testListe);
}

void testInsererEnqueue(void)
{
   printf("---------- insererEnQueue ----------\n");
   const int attendu[4] = {0,1,2,9};
   Liste* valeursAttendues = construireListeAvecValeurs(attendu, 4);
   //contient de base 0,1
   Liste* testListe = construireTestListe(2);
   Info i1 = 2;
   Info i2 = 9;
   insererEnQueue(testListe, &i1);
   insererEnQueue(testListe, &i2);
   bool resultat = sontEgales(valeursAttendues, testListe);
   printf("resultat : testInsererEnqueue = %s\n", btoa(resultat));
   libererListe(valeursAttendues);
   libererListe(testListe);
}

void testLongueur(void)
{
   printf("---------- longueur ----------\n");
   bool resultat;
   size_t longueurReel;
   // 0 élément
   {
      const int valeurAttendueVide = 0;
      Liste *testListe = initialiser();
      longueurReel = longueur(testListe);
      resultat = longueurReel == valeurAttendueVide;
      printf("testLongueur: attendu: %d : obtenu: %lld = %s\n", valeurAttendueVide, longueurReel, btoa(resultat));
      libererListe(testListe);
   }

   {
      const int valeurAttendue3 = 42;
      Liste *testListe = construireTestListe(valeurAttendue3);
      longueurReel = longueur(testListe);
      resultat = longueurReel == valeurAttendue3;
      printf("testLongueur: attendu: %d : obtenu: %lld = %s\n", valeurAttendue3, longueurReel, btoa(resultat));
      libererListe(testListe);
   }
}

void testSupprimerEntete(void)
{
   printf("---------- supprimerEnTete ----------\n");
   // test sur liste vide
   {
      const Status statusAttendu = LISTE_VIDE;
      const int infoAttendu = -1;
      Liste *testListe = initialiser();
      Info infoSuppr = -1;
      Status status = supprimerEnTete(testListe, &infoSuppr);
      bool resultat = status == statusAttendu && infoAttendu == infoSuppr;
      printf("testSupprimerEntete: infoAttendu: %d, obtenu: %d = %s\n", infoAttendu, infoSuppr, btoa(resultat));
      libererListe(testListe);
   }

   // supression de 3 éléments en tête
   {
      const Status statusAttendu = OK;
      const int infoAttendu = 2;
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      Info infoSuppr = -1;
      supprimerEnTete(testListe, &infoSuppr);
      supprimerEnTete(testListe, &infoSuppr);
      Status status = supprimerEnTete(testListe, &infoSuppr);
      bool resultat = status == statusAttendu && infoAttendu == infoSuppr;
      printf("testSupprimerEntete: infoAttendu: %d, obtenu: %d = %s\n", infoAttendu, infoSuppr, btoa(resultat));
      libererListe(testListe);
   }
}

void testSupprimerEnqueue(void)
{
   printf("---------- supprimerEnQueue ----------\n");
   // test sur liste vide
   {
      const Status statusAttendu = LISTE_VIDE;
      const int infoAttendu = -1;
      Liste *testListe = initialiser();
      Info infoSuppr = -1;
      Status status = supprimerEnQueue(testListe, &infoSuppr);
      bool resultat = status == statusAttendu && infoAttendu == infoSuppr;
      printf("testSupprimerEnqueue: infoAttendu: %d, obtenu: %d = %s\n", infoAttendu, infoSuppr, btoa(resultat));
      libererListe(testListe);
   }

   // suppression de 3 éléments en queue
   {
      const Status statusAttendu = OK;
      const int infoAttendu = 5;
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      Info infoSuppr = -1;
      supprimerEnQueue(testListe, &infoSuppr);
      supprimerEnQueue(testListe, &infoSuppr);
      Status status = supprimerEnQueue(testListe, &infoSuppr);
      bool resultat = status == statusAttendu && infoAttendu == infoSuppr;
      printf("testSupprimerEnqueue: infoAttendu: %d, obtenu: %d = %s\n", infoAttendu, infoSuppr, btoa(resultat));
      libererListe(testListe);
   }
}

void testSupprimerSelonCritere(void)
{
   printf("---------- supprimerSelonCritere ----------\n");
   // suppression des éléments en position impaire
   {
      const int attendu[4] = {0,2,4,6};
      Liste* valeursAttendues = construireListeAvecValeurs(attendu, 4);
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      supprimerSelonCritere(testListe, &estImpair);
      bool resultat = sontEgales(valeursAttendues, testListe);
      printf("testSupprimerSelonCritere(positions impaires): %s\n", btoa(resultat));
      libererListe(testListe);
      libererListe(valeursAttendues);
   }

   // suppression des éléments en position impaire
   {
      const int attendu[7] = {0,1,2,3,4,5,7};
      Liste* valeursAttendues = construireListeAvecValeurs(attendu, 7);
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      supprimerSelonCritere(testListe, &egalA6);
      bool resultat = sontEgales(valeursAttendues, testListe);
      printf("testSupprimerSelonCritere(egal a 6): %s\n", btoa(resultat));
      libererListe(testListe);
      libererListe(valeursAttendues);
   }
}

void testVider(void)
{
   printf("---------- supprimerSelonCritere ----------\n");
   // vider tout
   {
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 à 7
      //Suppression du contenu des listes
      printf("Suppression du contenu en entier : ");
      vider(testListe, 0);
      bool resultat = estVide(testListe);
      printf("testVider(depuis index 0) :  %s\n", btoa(resultat));
      libererListe(testListe);
   }
   // vider depuis indice 2
   {
      const int attendu[2] = {0,1};
      Liste* valeursAttendues = construireListeAvecValeurs(attendu, 2);
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      const size_t pos = 2;
      printf("Suppresion depuis l'indice %lld : ", pos);
      vider(testListe, pos);
      bool resultat = sontEgales(valeursAttendues, testListe);
      afficher(testListe, FORWARD);
      printf("testVider(Suppresion depuis l'indice %lld) : %s\n", pos, btoa(resultat));
      libererListe(testListe);
      libererListe(valeursAttendues);
   }
   // vider depuis indice 4
   {
      const int attendu[4] = {0,1,2,3};
      Liste* valeursAttendues = construireListeAvecValeurs(attendu, 4);
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      const size_t pos = 4;
      printf("Suppresion depuis l'indice %lld : ", pos);
      vider(testListe, pos);
      bool resultat = sontEgales(valeursAttendues, testListe);
      afficher(testListe, FORWARD);
      printf("testVider(Suppresion depuis l'indice %lld) : %s\n", pos, btoa(resultat));
      libererListe(testListe);
      libererListe(valeursAttendues);
   }
}
