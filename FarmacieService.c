//
// Created by Blajan David on 3/10/2024.
//
#include "FarmacieService.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>


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
int addMedService(Farmacie *far, int id, char *nume, char *concentratie, int cantitate) {
    Medicament *med = createMed(id, nume, concentratie, cantitate);
    int succ = validate(med);
    if (succ != 0) {
        destroyMed(med);
        return succ;
    }
    addMed(far, med);
    return 0;
}

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
int changeMedService(Farmacie *far, int id, char *nume, char *concentratie) {
    Medicament *med = createMed(id, nume, concentratie, 0);
    int succ = validate(med);
    if (succ != 0) {
        destroyMed(med);
        return succ;
    }

    succ = changeMed(far, med);
    destroyMed(med);
    if (succ == 1)
        return 5;
    return 0;
}

/**
 * Service function to delete meds in the array
 * @param farmacie - Farmacie* array of meds
 * @param id - int,>0
 * @return 1 - if there wasnt any element with the given id
 *         0 - if everything went well
 */
int deleteMedService(Farmacie *far, int id) {
    int succ = deleteMed(far, id);
    if (succ == 0)
        return 0;
    else
        return 1;
}

/**
 * Service function to sort the meds by name, amount
 * @param farmacie - Farmacie* array of meds
 * @param reverse - char, true - if u want the list in decreasing order, false otherwise
 * @return meds - array of meds sorted
 */
Farmacie *sortMeds(Farmacie *far, char *reverse) {
    Farmacie *meds = getAll(far);
    for (int i = 0; i < size(meds) - 1; i++)
        for (int j = i + 1; j < size(meds); j++)
            if (strcmp(getName(getElement(meds, i)), getName(getElement(meds, j))) > 0) {
                ElemType aux = getElement(meds, i);
                meds->elems[i] = meds->elems[j];
                meds->elems[j] = aux;
            } else if (strcmp(getName(getElement(meds, i)), getName(getElement(meds, j))) == 0)
                if (getAmount(getElement(meds, i)) > getAmount(getElement(meds, j))) {
                    ElemType aux = getElement(meds, i);
                    meds->elems[i] = meds->elems[j];
                    meds->elems[j] = aux;
                }
    if (strcmp(reverse, "true") == 0)
        for (int i = 0; i < size(meds) / 2; i++) {
            ElemType aux = getElement(meds, i);
            meds->elems[i] = meds->elems[size(meds) - i - 1];
            meds->elems[size(meds) - i - 1] = aux;
        }
    return meds;
}

/**
 * Service function to filter meds by amount, or by the first letter of the name
 * if those filter exist
 * @param far - Farmacie
 * @param amount - int
 * @param letter - char
 * @return filteredMeds - Farmacie filtered by amount, name
 */
Farmacie *filterMeds(Farmacie *far, int amount, char *letter) {
    Farmacie *filteredMeds = createFarmacie();
    for (int i = 0; i < size(far); i++)
        if (amount != -1 && strcmp(letter, "") != 0) {
            if (getAmount(getElement(far, i)) < amount
                && strncmp(getName(getElement(far, i)), letter, 1) == 0)
                addMed(filteredMeds, getElement(far, i));
        } else if (amount != -1) {
            if (getAmount(getElement(far, i)) < amount)
                addMed(filteredMeds, getElement(far, i));
        } else if (strcmp(letter, "") != 0) {
            if (strncmp(getName(getElement(far, i)), letter, 1) == 0)
                addMed(filteredMeds, getElement(far, i));
        }
    return filteredMeds;
}

/**
* Functions for testing
*/

void testAddMed() {
    Farmacie *far = createFarmacie();
    addMedService(far, 1, "paracetamol", "30%", 10);
    addMedService(far, 2, "nurofen", "50%", 5);
    assert(size(far) == 2);
    int error = addMedService(far, 3, "", "", 3);
    assert(error == 2);
    addMedService(far, 1, "paracetamol", "30%", 5);
    assert(size(far) == 2);
    Medicament *med = getElement(far, 0);
    assert(getAmount(med) == 15);
    destroyFarmacie(far);
}

void testChangeMed() {
    Farmacie *far = createFarmacie();
    addMedService(far, 1, "paracetamol", "30%", 10);
    addMedService(far, 2, "nurofen", "50%", 5);
    assert(size(far) == 2);
    changeMedService(far, 1, "strepsils", "20%");
    Medicament *med = getElement(far, 0);
    assert(strcmp(getName(med), "strepsils") == 0);
    assert(strcmp(getConcentration(med), "20%") == 0);
    int error = changeMedService(far, 1, "", "");
    assert(error == 2);
    int error2 = changeMedService(far, 3, "strepsils", "29%");
    assert(error2 == 5);
    destroyFarmacie(far);
}

void testDeleteMed() {
    Farmacie *far = createFarmacie();
    addMedService(far, 1, "paracetamol", "30%", 10);
    addMedService(far, 2, "nurofen", "50%", 5);
    assert(size(far) == 2);
    int error2 = deleteMedService(far, 1);
    assert(error2 == 0);
    assert(size(far) == 1);
    int error = deleteMedService(far, 5);
    assert(error == 1);
    destroyFarmacie(far);
}

void testSortMeds() {
    Farmacie *far = createFarmacie();
    addMedService(far, 1, "paracetamol", "30%", 10);
    addMedService(far, 2, "nurofen", "50%", 5);
    addMedService(far, 3, "paracetamol", "25%", 8);
    addMedService(far, 4, "decasept", "100%", 15);
    Farmacie *meds = sortMeds(far, "false");
    Medicament *med1 = getElement(meds, 0);
    Medicament *med2 = getElement(meds, 1);
    Medicament *med3 = getElement(meds, 2);
    Medicament *med4 = getElement(meds, 3);
    assert(getId(med1) == 4);
    assert(getId(med2) == 2);
    assert(getId(med3) == 3);
    assert(getId(med4) == 1);
    Farmacie *meds1 = sortMeds(far, "true");
    Medicament *med5 = getElement(meds1, 0);
    assert(getId(med5) == 1);
    destroyFarmacie(far);
}

void testFilterMeds() {
    Farmacie *far = createFarmacie();
    addMedService(far, 1, "paracetamol", "30%", 10);
    addMedService(far, 2, "nurofen", "50%", 5);
    addMedService(far, 3, "paracetamol", "25%", 8);
    addMedService(far, 4, "decasept", "100%", 15);
    Farmacie *filteredMeds = filterMeds(far, 9, "p");
    assert(size(filteredMeds) == 1);
    assert(getId(getElement(filteredMeds, 0)) == 3);
    free(filteredMeds->elems);
    free(filteredMeds);
    filteredMeds = filterMeds(far, 13, "");
    assert(size(filteredMeds) == 3);
    free(filteredMeds->elems);
    free(filteredMeds);
    filteredMeds = filterMeds(far, -1, "p");
    assert(size(filteredMeds) == 2);
    destroyFarmacie(far);
    free(filteredMeds->elems);
    free(filteredMeds);
}
