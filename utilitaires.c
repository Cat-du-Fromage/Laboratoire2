/*
-----------------------------------------------------------------------------------
Nom du fichier : Utilitaires.c
Auteur(s) : Johan Voland, Florian Duruz, Guillaume Dunant
Date creation : 01/05/2023
Description : implémentation des fonctions utilitaires.h
Remarque(s) : -
Compilateur : Mingw-w64 gcc 12.2.0
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

bool estImpair(size_t position, const Info *info) {
   (void) info;//Evite le warning "variable unused"
   return !(position % 2);
}
