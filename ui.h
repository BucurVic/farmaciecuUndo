//
// Created by Blajan David on 3/10/2024.
//

#ifndef FARMACIE_UI_H
#define FARMACIE_UI_H

#include "FarmacieService.h"

/**
 * function to print the options
 */
void printOptions();

/**
 * ui function to add the med
 */
void addMedUi(Farmacie*, int, char*, char*, int);

/**
 * ui function to change the med
 */
void changeMedUi(Farmacie*, int, char*, char*);

/**
 * ui function to delete the med
 */
void deleteMedUi(Farmacie*, int);

/**
 * ui function to print the sorted meds after name, amount
 */
void printSorted(Farmacie*, char*);

/**
 * ui function to print the filtered meds by amount, name
 */
void filterMedUi(Farmacie* , int, char*);

/**
 * ui function to run the app
 */
void run();

#endif //FARMACIE_UI_H
