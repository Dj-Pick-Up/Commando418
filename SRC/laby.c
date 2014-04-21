#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "structs.h"
#include "laby.h"
#include "config.h"


char testCell(int i, int j){
    /* Retourne 1 si la case est libre, 0 sinon */
    if (i > G_WIDTH || i<0 || j > G_HEIGHT || i<0)
	return(0);
    return(map[i][j] == FREE_CHAR);
}


char testLaby(){
    int sum=0;	    // La somme de tous les éléments du maprinthe
    int endLine=0;  // La somme de toutes les cases de dernière ligne
    int out;
    int i, j;

    for (i=0; i<G_WIDTH; i++){
	for (j=0; j<G_HEIGHT; j++){
	    sum += testCell(i, j);
	}
	endLine += testCell(i, G_HEIGHT - 1);
    }

    if (sum < G_HEIGHT * G_WIDTH / 3 || !endLine){
	return(0);
    }
    
    /* On choisit dans quelle case on positionnera l'arrivée */
    out = 1 + rand() % endLine;
    for (i=0; out; i++){
	if (testCell(i, G_HEIGHT - 1)){
	    out --;
	}
	if (!out){
	    map[i][G_HEIGHT - 1] = EXIT_CHAR;
	    exit_x = i + X_MIN;
	}
    }
    return(1);
}


void freeCell(int x, int y, int prof, int max){
    int adj;
    int xcur, ycur;

    /* Libère la case courante */
    map[x][y] = FREE_CHAR;


    for (xcur = x-1; xcur <= x+1; xcur ++){
	for (ycur = y-1; ycur <= y+1; ycur ++){
	    if ((xcur == x || ycur == y) && xcur >= 0 && xcur < G_WIDTH && ycur >= 0 && ycur < G_HEIGHT && !testCell(xcur, ycur)){
		adj = testCell(xcur+1, ycur) + testCell(xcur, ycur+1) + testCell(xcur-1, ycur) + testCell(xcur, ycur-1);
		if (
			(adj < 3) &&
			(rand() % (5 - 2 * adj) + 1 > 1)
			&& (rand() % (2 * max) + 2 * max > prof)
		   ){
		    freeCell(xcur, ycur, prof + 1, max);
		}
	    }
	}
    }
}


void createLaby(){
    int i, j;
    
    /* Tracé de l'arbre */
    do{
	for (i=0; i<G_WIDTH; i++){
	    for (j=0; j<G_HEIGHT; j++){
		map[i][j] = OBSTACLE_CHAR;  // Au départ, la map est remplie d'obstacles
	    }
	}
	freeCell(G_WIDTH / 2, 0, 1, G_WIDTH + G_HEIGHT);
    }while(!testLaby());
}
