#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "action.h"

int main (){
    loadfile("dbmhs.dat");
    while(1){
    int idx = useroption();
    system("cls");
    if (idx == 0){
        printf("-----------------------------------------------------------\n");
        printf("                   Menu: %s   \n", menuoptions[idx]);
        AddData();
    }
    else if (idx == 1){
         printf("-----------------------------------------------------------\n");
         printf("                  Menu: %s   \n", menuoptions[idx]);
        ChangeData();
    }
    else if (idx == 2){
        printf("-----------------------------------------------------------\n");
        printf("       Menu: %s   \n", menuoptions[idx]);
        PrintDataIdx();
    }
    else if (idx == 3){
        printf("-----------------------------------------------------------\n");
        printf("          Menu: %s   \n", menuoptions[idx]);
        PrintData();
    }
    else if (idx == 4){
        printf("-----------------------------------------------------------\n");
        printf("          Menu: %s   \n", menuoptions[idx]);
        DeleteData();
    }
    else if (idx == 5){
        break;
    }
    system("cls");
    }
    printf("FP Strukdat 199 & 208");
}