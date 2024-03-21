//
// Created by Blajan David on 3/9/2024.
//

#ifndef FARMACIE_MEDICAMENT_H
#define FARMACIE_MEDICAMENT_H

/**
 * Medicament - struct type
 * id - int,>0
 * nume - char, not null
 * concentratie - char, not null
 * cantitate - int, >=0
 */
typedef struct{
    int id;
    char* nume;
    char* concentratie;
    int cantitate;
} Medicament;

/**
 * constructor for the med
 * @param id - int,>0
 * @param nume - char, not null
 * @param concentratie - char, not null
 * @param cantitate - int, >=0
 * @return med - Medicament type
 */
Medicament* createMed(int id, char* nume, char* concentratie, int cantitate);

/**
 * destructor for the array
 * @param med - Medicament type
 */
void destroyMed(Medicament* med);

/**
 * getter for the id
 * @return med id
 */
int getId(Medicament*);

/**
 * getter for the name
 * @return med name
 */
char* getName(Medicament*);

/**
 * getter for the concentration
 * @return med concentration
 */
char* getConcentration(Medicament*);

/**
 * getter for the amount
 * @return med amount
 */
int getAmount(Medicament*);

/**
 * setter for the amount
 */
void setAmount(Medicament*, int);

/**
 * functions for testing
 */
void testCreateDestroy();

/**
 * validate function to validate the med
 * @return 0 - if everything went well
 *         1,2,3,4 - if there was an error with the med
 */
int validate(Medicament*);

#endif //FARMACIE_MEDICAMENT_H