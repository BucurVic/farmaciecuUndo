#include "FarmacieService.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

ServiceFarmacie createServiceFarmacie(){
    ServiceFarmacie farm;
    farm.allMedicamente = createFarmacie();
    farm.undoList = createFarmacie();
    return farm;
}

void destroyServiceFarmacie(ServiceFarmacie* servfar){
    destroyFarmacie(servfar->allMedicamente, (DestroyFct) destroyMed, 0);
    destroyFarmacie(servfar->undoList, (DestroyFct) destroyFarmacieMed, 0);
}

int addMedService(ServiceFarmacie* servfar, int id, char *nume, char *concentratie, int cantitate) {
    Medicament *med = createMed(id, nume, concentratie, cantitate);
    int succ = validate(med);
    if (succ != 0) {
        destroyMed(med);
        return succ;
    }
    Farmacie* ListaUndo = copyFarmacie(servfar->allMedicamente, (CopyFct) copyMedicament);
    addMed(servfar->allMedicamente, med);
    addMed(servfar->undoList, ListaUndo);
    return 0;
}


int changeMedService(ServiceFarmacie *servfar, int id, char *nume, char *concentratie) {
    Medicament *med = createMed(id, nume, concentratie, 0);
    Farmacie* ListaUndo = copyFarmacie(servfar->allMedicamente, (CopyFct) copyMedicament);
    int succ = validate(med);
    if (succ != 0) {
        destroyMed(med);
        destroyFarmacie(ListaUndo, (DestroyFct) destroyMed, 0);
        return succ;
    }
    succ = changeMed(servfar->allMedicamente, med);
    destroyMed(med);
    if (succ == 1) {
        destroyFarmacie(ListaUndo, (DestroyFct) destroyMed, 0);
        return 5;
    }
    addMed(servfar->undoList, ListaUndo);
    return 0;
}


int deleteMedService(ServiceFarmacie *servfar, int id) {
    Farmacie* ListaUndo = copyFarmacie(servfar->allMedicamente, (CopyFct) copyMedicament);

    int succ = deleteMed(servfar->allMedicamente, id);
    if (succ == 0) {
        addMed(servfar->undoList, ListaUndo);
        return 0;
    }
    else {
        destroyFarmacie(ListaUndo, (DestroyFct) destroyMed, 0);
        return 1;
    }
}


Farmacie *sortMeds(ServiceFarmacie *servfar, char *reverse) {
    Farmacie *meds = getAll(servfar->allMedicamente);
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


Farmacie* filterMeds(ServiceFarmacie *servfar, int amount, char *letter) {
    Farmacie *filteredMeds = createFarmacie();
    for (int i = 0; i < size(servfar->allMedicamente); i++)
        if (amount != -1 && strcmp(letter, "") != 0) {
            if (getAmount(getElement(servfar->allMedicamente, i)) < amount
                && strncmp(getName(getElement(servfar->allMedicamente, i)), letter, 1) == 0)
                addMed(filteredMeds, getElement(servfar->allMedicamente, i));
        } else if (amount != -1) {
            if (getAmount(getElement(servfar->allMedicamente, i)) < amount)
                addMed(filteredMeds, getElement(servfar->allMedicamente, i));
        } else if (strcmp(letter, "") != 0) {
            if (strncmp(getName(getElement(servfar->allMedicamente, i)), letter, 1) == 0)
                addMed(filteredMeds, getElement(servfar->allMedicamente, i));
        }
    return filteredMeds;
}

int undo(ServiceFarmacie* servfar){
    if (size(servfar->undoList) == 0)
        return 1;
    destroyFarmacie(servfar->allMedicamente, (DestroyFct) destroyMed, 0);
    Farmacie* copie = copyFarmacie(servfar->undoList->elems[size(servfar->undoList)-1], (CopyFct) copyMedicament);
    servfar->allMedicamente = copie;
    destroyFarmacie(servfar->undoList->elems[size(servfar->undoList)-1], (DestroyFct) destroyMed, 0);
    servfar->undoList->len--;
    return 0;
}

void testAddMed() {
    ServiceFarmacie servfar = createServiceFarmacie();
    addMedService(&servfar, 1, "paracetamol", "30%", 10);
    addMedService(&servfar, 2, "nurofen", "50%", 5);
    assert(size(servfar.allMedicamente) == 2);
    int error = addMedService(&servfar, 3, "", "", 3);
    assert(error == 2);
    addMedService(&servfar, 1, "paracetamol", "30%", 5);
    assert(size(servfar.allMedicamente) == 2);
    Medicament *med = getElement(servfar.allMedicamente, 0);
    assert(getAmount(med) == 15);
    destroyServiceFarmacie(&servfar);
}

void testChangeMed() {
    ServiceFarmacie servfar = createServiceFarmacie();
    addMedService(&servfar, 1, "paracetamol", "30%", 10);
    addMedService(&servfar, 2, "nurofen", "50%", 5);
    assert(size(servfar.allMedicamente) == 2);
    changeMedService(&servfar, 1, "strepsils", "20%");
    Medicament *med = getElement(servfar.allMedicamente, 0);
    assert(strcmp(getName(med), "strepsils") == 0);
    assert(strcmp(getConcentration(med), "20%") == 0);
    int error = changeMedService(&servfar, 1, "", "");
    assert(error == 2);
    int error2 = changeMedService(&servfar, 3, "strepsils", "29%");
    assert(error2 == 5);
    destroyServiceFarmacie(&servfar);
}

void testDeleteMed() {
    ServiceFarmacie servfar = createServiceFarmacie();
    addMedService(&servfar, 1, "paracetamol", "30%", 10);
    addMedService(&servfar, 2, "nurofen", "50%", 5);
    assert(size(servfar.allMedicamente) == 2);
    int error2 = deleteMedService(&servfar, 1);
    assert(error2 == 0);
    assert(size(servfar.allMedicamente) == 1);
    int error = deleteMedService(&servfar, 5);
    assert(error == 1);
    destroyServiceFarmacie(&servfar);
}

void testSortMeds() {
    ServiceFarmacie servfar = createServiceFarmacie();
    addMedService(&servfar, 1, "paracetamol", "30%", 10);
    addMedService(&servfar, 2, "nurofen", "50%", 5);
    addMedService(&servfar, 3, "paracetamol", "25%", 8);
    addMedService(&servfar, 4, "decasept", "100%", 15);
    Farmacie *meds = sortMeds(&servfar, "false");
    Medicament *med1 = getElement(meds, 0);
    Medicament *med2 = getElement(meds, 1);
    Medicament *med3 = getElement(meds, 2);
    Medicament *med4 = getElement(meds, 3);
    assert(getId(med1) == 4);
    assert(getId(med2) == 2);
    assert(getId(med3) == 3);
    assert(getId(med4) == 1);
    Farmacie *meds1 = sortMeds(&servfar, "true");
    Medicament *med5 = getElement(meds1, 0);
    assert(getId(med5) == 1);
    destroyServiceFarmacie(&servfar);
}

void testFilterMeds() {
    ServiceFarmacie servfar = createServiceFarmacie();
    addMedService(&servfar, 1, "paracetamol", "30%", 10);
    addMedService(&servfar, 2, "nurofen", "50%", 5);
    addMedService(&servfar, 3, "paracetamol", "25%", 8);
    addMedService(&servfar, 4, "decasept", "100%", 15);
    Farmacie *filteredMeds = filterMeds(&servfar, 9, "p");
    assert(size(filteredMeds) == 1);
    assert(getId(getElement(filteredMeds, 0)) == 3);
    free(filteredMeds->elems);
    free(filteredMeds);
    filteredMeds = filterMeds(&servfar, 13, "");
    assert(size(filteredMeds) == 3);
    free(filteredMeds->elems);
    free(filteredMeds);
    filteredMeds = filterMeds(&servfar, -1, "p");
    assert(size(filteredMeds) == 2);
    destroyServiceFarmacie(&servfar);
    free(filteredMeds->elems);
    free(filteredMeds);
}

void testUndo(){
    ServiceFarmacie servfar = createServiceFarmacie();
    addMedService(&servfar, 1, "paracetamol", "30%", 10);
    addMedService(&servfar, 2, "nurofen", "50%", 5);
    addMedService(&servfar, 3, "paracetamol", "25%", 8);
    Farmacie* far = getAll(servfar.allMedicamente);
    assert(size(far) == 3);
    undo(&servfar);
    far = getAll(servfar.allMedicamente);
    assert(size(far) == 2);
    undo(&servfar);
    undo(&servfar);
    far = getAll(servfar.allMedicamente);
    assert(size(far) == 0);
    assert(undo(&servfar)!=0);
    destroyServiceFarmacie(&servfar);
}