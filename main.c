#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SETTINGS 0
#define DEBUG 0

// tab des solutions
// tab situation


// |-----|-----|-----|
// |> O <|  X  |  1  |
// |-----|-----|-----|
// |  O  |  X  |  1  |
// |-----|-----|-----|
// |  O  |  X  |  1  |
// |-----|-----|-----|


void clear(){
	system("cls");
}

int isInt(char nomber[]){
	for(int i = 0, imax = strlen(nomber); i < imax; i++){
		int a = nomber[i];
		if(a < 48 || a > 57){
			return 1; //isn't int
		}
	}
	return 0; //isInt
}

int random(int a, int b){
	int alea = -1;
    srand(time(NULL));
    while(alea < a || alea >= b){
		alea = rand();
    }
}

// - / ? / X / @ / 0 / 1 / 2 / 3 / 4 / 5 / 6 / 7 / 8
// a modifier pour > 1 <
void hit(char c){
	switch(c){
		case '-':
			printf("-----");
			break;
		case '?':
			printf("  ?  ");
			break;
		case '+':
			printf(" -|- ");
			break;
		case 'X':
			printf("  X  ");
			break;
		case '@':
			printf("  @  ");
			break;
		case '0':
			printf("  0  ");
			break;
		case '1':
			printf("  1  ");
			break;
		case '2':
			printf("  2  ");
			break;
		case '3':
			printf("  3  ");
			break;
		case '4':
			printf("  4  ");
			break;
		case '5':
			printf("  5  ");
			break;
		case '6':
			printf("  6  ");
			break;
		case '7':
			printf("  7  ");
			break;
		case '8':
			printf("  8  ");
			break;
		default:
			printf("     ");
			break;
	}
}

void line(char line[], int l){
	printf("|");
	for(int i = 0, imax = l; i < imax; i++){
		hit(line[i]);
		printf("|");
	}
	printf("\n");
}

void linePulled(int l){
	printf("|");
	for(int i = 0, imax = l; i < imax; i++){
		hit('-');
		printf("|");
	}
	printf("\n");
}

void setIndication(char board[31][31], int l){
	// x+1 / y
	// x-1 / y
	// x / y+1
	// x / y-1
	// x+1 / y+1
	// x+1 / y-1
	// x-1 / y+1
	// x-1 / y-1

	int nb_bomb = 0;
	for(int x = 0, xmax = l; x < xmax; x++){
		for(int y = 0, ymax = l; y < ymax; y++){
			nb_bomb = 0;
			char c[2];
			if(board[x][y] != 'X'){
				if(board[x+1][y] == 'X'){
					nb_bomb++;
				}
				if(board[x+1][y+1] == 'X'){
					nb_bomb++;
				}
				if(board[x][y+1] == 'X'){
					nb_bomb++;
				}
				if(board[x-1][y+1] == 'X'){
					nb_bomb++;
				}
				if(board[x-1][y] == 'X'){
					nb_bomb++;
				}
				if(board[x-1][y-1] == 'X'){
					nb_bomb++;
				}
				if(board[x][y-1] == 'X'){
					nb_bomb++;
				}
				if(board[x+1][y-1] == 'X'){
					nb_bomb++;
				}
				sprintf(c, "%d", nb_bomb); //int to char
				if(c[0] != '0') // keep ' ' if no bomb
					board[x][y] = c[0];
			}
		}
	}
	printf("\n"); 
}

void setBomb(char board[31][31], int l, int bomb){
	int min = 0;
	int max = l;
	int x, y;
	if(DEBUG)
		printf("min: %d, max: %d\n", min, max);
	while(bomb > 0){
		x = random(min, max);
		y = random(min, max);
		if(board[x][y] != 'X'){
			if(DEBUG)
				printf("x: %d - y: %d\n", x, y);
			board[x][y] = 'X';
			bomb--;
		}
	}
}

void display(char board[31][31], int l){
	//clear();
	linePulled(l);
	for(int i = 0, imax = l; i < imax; i++){
		line(board[i], l);
		linePulled(l);
	}
}

int testSettings(int argc, char *argv[], int l, int bomb){
	if(argc == 3){ //2 paramètres OK
		if(isInt(argv[1]) == 0 && isInt(argv[2]) == 0){ //isInt OK
			l = atoi(argv[1]);
			bomb = atoi(argv[2]);
			if(l*l > bomb){ //nombre de bombe inférieur à nombre de case
				if(l >= 0 && bomb >= 0){ //nombre de bombe et nombre de case positifs
					return 0;
				}else{
					printf("Les deux parametres doivent être positif.\n");
					return 1;
				}
			}else{
				printf("Le nombre de bombe est trop important.\n");
				return 1;
			}

		}else{
			printf("Les deux parametres inscrits ne sont pas des 'int'.\n"); //isInt KO
			return 1;
		}
	}else{ //2 paramètres KO
		printf("2 parametres sont demandes.\n");
		return 1;
	}
}

void displaySettings(int argc, char *argv[]){
	for(int i = 0, imax = argc; i < imax; i++){
		printf("%d: ", i);
		for(int j = 0, jmax = strlen(argv[i]); j < jmax; j++){
			printf("%c", argv[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]){

	int l = 0, bomb = 0;
	char board_solution[31][31]; 	// tableau solution
	char board_problem[31][31]; 	// tableau probleme
	char board_cursor[31][31]; 		// tableau curseur

	//initialisation boards
	for(int i = 0, imax = 31; i < imax; i++){
		for(int j = 0, jmax = 31; j < jmax; j++){
			board_solution[i][j] = '0';
			board_problem[i][j] = ' ';
			board_cursor[i][j] = '0';
		}
	}


	// Debug settings
	if(SETTINGS)
		displaySettings(argc, argv);

	//test settings correct
	if(testSettings(argc, argv, l, bomb) == 1)
		return 1;
	
	// char to int
	l = atoi(argv[1]);
	bomb = atoi(argv[2]);

	//board_solution
	setBomb(board_solution, l, bomb);
	setIndication(board_problem, l);

	//board_cursor
	board_cursor[0][0] = '1'; //set cursor to 0 0

	//display(board_solution, l);
	display(board_problem, l);
	//display(board_cursor, l);

	return 0;
}


//séparer fichier.c (header)
//intégration selecteur cursor (wesh.c)