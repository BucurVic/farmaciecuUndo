#ifndef FARMACIE_FARMACIE_H
#define FARMACIE_FARMACIE_H

#include "Medicament.h"

typedef void* ElemType;
/**
 * Farmacie - struct type
 * elems - array of meds
 * len - length of the array
 */

typedef void(*DestroyFct)(ElemType);

typedef ElemType (*CopyFct)(ElemType);

typedef struct {
    ElemType* elems;
    int len;
    int maxCapacity;
    DestroyFct destroyfunciton;
} Farmacie;

/**
 * constructor for farmacie
 * @return far - array of meds
 */
Farmacie* createFarmacie();

void destroyFarmacieMed(Farmacie* far);

/**
 * destructor for farmacie
 */
void destroyFarmacie(Farmacie*, DestroyFct functiedestroy, int);

/**
 * function to resize the array
 * @param far - Farmacie
 */
void resize(Farmacie*);

/**
 * repo function to get an element from the array
 * @param farmacie - Farmacie*, array of meds
 * @param poz - int, index of the element you want to return
 * @return element at the poz index - Medicament type
 */
ElemType getElement(Farmacie* , int);

/**
 * repo function to get the size of the array
 * @param farmacie - Farmacie*, array of meds
 * @return size of array - int
 */
int size(Farmacie*);

/**
 * repo function to add an element to the array, adds the element to the end of the array
 * if an element with the same id doesnt exist, or increments the amount otherwise
 * @param farmacie - Farmacie*, array of meds
 * @param med - Medicament*
 */
void addMed(Farmacie*, ElemType);

/**
 * repo function to change an element in the array, changes the name and concentration
 * if an element with the given id exist, throws error otherwise
 * @param farmacie - Farmacie*, array of meds
 * @param med - Medicament*
 * @return 1 - if the element doesnt exist
 *         0 - if everything went well
 */
int changeMed(Farmacie*, ElemType);

/**
 * repo function to delete an element in the array, set the amount to 0, moves it to the back
 * of the array and descreses the length if the item exist, throws error otherwise
 * @param farmacie - Farmacie*, array of meds
 * @param id - int,>0
 * @return 1 - if the element doesnt exist
 *         0 - if everything went well
 */
int deleteMed(Farmacie*, int);

/**
 * repo function to get all the items in the array
 * @param farmacie - Farmacie*, array of meds
 * @return far - Farmacie*, array of meds
 */
Farmacie* getAll(Farmacie*);

Farmacie* copyFarmacie(Farmacie*, CopyFct);

/**
 * Functions for testing
 */
void testAddFarmacie();
void testCopyList();
void testListadeListe();
void testChangeFarmacie();
void testDeleteFarmacie();

#endif //FARMACIE_FARMACIE_H