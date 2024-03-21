//
// Created by Blajan David on 3/10/2024.
//

#ifndef FARMACIE_FARMACIESERVICE_H
#define FARMACIE_FARMACIESERVICE_H

#include "Farmacie.h"

/**
 * Service function to add meds to the array
 * @param farmacie - Farmacie* array of meds
 * @param id - int,>0
 * @param name - char, not null
 * @param concentration - char, not null
 * @param amount - int, >=0
 * @return 1,2,3,4 - if there was an error validating the med
 *         0 - if everything went well
 */
int addMedService(Farmacie*, int, char*, char*, int);

/**
 * Service function to change meds in the array
 * @param farmacie - Farmacie* array of meds
 * @param id - int,>0
 * @param name - char, not null
 * @param concentration - char, not null
 * @return 1,2,3,4 - if there was an error validating the med
 *         5 - if there wasnt any element with the given id
 *         0 - if everything went well
 */
int changeMedService(Farmacie*, int, char*, char*);

/**
 * Service function to delete meds in the array
 * @param farmacie - Farmacie* array of meds
 * @param id - int,>0
 * @return 1 - if there wasnt any element with the given id
 *         0 - if everything went well
 */
int deleteMedService(Farmacie*, int);

/**
 * Service function to sort the meds by name, amount
 * @param farmacie - Farmacie* array of meds
 * @param reverse - char, true - if u want the list in decreasing order, false otherwise
 * @return meds - array of meds sorted
 */
Farmacie* sortMeds(Farmacie*, char*);

/**
 * Service function to filter meds by amount, or by the first letter of the name
 * if those filter exist
 * @param far - Farmacie
 * @param amount - int
 * @param letter - char
 * @return filteredMeds - Farmacie filtered by amount, name
 */
Farmacie* filterMeds(Farmacie*, int, char*);

/**
 * Functions for testing
 */
void testAddMed();
void testChangeMed();
void testDeleteMed();
void testSortMeds();
void testFilterMeds();

#endif //FARMACIE_FARMACIESERVICE_H