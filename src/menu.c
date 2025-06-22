#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menu.h"

#define up 72
#define down 80
#define enter 13

const char * menuoptions[6] = {
    "1. \x1b[4mM\x1b[24menambah data", //M
    "2. Meng\x1b[4mu\x1b[24mbah data", //U
    "3. Menampilkan semua data dengan inde\x1b[4mx\x1b[24m", //X
    "4. Menampilkan semua data \x1b[4mt\x1b[24manpa index", //T
    "5. \x1b[4mH\x1b[24mapus data", // H
    "6. \x1b[4mK\x1b[24meluar" // K
};
void textcolor(int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void showmenu(int highlight){
    system("cls"); 
    printf("/******************************************************/\n");
    printf("/*          Menu Pilihan Database Mahasiswa:          */\n");
    // printf("/******************************************************/\n");
   

    printf("+------------------------------------------------------+\n");
    for (int i = 0; i<6; i++){
        if (highlight == i){
            textcolor(240);
        }
        else{
            textcolor(15);
        }
        printf("%s\n", menuoptions[i]);
    }
    textcolor(15);
    printf("+------------------------------------------------------+\n");
}
int keyint(char key){
    if (key == 'M' || key == 'm'){
        return 0;
    }
    else if (key == 'U' || key == 'u'){
        return 1;
    }
    else if (key == 'X' || key == 'x'){
        return 2;
    }
    else if (key == 'T' || key == 't'){
        return 3;
    }
    else if (key == 'H' || key == 'h'){
        return 4;
    }
    else if (key == 'K' || key == 'k'){
        return 5;
    }
    else{
        return -1;
    }
}
int useroption(){
    int pos = 0;
    int select = -1;
    while (1){
        showmenu(pos);
        char key = getch();

        if (key == -32 || key == 0){
            key = getch();
        if (key == up){
            pos = (5 + pos) % 6;
        }
        else if (key == down){
            pos = (pos + 1) % 6;
        }
        }
        else if (key == enter){
            select = pos;
            break;
        }
        else if (key >= '1' && key <= '6'){
            select = key - '1';
            break;
        }
        else{
            int idx = keyint(key);
            if (idx != -1){
                select = idx;
                break;
            }
            else{
                printf("Invalid option\n");
            }
        }
    }
    return select;
}