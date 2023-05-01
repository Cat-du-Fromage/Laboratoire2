/*
-----------------------------------------------------------------------------------
Nom du fichier : Utilitaires.c
Auteur(s) : Florian Duruz
Date creation : 01/05/2023
Description : <à compléter>
Remarque(s) : <à compléter>
Compilateur : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------
*/

#include "utilitaires.h"

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
