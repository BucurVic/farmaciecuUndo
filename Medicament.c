#include "Medicament.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
 * constructor for the med
 * @param id - int,>0
 * @param nume - char, not null
 * @param concentratie - char, not null
 * @param cantitate - int, >=0
 * @return med - Medicament type
 */
Medicament* createMed(int id, char* nume, char* concentratie, int cantitate){
    Medicament *med = malloc(sizeof(Medicament));
    unsigned long long nr;

    med->id = id;

    nr = strlen(nume) + 1;
    med->nume = malloc(sizeof(char) * nr );
    strcpy(med->nume, nume);

    nr = strlen(concentratie) + 1;
    med->concentratie = malloc(sizeof(char) * nr);
    strcpy(med->concentratie, concentratie);

    med->cantitate = cantitate;

    return med;
}

/**
 * destructor for the array
 * @param med - Medicament type
 */
void destroyMed(Medicament* med){
    free(med->nume);
    free(med->concentratie);
    free(med);
}


Medicament* copyMedicament(Medicament* med){
    return createMed(med->id, med->nume, med->concentratie, med->cantitate);
}

/**
 * validate function to validate the med
 * @return 0 - if everything went well
 *         1,2,3,4 - if there was an error with the med
 */
int validate(Medicament* med){
    if (med->id <= 0)
        return 1;
    if (strlen(med->nume) == 0)
        return 2;
    if (strlen(med->concentratie) == 0)
        return 3;
    if (med->cantitate < 0)
        return 4;
    return 0;
}

/**
 * getter for the id
 * @return med id
 */
int getId(Medicament* med) {
    return med->id;
}

/**
 * getter for the name
 * @return med name
 */
char* getName(Medicament* med){
    return med->nume;
}

/**
 * getter for the concentration
 * @return med concentration
 */
char* getConcentration(Medicament* med){
    return med->concentratie;
}

/**
 * getter for the amount
 * @return med amount
 */
int getAmount(Medicament* med){
    return med->cantitate;
}

/**
 * setter for the amount
 */
void setAmount(Medicament* med, int quantity){
    med->cantitate = quantity;
}

/**
 * functions for testing
 */
void testCreateDestroy(){
    Medicament* med5 = createMed(1, "paracetamol", "70%", 10);
    assert(getId(med5) == 1);
    assert(strcmp(getName(med5),"paracetamol")==0);
    assert(strcmp(getConcentration(med5),"70%")==0);
    assert(getAmount(med5)==10);
    assert(validate(med5) == 0);

    destroyMed(med5);

    Medicament* med1 = createMed(2, "", "60%", 5);
    assert(validate(med1) == 2);
    destroyMed(med1);

    Medicament* med2 = createMed(3, "xanax", "", 3);
    assert(validate(med2) == 3);
    destroyMed(med2);

    Medicament* med3 = createMed(-1, "nurofen", "", 5);
    assert(validate(med3) == 1);
    destroyMed(med3);

    Medicament* med4 = createMed(4,"paracetamol", "50%", -6);
    assert(validate(med4) == 4);
    destroyMed(med4);
}