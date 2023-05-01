/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Johan Voland, Florian Duruz, Guillaume Dunant
 Date creation  : 30.04.2023

 Description    : Programme permettant de tester l'implémentation de la liste
 						doublement chaînée.

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 12.2.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdio.h>

/**
 * @brief Vérifie que l'info entrée est égale à 6.
 *
 * @param position Position à tester.
 * @param info Info à tester.
 * @return True si info est égal à 6, False sinon.
 */
bool checkIf6(size_t position, const Info *info);

/**
 * @brief Test si la position est impaire ou que la valeur est comprise entre 2
 * 		 nombres.
 *
 * @param position Position à tester.
 * @param info Info à tester.
 * @return True si la position est impaire ou que info est compris entre deux
 * 		  valeurs, False sinon.
 */
bool checkImpaireOuRange(size_t position, const Info *info);

int main(void) {
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
	printf("l = %lld : ", longueur(l));
	afficher(l, FORWARD);

	supprimerSelonCritere(l, &checkIf6);
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

	Liste *l3 = initialiser();
	const Info i1 = 1;
	const Info i2 = 2;
	const	Info i3 = 3;
	insererEnTete(l3, &i1);
	insererEnTete(l3, &i6);
	insererEnTete(l3, &i3);
	insererEnTete(l3, &i2);
	insererEnQueue(l3, &i6);
	afficher(l3, BACKWARD);
	afficher(l3, FORWARD);

	supprimerSelonCritere(l3, &checkImpaireOuRange);
	afficher(l3, FORWARD);

	return 0;
}

bool checkIf6(size_t position, const Info *info) {
	return *info == 6;
}

bool checkImpaireOuRange(size_t position, const Info *info) {
	return position % 2 || *info <= 3 && *info > 1;
}