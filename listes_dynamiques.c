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
Liste *initialiser(void) {
    //Allocation de la mémoire
    Liste *list = (Liste *) malloc(sizeof(Liste));

    //Retourne NULL si la mémoire n'a pas pu être initialisé
    if (list == NULL) {
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
bool estVide(const Liste *liste) {
    return liste->tete == NULL && liste->queue == NULL;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie combien il y a d'éléments dans liste.
size_t longueur(const Liste *liste) {
    size_t compteur = 0;
    Element *actual = liste->tete;

    while (actual != NULL) {
        ++compteur;
        actual = actual->suivant;
    }

    return compteur;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Affiche le contenu intégral de liste sous la forme : [info_1,info_2,...]
// Dans le cas d'une liste vide, affiche : []
// En mode FORWARD, resp. BACKWARD, l'affichage se fait en parcourant liste
// dans le sens tete -> queue, resp. queue -> tete.
void afficher(const Liste *liste, Mode mode) {
    //Initialise le pointeur qui parcourira la liste
    Element *actuel;
    if (mode == FORWARD) {
        actuel = liste->tete;
    } else {
        actuel = liste->queue;
    }

    //Affiche les valeurs du tableau
    printf("[");
    if (actuel != NULL) {
        while (true) {
            printf("%d", actuel->info);

            if (mode == FORWARD) {
                actuel = actuel->suivant;
            } else {
                actuel = actuel->precedent;
            }

            if (actuel == NULL) {
                break;
            } else {
                printf(",");
            }
        }
    }
    printf("]\n");
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en tête de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnTete(Liste *liste, const Info *info) {
    Element *element = (Element *) malloc(sizeof(Element));

    if (element == NULL) {
        return MEMOIRE_INSUFFISANTE;
    }

    Info *infoTmp = NULL;
    if ((infoTmp = malloc(sizeof(Info))) == NULL) {
        return MEMOIRE_INSUFFISANTE;
    }
    memcpy(infoTmp, info, sizeof(Info));

    element->info = *infoTmp;

    if (estVide(liste)) {
        liste->tete = element;
        liste->queue = element;
        element->precedent = NULL;
        element->suivant = NULL;

    } else {
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
Status insererEnQueue(Liste *liste, const Info *info) {
    Element *element = (Element *) malloc(sizeof(Element));

    if (element == NULL) {
        return MEMOIRE_INSUFFISANTE;
    }

    Info *infoTmp = NULL;
    if ((infoTmp = malloc(sizeof(Info))) == NULL) {
        return MEMOIRE_INSUFFISANTE;
    }
    memcpy(infoTmp, info, sizeof(Info));

    element->info = *infoTmp;

    if (estVide(liste)) {
        liste->tete = element;
        liste->queue = element;
        element->precedent = NULL;
        element->suivant = NULL;

    } else {
        element->suivant = NULL;
        element->precedent = liste->queue;
        liste->queue->suivant = element;
        liste->queue = element;
    }
    return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en tête de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnTete(Liste *liste, Info *info) {
    //Vérifie que la liste n'est pas vide
    if (estVide(liste))
        return LISTE_VIDE;

    //Copie la valeur de info en tête
    if (info != NULL)
        memcpy(info, &liste->tete->info, sizeof(Info));

    //S'il n'y a qu'un élément
    if (liste->tete->suivant == NULL) {
        free(liste->tete);
        liste->tete = NULL;
        liste->queue = NULL;
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
// Renvoie, via le paramètre info, l'info stockée dans l'élément en queue de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnQueue(Liste *liste, Info *info) {
    //Vérifie que la liste n'est pas vide
    if (estVide(liste))
        return LISTE_VIDE;

    //Copie la valeur de info en queue
    if (info != NULL)
        memcpy(info, &liste->queue->info, sizeof(Info));

    //S'il n'y a qu'un élément
    if (liste->queue->precedent == NULL) {
        free(liste->queue);
        liste->tete = NULL;
        liste->queue = NULL;
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
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste qui
// vérifient le critère passé en second paramètre.
// Exemple: on souhaite supprimer de la liste tous les éléments dont la position est
// impaire et pour lesquels info est compris dans un certain intervalle de valeurs
void supprimerSelonCritere(Liste *liste, bool (*critere)(size_t position, const Info *info)) {
    size_t compteur = 1;
    Element *element = liste->tete;

    while (element != NULL) {
        //Si le critère pour l'élément est rempli
        if (critere(compteur, &element->info)) {
            //Supprime l'élément de liste
            if (element->precedent != NULL && element->suivant != NULL) {
                element->precedent->suivant = element->suivant;
                element->suivant->precedent = element->precedent;
            } else if (element == liste->tete && element == liste->queue) {
                liste->tete = NULL;
                liste->queue = NULL;
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
    }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste
// à partir de la position position
// N.B. Vider à partir de la position 0 signifie vider toute la liste.
void vider(Liste *liste, size_t position) {
    Element *elementAGarder = liste->tete;
    for (size_t i = 1; i < position - 1; i++) {
        if (elementAGarder == NULL) {
            break;
        }
        elementAGarder = elementAGarder->suivant;
    }

    if (elementAGarder != NULL || position == 0) {
        Status statu = OK;
        while (liste->queue != elementAGarder || statu == OK && position == 0) {
            statu = supprimerEnQueue(liste, NULL);
        }
    }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste1 et liste2 sont égales (au sens mêmes infos et infos
// apparaissant dans le même ordre), false sinon.
// N.B. 2 listes vides sont considérées comme égales.
bool sontEgales(const Liste *liste1, const Liste *liste2) {
    Element *el1 = liste1->tete;
    Element *el2 = liste2->tete;

    //Vérifie que les 2 listes ont la même longueur
    if (longueur(liste1) == longueur(liste2)) {

        //Retourne true si les deux listes sont vides
        if(el1 == NULL && el2 == NULL)
            return true;

        //Tant que les deux infos sont identiques
        while (el1->info == el2->info) {
            //Passe aux éléments suivants
            el1 = el1->suivant;
            el2 = el2->suivant;

            //Renvoie true s'il n'y a plus d'élément dans les deux listes
            if (el1 == NULL && el2 == NULL)
                return true;
        }
    }
    return false;
}
// ------------------------------------------------------------------------------


bool check(size_t position, const Info *info) {
    return *info == 6;
}

int main() {
    Liste *l = initialiser();
    const Info i4 = 4;
    const Info i5 = 5;
    const Info i6 = 6;
    insererEnQueue(l, &i4);
    insererEnTete(l, &i5);
    insererEnQueue(l, &i6);
    insererEnQueue(l, &i6);
    insererEnQueue(l, &i5);
    insererEnQueue(l, &i6);
    afficher(l, FORWARD);
    supprimerSelonCritere(l, &check);
    afficher(l, FORWARD);
    Liste *l2 = initialiser();
    insererEnTete(l2, &i5);
    insererEnTete(l2, &i4);
    insererEnTete(l2, &i5);
    printf("%d\n", sontEgales(l, l2));
    supprimerEnTete(l, NULL);
    printf("%d\n", sontEgales(l, l2));
    vider(l, 0);
    vider(l2, 0);
    printf("%d\n", sontEgales(l, l2));

    return 0;
}
