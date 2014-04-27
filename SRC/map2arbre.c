#include <stdio.h>
#include <math.h>
#include "structs.h"
#include "structs.h"
#include "config.h"
#include "map2arbre.h"
#include "display.h"


void genTree(){
    /* Remplit le 4-arbre mapTree à l'aide des informations contenues dans map */
    mapTree = map2tree(0, 0, G_WIDTH, G_HEIGHT);
}


karbre map2tree(int x1, int z1, int x2, int z2){
    karbre res = kArbreVide();
    int x12 = (x1 + x2) / 2;
    int z12 = (z1 + z2) / 2;

    switch(moyMap(x1, z1, x2, z2)){
	case OBSTACLE_CHAR :
	    res = kConsArbre(OBSTACLE_CHAR, kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide());
	    break;
	case FREE_CHAR :
	    res = kConsArbre(FREE_CHAR, kArbreVide(), kArbreVide(), kArbreVide(), kArbreVide());
	    break;
	case MIXED_CHAR :
	    res = kConsArbre(MIXED_CHAR,
		    map2tree(x1, z12, x12, z2),
		    map2tree(x12, z12, x2, z2),
		    map2tree(x12, z1, x2, z12),
		    map2tree(x1, z1, x12, z12)
		    );
	    break;
    }
    return(res);
}


char moyMap(int x1, int z1, int x2, int z2){
    char type = map[x1][z1];
    int x, z;

    for (x=x1; x<x2 && type != MIXED_CHAR; x++){
    	for (z=z1; z<z2 && type != MIXED_CHAR; z++){
	    if (map[x][z] != type){
		type = MIXED_CHAR;
	    }
	}
    }

    return(type);
}


char isLeaf(karbre tree){
    return(kRacine(tree) != MIXED_CHAR);
}

void printTree(){
    kAfficher(mapTree, printLeaf);
}


void printLeaf(char e){
    switch(e){
	case FREE_CHAR :
	    printf("Libre");
	    break;
	case OBSTACLE_CHAR :
	    printf("Occupee");
	    break;
    }
}


void dispTree(){
    dispTreeRange(p1.x, p1.z, cam_range, X_MIN, Z_MIN, X_MAX, Z_MAX, mapTree);
}


void dispTreeRange(int c_x, int c_z, int range, int x1, int z1, int x2, int z2, karbre tree){ 
    int x12 = (x1 + x2) / 2;
    int z12 = (z1 + z2) / 2;


    switch(inside(c_x, c_z, range, x1, z1, x2, z2)){
	case INSIDE :
	    dispCell(tree, x1, z1, x2, z2);
	    break;
	case OUTSIDE :
	    // Do nothing
	    break;
	case MIXED :
	    if (isLeaf(tree)){
		// Si c'est une feuille, on l'affiche
		dispCell(tree, x1, z1, x2, z2);
	    }
	    else{
		dispTreeRange(c_x, c_z, range, x1, z12, x12, z2, kfils(0, tree));
		dispTreeRange(c_x, c_z, range, x12, z12, x2, z2, kfils(1, tree));
		dispTreeRange(c_x, c_z, range, x12, z1, x2, z12, kfils(2, tree));
		dispTreeRange(c_x, c_z, range, x1, z1, x12, z12, kfils(3, tree));
	    }
	    break;
    }
}


void dispCell(karbre tree, int x1, int z1, int x2, int z2){
    int x12 = (x1 + x2) / 2;
    int z12 = (z1 + z2) / 2;

    switch(kRacine(tree)){
	case FREE_CHAR :
	    // On affiche juste le sol
	    dispGround(x1, z1, x2, z2);
	    break;
	case OBSTACLE_CHAR :
	    // On affiche un gros bloc
	    dispRoof(x1, z1, x2, z2);
	    dispWall(x1, z1, x2, z1);
	    dispWall(x2, z1, x2, z2);
	    dispWall(x1, z2, x2, z2);
	    dispWall(x1, z1, x1, z2);
	    break;
	case MIXED_CHAR :
	    // On affine
	    dispCell(kfils(0, tree), x1, z12, x12, z2);
	    dispCell(kfils(1, tree), x12, z12, x2, z2);
	    dispCell(kfils(2, tree), x12, z1, x2, z12);
	    dispCell(kfils(3, tree), x1, z1, x12, z12);
	    break;
    }
}


char inside(int c_x, int c_z, int r, int x1, int z1, int x2, int z2){
    int x, z, i, k;
    int in = 0, out = 0;
    int d;

    /* On mesure combien de sommets du cube sont dans le cercle */
    for (x=x1, i=0; i < 2; x=x2, i++){
	    for (z=z1, k=0; k < 2; z=z2, k++){
		d = distance(c_x, c_z, x, z) - r;
		if (d>0){
		    out ++;
		}	
		else if (d<0){
		    in ++;
		}
	    }	
    }

    /* On interprète le résultat */
    if (in == 4){
	// Le cube est dans la sphère
	return(INSIDE);
    }
    else if (out == 4){
	// Les 8 cotés du cube sont hors de la sphère, reste à déterminer si elle coupe le cube
	// On regarde donc la position du centre de la sphere par rapport au cube dont on augmente chaque dimension de r (de chaque coté)
	if (((c_x <= x1 - r) || (c_x >= x2 + r)) || ((c_z <= z1 - r) || (c_z >= z2 + r))){
	    // La sphere est hors du cube
    	    return(OUTSIDE);
	}
    }

    // Si on est ici, c'est que :
    //	- soit les 8 sommets du cube sont extérieurs à la sphere, mais on a détecté une intersection entre la sphère et le cube
    //	- soit des cotés du cube sont dans la sphère et et d'autres non
    // Dans tous les cas, on est sûr que la sphère intersecte le cube

    // On regarde si on est au niveau du pixel
    if (x2 -x1 == 1 || z2 - z1 == 1){
	// Si oui, on fait une approximation
	return (OUTSIDE);
    }
    else{
	// Sinon, on continue d'affiner
	return(MIXED);
    }
}


int distance(int x1, int z1, int x2, int z2){
    return(sqrt(pow(x1 - x2, 2) + pow(z1 - z2, 2)));
}
