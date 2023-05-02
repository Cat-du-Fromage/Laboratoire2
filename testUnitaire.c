/*
-----------------------------------------------------------------------------------
Nom du fichier : testUnitaire.c
Auteur(s) : Johan Voland, Florian Duruz, Guillaume Dunant
Date creation : 02/05/2023
Description : implémentations des tests unitaires
Remarque(s) : valeur de max Size_t trouvée sur https://en.cppreference.com/w/c/types/size_t
Compilateur : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/
#include "testUnitaire.h"

void libererListe(Liste* liste)
{
   free(liste);
   liste = NULL;
}

Liste* construireTestListe(size_t numElement)
{
   Liste* liste = initialiser();
   for (int i = 0; i < numElement; ++i) {
      Info info = i;
      insererEnQueue(liste, &info);
   }
   return liste;
}

Liste* construireListeAvecValeurs(const int valeurs[], size_t numvaleur)
{
   Liste* liste = initialiser();
   for (size_t i = 0; i < numvaleur; ++i) {
      Info info = valeurs[i];
      insererEnQueue(liste, &info);
   }
   return liste;
}

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
      printf("testLongueur: attendu: %d : obtenu: %d = %s\n", valeurAttendueVide, longueurReel, btoa(resultat));
      libererListe(testListe);
   }

   {
      const int valeurAttendue3 = 42;
      Liste *testListe = construireTestListe(valeurAttendue3);
      longueurReel = longueur(testListe);
      resultat = longueurReel == valeurAttendue3;
      printf("testLongueur: attendu: %d : obtenu: %d = %s\n", valeurAttendue3, longueurReel, btoa(resultat));
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
   // suppression des éléments en position impair
   {
      const int attendu[4] = {0,2,4,6};
      Liste* valeursAttendues = construireListeAvecValeurs(attendu, 4);
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      supprimerSelonCritere(testListe, &estImpair);
      bool resultat = sontEgales(valeursAttendues, testListe);
      printf("testSupprimerSelonCritere(positions impaires): %s\n", btoa(resultat));
      libererListe(testListe);
   }

   // suppression des éléments en position impair
   {
      const int attendu[7] = {0,1,2,3,4,5,7};
      Liste* valeursAttendues = construireListeAvecValeurs(attendu, 7);
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      supprimerSelonCritere(testListe, &egalA6);
      bool resultat = sontEgales(valeursAttendues, testListe);
      printf("testSupprimerSelonCritere(egal a 6): %s\n", btoa(resultat));
      libererListe(testListe);
   }
}

void testVider(void)
{
   printf("---------- supprimerSelonCritere ----------\n");
   // vider tout
   {
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
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
      Liste* valeursAttendues = construireListeAvecValeurs(attendu, 3);
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      const size_t pos = 2;
      printf("Suppresion depuis l'indice %lld : ", pos);
      vider(testListe, pos);
      bool resultat = sontEgales(valeursAttendues, testListe);
      afficher(testListe, FORWARD);
      printf("testVider(Suppresion depuis l'indice %lld) : %s\n", pos, btoa(resultat));
      libererListe(testListe);
   }
   // vider depuis indice 4
   {
      const int attendu[4] = {0,1,2,3};
      Liste* valeursAttendues = construireListeAvecValeurs(attendu, 3);
      Liste* testListe = construireTestListe(8); // valeurs infos: 0 -> 7
      const size_t pos = 4;
      printf("Suppresion depuis l'indice %lld : ", pos);
      vider(testListe, pos);
      bool resultat = sontEgales(valeursAttendues, testListe);
      afficher(testListe, FORWARD);
      printf("testVider(Suppresion depuis l'indice %lld) : %s\n", pos, btoa(resultat));
      libererListe(testListe);
   }
}






