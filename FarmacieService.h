#ifndef FARMACIE_FARMACIESERVICE_H
#define FARMACIE_FARMACIESERVICE_H

#include "Farmacie.h"

typedef struct {
    Farmacie* allMedicamente;
    Farmacie* undoList; //lista de liste
}ServiceFarmacie;

/**
 * Service function that creates a ServiceFarmacie
 * @return
 */
ServiceFarmacie createServiceFarmacie();

/**
 * Service function that destroys a ServiceFarmacie
 * @param farmcacie
 */
void destroyServiceFarmacie(ServiceFarmacie* farmcacie);

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
int addMedService(ServiceFarmacie*, int, char*, char*, int);

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
int changeMedService(ServiceFarmacie*, int, char*, char*);

/**
 * Service function to delete meds in the array
 * @param farmacie - Farmacie* array of meds
 * @param id - int,>0
 * @return 1 - if there wasnt any element with the given id
 *         0 - if everything went well
 */
int deleteMedService(ServiceFarmacie*, int);

/**
 * Service function to sort the meds by name, amount
 * @param farmacie - Farmacie* array of meds
 * @param reverse - char, true - if u want the list in decreasing order, false otherwise
 * @return meds - array of meds sorted
 */
Farmacie* sortMeds(ServiceFarmacie *, char*);

/**
 * Service function to filter meds by amount, or by the first letter of the name
 * if those filter exist
 * @param far - Farmacie
 * @param amount - int
 * @param letter - char
 * @return filteredMeds - Farmacie filtered by amount, name
 */
Farmacie* filterMeds(ServiceFarmacie*, int, char*);

int undo(ServiceFarmacie* servar);

/*
 * Functions for testing
 */
void testAddMed();
void testChangeMed();
void testDeleteMed();
void testSortMeds();
void testFilterMeds();
void testUndo();

#endif //FARMACIE_FARMACIESERVICE_H