#include "IA.h"
#include "structs.h"
#include "config.h"
#include "main.h"


void manageAllMobs(){
    int i;

    for (i=1; i<pTab.n; i++){
	// Si l'enemi est assez proche du joueur, il s'active
	if (distance(pTab.p[0].x, pTab.p[0].z, pTab.p[i].x, pTab.p[i].z)){
	    manageMob(&(pTab.p[i]));
	}
    }
}


void manageMob(player * p){
}
