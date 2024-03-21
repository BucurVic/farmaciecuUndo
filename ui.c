//
// Created by Blajan David on 3/10/2024.
//

#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * function to print the options
 */
void printOptions(){
    printf("exit - Pentru a parasi aplicatia\n"
           "add - Pentru a adauga medicament (expecting id-integer, nume-char, concentratie - char, cantitate - char)\n"
           "change - Pentru a modifica medicament (expecting id-integer, nume-char, concentratie - char)\n"
           "delete - Pentru a sterge medicament (expecting id-integer)\n"
           "sorted - Pentru a afisa lista sortata (expecting true-if reverse sort)\n"
           "filter - Pentru a afisa lista sortata (expecting byAmount - if filter by amount/byName - if filter by name)\n");
}

/**
 * ui function to add the med
 */
void addMedUi(Farmacie* far, int id, char* nume, char* concentratie, int cantitate){
    int error = addMedService(far, id, nume, concentratie, cantitate);
    if (error!=0)
        printf("Invalid input\n");
    else
        printf("Med was saved\n");
}

/**
 * ui function to change the med
 */
void changeMedUi(Farmacie* far,int id,char* nume, char* concentratie){
    int error = changeMedService(far, id, nume, concentratie);
    if (error==5)
        printf("Med id doesnt match with any in the list\n");
    else if (error!=0)
        printf("Invalid input\n");
    else
        printf("Med was changed\n");
}

/**
 * ui function to delete the med
 */
void deleteMedUi(Farmacie* far, int id){
    int error = deleteMedService(far, id);
    if (error == 1)
        printf("No med with the id in the list\n");
    else
        printf("Med was deleted successfully\n");
}

/**
 * ui function to print the sorted meds after name, amount
 */
void printSorted(Farmacie* far, char* reverse){
    Farmacie* list;
    list = sortMeds(far, reverse);
    for(int i=0;i<size(list);i++){
        printf("%d %s %s %d\n", getId(getElement(list, i)),
               getName(getElement(list, i)),
               getConcentration(getElement(list, i)),
               getAmount(getElement(list,i)));
    }
}

/**
 * ui function to print the filtered meds by amount, name
 */
void filterMedUi(Farmacie* far, int amount, char* letter){
    Farmacie* list;
    list = filterMeds(far, amount, letter);
    for(int i=0;i<size(list);i++){
        printf("%d %s %s %d\n", getId(getElement(list, i)),
               getName(getElement(list, i)),
               getConcentration(getElement(list, i)),
               getAmount(getElement(list,i)));
    }
    free(list->elems);
    free(list);
}

/**
 * ui function to run the app
 */
void run(){
    Farmacie *far = createFarmacie();
    char cmd[100];
    while(1){
        printOptions();
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd,"\n")] = '\0';

        if (strcmp(cmd, "exit") == 0) {
            break;
        }

        char *token = strtok(cmd, " ");
        char *parts[100];
        int count = 0;
        while(token!=NULL){
            parts[count++] = token;
            token = strtok(NULL," ");
        }

        char *optiune = parts[0];
        if (strcmp(optiune, "add") == 0){
            int id = (int)strtol(parts[1], NULL, 10);
            char* nume = parts[2];
            char* concentratie = parts[3];
            int cantitate = (int)strtol(parts[4], NULL, 10);
            addMedUi(far, id, nume, concentratie, cantitate);
        }
        else if (strcmp(optiune, "change") == 0){
            int id = (int)strtol(parts[1], NULL, 10);
            char* nume = parts[2];
            char* concentratie = parts[3];
            changeMedUi(far, id, nume, concentratie);
        }
        else if (strcmp(optiune, "delete") == 0){
            int id =(int)strtol(parts[1], NULL, 10);
            deleteMedUi(far, id);
        }
        else if (strcmp(optiune, "sorted") == 0){
            char* reverse = parts[1];
            strcpy(reverse, parts[1]);
            printSorted(far, reverse);
        }
        else if (strcmp(optiune, "filter")==0) {
            char *type1 = parts[1];
            char *letter = "";
            int amount = -1;
            if (strcmp(type1, "byAmount") == 0) {
                amount = (int)strtol(parts[2], NULL, 10);
                if (strcmp(parts[3], "byName") == 0) {
                    letter = parts[4];
                }
            } else {
                letter = parts[2];
            }
            filterMedUi(far, amount, letter);
        }
    }
    destroyFarmacie(far);
}