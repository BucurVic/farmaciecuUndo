#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printOptions(){
    printf("exit - Pentru a parasi aplicatia\n"
           "add - Pentru a adauga medicament (expecting id-integer, nume-char, concentratie - char, cantitate - char)\n"
           "change - Pentru a modifica medicament (expecting id-integer, nume-char, concentratie - char)\n"
           "delete - Pentru a sterge medicament (expecting id-integer)\n"
           "sorted - Pentru a afisa lista sortata (expecting true-if reverse sort)\n"
           "filter - Pentru a afisa lista sortata (expecting byAmount - if filter by amount/byName - if filter by name)\n");
}


void addMedUi(ServiceFarmacie* servfar, int id, char* nume, char* concentratie, int cantitate){
    int error = addMedService(servfar, id, nume, concentratie, cantitate);
    if (error!=0)
        printf("Invalid input\n");
    else
        printf("Med was saved\n");
}


void changeMedUi(ServiceFarmacie* servfar,int id,char* nume, char* concentratie){
    int error = changeMedService(servfar, id, nume, concentratie);
    if (error==5)
        printf("Med id doesnt match with any in the list\n");
    else if (error!=0)
        printf("Invalid input\n");
    else
        printf("Med was changed\n");
}


void deleteMedUi(ServiceFarmacie* servfar, int id){
    int error = deleteMedService(servfar, id);
    if (error == 1)
        printf("No med with the id in the list\n");
    else
        printf("Med was deleted successfully\n");
}


void printSorted(ServiceFarmacie* servfar, char* reverse){
    Farmacie* list;
    list = sortMeds(servfar, reverse);
    for(int i=0;i<size(list);i++){
        printf("%d %s %s %d\n", getId(getElement(list, i)),
               getName(getElement(list, i)),
               getConcentration(getElement(list, i)),
               getAmount(getElement(list,i)));
    }
}


void filterMedUi(ServiceFarmacie * servfar, int amount, char* letter){
    Farmacie* list;
    list = filterMeds(servfar, amount, letter);
    for(int i=0;i<size(list);i++){
        printf("%d %s %s %d\n", getId(getElement(list, i)),
               getName(getElement(list, i)),
               getConcentration(getElement(list, i)),
               getAmount(getElement(list,i)));
    }
    free(list->elems);
    free(list);
}


void run(){
    ServiceFarmacie servfar = createServiceFarmacie();
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
            addMedUi(&servfar, id, nume, concentratie, cantitate);
        }
        else if (strcmp(optiune, "change") == 0){
            int id = (int)strtol(parts[1], NULL, 10);
            char* nume = parts[2];
            char* concentratie = parts[3];
            changeMedUi(&servfar, id, nume, concentratie);
        }
        else if (strcmp(optiune, "delete") == 0){
            int id =(int)strtol(parts[1], NULL, 10);
            deleteMedUi(&servfar, id);
        }
        else if (strcmp(optiune, "sorted") == 0){
            char* reverse = parts[1];
            strcpy(reverse, parts[1]);
            printSorted(&servfar, reverse);
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
            filterMedUi(&servfar, amount, letter);
        }
        else if(strcmp(optiune, "undo") == 0){
            if(undo(&servfar) != 0)
                printf("Undo Indisponibil!");
            else
                printf("S-a efectuat undo!");
        }
    }
    destroyServiceFarmacie(&servfar);
}