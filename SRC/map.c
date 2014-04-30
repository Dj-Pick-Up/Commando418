	/********************************
	 *	    map			*
	 *==============================*
	 * Alexis Braine -		*
	 *		  Arslen Remaci *
	 *------------------------------*
	 * Contient les fonctions de	*
	 * gestion de la matrice 'map'	*
	 ********************************/


#include "structs.h"
#include "config.h"
#include "map.h"


void setObstacle(int x, int z){
    map[x - X_MIN][z - Z_MIN] = OBSTACLE_CHAR;
}


void setFree(int x, int z){
    map[x - X_MIN][z - Z_MIN] = FREE_CHAR;
}


char isFree(int x, int z){
    return(map[x - X_MIN][z - Z_MIN] != OBSTACLE_CHAR);
}
