#include "Medicament.h"
#include "Farmacie.h"
#include "FarmacieService.h"
#include "ui.h"

/**
 * function to run all tests
 */
void TestAll(){
    testCreateDestroy();
    testAddFarmacie();
    testChangeFarmacie();
    testDeleteFarmacie();
    testAddMed();
    testChangeMed();
    testDeleteMed();
    testSortMeds();
    testFilterMeds();
}

/**
 * main function
 */
int main() {
    TestAll();
    run();
    return 0;
}
