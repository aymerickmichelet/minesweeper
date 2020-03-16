#include <stdio.h>
#include "conio.h"

#define HEIGHT 2
#define WIDTH 2

void clear(){
    system("clear");
}

int setCursor(int cursor, int action){
    switch (action) {
        case 1: // haut
            if(cursor >= WIDTH)
                return cursor - WIDTH;
            break;
        case 2: // droite
            if(HEIGHT * WIDTH > cursor + 1)
                return cursor + 1;
            break;
        case 3: // bas
            if(cursor + WIDTH < HEIGHT * WIDTH)
                return cursor + WIDTH;
            break;
        case 4: // gauche
            if(cursor > 0)
                return cursor - 1;
            break;
        default:
            return cursor;
    }
    return cursor;
}

int getKey(){
    do{
        char c = getch();
        switch (c) {
            case 72: // haut
                return 1;
            case 77: // droite
                return 2;
            case 80: // bas
                return 3;
            case 75: // gauche
                return 4;
            case 27: // echape
                return 0;
            default:
                break;
        }
    }while(1);
}


void menu(int cursor){
    printf("Menu:\n");
    if(cursor == 0) printf("> ");
    printf("Aymerick");
    if(cursor == 0) printf(" <");
    printf("\t");
    if(cursor == 1) printf("> ");
    printf("Soso");
    if(cursor == 1) printf(" <");
    printf("\n");
    if(cursor == 2) printf("> ");
    printf("Basile");
    if(cursor == 2) printf(" <");
    printf("\t");
    if(cursor == 3) printf("> ");
    printf("Nicola");
    if(cursor == 3) printf(" <");
    printf("\n");
}

int main(void) {
    int cursor = 0;
    do {
        clear();
        menu(cursor);
        int action = getKey();
        if(action == 0)
            return 0;
        cursor = setCursor(cursor, action);
    } while (1);
}


// tab 9
// haut   -32 + 72
// bas    -32 + 80
// droite -32 + 77
// gauche -32 + 75


/*
    afficher menu
    recupère touche
    determine action (h/d/b/g)
    deplacement du curseur
*/