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
    testCopyList();
    testListadeListe();
    testAddMed();
    testChangeMed();
    testDeleteMed();
    testSortMeds();
    testFilterMeds();
    testUndo();
}

/**
 * main function
 */
int main() {
    TestAll();
    run();
    return 0;
}
