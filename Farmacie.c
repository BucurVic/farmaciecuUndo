//
// Created by Blajan David on 3/9/2024.
//
#include "Farmacie.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/**
 * constructor for farmacie
 * @return far - array of meds
 */
Farmacie* createFarmacie(){
    Farmacie* far = malloc(sizeof(Farmacie));
    far->len = 0;
    far->maxCapacity = 1;
    far->elems = malloc(sizeof(Medicament) * far->maxCapacity);
    return far;
}

/**
 * destructor for farmacie
 */
void destroyFarmacie(Farmacie* far){
    for(int i=0;i<size(far);i++)
        destroyMed(far->elems[i]);
    free(far->elems);
    free(far);
}

/**
 * function to resize the array
 * @param far - Farmacie
 */
void resize(Farmacie* far){
    ElemType* meds = malloc(sizeof(Medicament) * far->maxCapacity * 2);
    for(int i=0;i<size(far);i++)
        meds[i] = far->elems[i];
    free(far->elems);
    far->maxCapacity = 2 * far->maxCapacity;
    far->elems = meds;
}

/**
 * repo function to get an element from the array
 * @param farmacie - Farmacie*, array of meds
 * @param poz - int, index of the element you want to return
 * @return element at the poz index - Medicament type
 */
ElemType getElement(Farmacie* far, int poz){
    return far->elems[poz];
}

/**
 * repo function to get the size of the array
 * @param farmacie - Farmacie*, array of meds
 * @return size of array - int
 */
int size(Farmacie* far){
    return far->len;
}

/**
 * repo function to add an element to the array, adds the element to the end of the array
 * if an element with the same id doesnt exist, or increments the amount otherwise
 * @param farmacie - Farmacie*, array of meds
 * @param med - Medicament*
 */
void addMed(Farmacie* far, ElemType med){
    for (int i = 0; i < size(far); i++)
        if (getId(med) == getId(getElement(far, i))){
            setAmount(getElement(far, i), getAmount(getElement(far, i)) + getAmount(med));
            destroyMed(med);
            return;
        }
    if (far->len == far->maxCapacity)
        resize(far);
    far->elems[size(far)] = med;
    far->len++;
}

/**
 * repo function to get all the items in the array
 * @param farmacie - Farmacie*, array of meds
 * @return far - Farmacie*, array of meds
 */
Farmacie* getAll(Farmacie* far){
    return far;
}

/**
 * repo function to change an element in the array, changes the name and concentration
 * if an element with the given id exist, throws error otherwise
 * @param farmacie - Farmacie*, array of meds
 * @param med - Medicament*
 * @return 1 - if the element doesnt exist
 *         0 - if everything went well
 */
int changeMed(Farmacie* far, ElemType med){
    for (int i=0; i<size(far); i++){
        if (getId(med) == getId(getElement(far, i))){
            unsigned long long nr;

            nr = strlen(getName(med)) + 1;
            free(far->elems[i]->nume);
            far->elems[i]->nume = malloc(sizeof(char) * nr);
            strcpy_s(far->elems[i]->nume, nr, getName(med));

            nr = strlen(getConcentration(med)) + 1;
            free(far->elems[i]->concentratie);
            far->elems[i]->concentratie = malloc(sizeof(char) * nr);
            strcpy_s(far->elems[i]->concentratie, nr, getConcentration(med));
            return 0;
        }
    }
    return 1;
}

/**
 * repo function to delete an element in the array, set the amount to 0, moves it to the back
 * of the array and descreses the length if the item exist, throws error otherwise
 * @param farmacie - Farmacie*, array of meds
 * @param id - int,>0
 * @return 1 - if the element doesnt exist
 *         0 - if everything went well
 */
int deleteMed(Farmacie* far,int id){
    for (int i=0;i<size(far);i++)
        if (id == getId(getElement(far, i))){
            destroyMed(far->elems[i]);
            for(int j=i;j<size(far);j++)
                far->elems[j] = far->elems[j+1];
            far->len--;
            return 0;
        }
    return 1;
}

/**
 * Functions for testing
 */

void testAddFarmacie(){
    Farmacie* far = createFarmacie();
    addMed(far, createMed(1,"paracetamol", "70%", 10));
    addMed(far, createMed(2, "xanax", "50%", 4));
    assert (size(far)==2);
    Medicament* med1 = getElement(far, 0);
    assert (strcmp(getName(med1), "paracetamol") == 0);
    Medicament* med2 = getElement(far, 1);
    assert (strcmp(getName(med2),"xanax")==0);
    addMed(far, createMed(1,"paracetamol","70%",10));
    Medicament* med3 = getElement(far, 0);
    assert(size(far)==2);
    assert(getAmount(med3)==20);
    destroyFarmacie(far);
}

void testChangeFarmacie(){
    Farmacie *far = createFarmacie();
    addMed(far, createMed(1,"paracetamol", "70%", 10));
    addMed(far, createMed(2, "xanax", "50%", 4));
    assert (size(far)==2);
    Farmacie* med = getAll(far);
    assert(size(med)==2);
    Medicament* med1 = getElement(far, 0);
    assert (strcmp(getName(med1), "paracetamol") == 0);
    Medicament* med2 = getElement(far, 1);
    assert (strcmp(getName(med2),"xanax")==0);
    Medicament* medChange1 = createMed(1, "nurofen", "30%", 10);
    changeMed(far, medChange1);
    Medicament* medChange2 = createMed(2, "strepsils", "55%", 4);
    changeMed(far, medChange2);
    assert (size(far)==2);
    Medicament* med3 = getElement(far, 0);
    assert (strcmp(getName(med3), "nurofen") == 0);
    assert (strcmp(getConcentration(med3), "30%")==0);
    Medicament* med4 = getElement(far, 1);
    assert (strcmp(getName(med4),"strepsils")==0);
    assert (strcmp(getConcentration(med4), "55%") == 0);
    destroyMed(medChange1);
    destroyMed(medChange2);
    destroyFarmacie(far);
}

void testDeleteFarmacie(){
    Farmacie* far = createFarmacie();
    addMed(far, createMed(1,"paracetamol", "70%", 10));
    addMed(far, createMed(2, "xanax", "50%", 4));
    assert (size(far)==2);
    deleteMed(far, 1);
    assert(size(far)==1);
    destroyFarmacie(far);
}
