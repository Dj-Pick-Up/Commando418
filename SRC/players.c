#include <stdio.h>
#include <math.h>
#include "structs.h"
#include "config.h"
#include "players.h"
#include "map.h"


void goForward(player * p){
    float dx = cos(p->angle) * MOV_UNIT * deltaMoment;
    float dz = sin(p->angle) * MOV_UNIT * deltaMoment;

    if ((p->x + dx < X_MIN || p->x + dx > X_MAX || !isFree(floor(p->x + dx + ((dx > 0)?1:-1) * X_HITBOX), floor(p->z - Z_HITBOX)) || !isFree(floor(p->x + dx + ((dx > 0)?1:-1) * X_HITBOX), floor(p->z + Z_HITBOX))) && !kTab[NOCLIP_BIT]){
	dx = 0;
    }
    if ((p->z + dz < Z_MIN || p->z + dz > Z_MAX || !isFree(floor(p->x - X_HITBOX), floor(p->z + dz + ((dz > 0)?1:-1) * Z_HITBOX)) || !isFree(floor(p->x + X_HITBOX), floor(p->z + dz + ((dz > 0)?1:-1) * Z_HITBOX))) && !kTab[NOCLIP_BIT]){
	dz = 0;
    }
    p->x += dx;
    p->y += 0;
    p->z += dz;
}


void goBackward(player * p){
    float dx = cos(p->angle) * MOV_UNIT * deltaMoment;
    float dz = sin(p->angle) * MOV_UNIT * deltaMoment;

    if ((p->x - dx < X_MIN || p->x - dx > X_MAX || !isFree(floor(p->x - dx - ((dx > 0)?1:-1) * X_HITBOX), floor(p->z - Z_HITBOX)) || !isFree(floor(p->x - dx - ((dx > 0)?1:-1) * X_HITBOX), floor(p->z + Z_HITBOX))) && !kTab[NOCLIP_BIT]){
	dx = 0;
    }
    if ((p->z - dz < Z_MIN || p->z - dz > Z_MAX || !isFree(floor(p->x - X_HITBOX), floor(p->z - dz - ((dz > 0)?1:-1) * Z_HITBOX)) || !isFree(floor(p->x + X_HITBOX), floor(p->z - dz - ((dz > 0)?1:-1) * Z_HITBOX))) && !kTab[NOCLIP_BIT]){
	dz = 0;
    }
    p->x -= dx;
    p->y -= 0;
    p->z -= dz;
}


void goLeft(player * p){
    float dx = cos(p->angle - M_PI/2) * MOV_UNIT * deltaMoment;
    float dz = sin(p->angle - M_PI/2) * MOV_UNIT * deltaMoment;

    if ((p->x + dx < X_MIN || p->x + dx > X_MAX || !isFree(floor(p->x + dx + ((dx > 0)?1:-1) * X_HITBOX), floor(p->z - Z_HITBOX)) || !isFree(floor(p->x + dx + ((dx > 0)?1:-1) * X_HITBOX), floor(p->z + Z_HITBOX))) && !kTab[NOCLIP_BIT]){
	dx = 0;
    }
    if ((p->z + dz < Z_MIN || p->z + dz > Z_MAX || !isFree(floor(p->x - X_HITBOX), floor(p->z + dz + ((dz > 0)?1:-1) * Z_HITBOX)) || !isFree(floor(p->x + X_HITBOX), floor(p->z + dz + ((dz > 0)?1:-1) * Z_HITBOX))) && !kTab[NOCLIP_BIT]){
	dz = 0;
    }
    p->x += dx;
    p->y += 0;
    p->z += dz;
}


void goRight(player * p){
    float dx = cos(p->angle + M_PI/2) * MOV_UNIT * deltaMoment;
    float dz = sin(p->angle + M_PI/2) * MOV_UNIT * deltaMoment;

    if ((p->x + dx < X_MIN || p->x + dx > X_MAX || !isFree(floor(p->x + dx + ((dx > 0)?1:-1) * X_HITBOX), floor(p->z - Z_HITBOX)) || !isFree(floor(p->x + dx + ((dx > 0)?1:-1) * X_HITBOX), floor(p->z + Z_HITBOX))) && !kTab[NOCLIP_BIT]){
	dx = 0;
    }
    if ((p->z + dz < Z_MIN || p->z + dz > Z_MAX || !isFree(floor(p->x - X_HITBOX), floor(p->z + dz + ((dz > 0)?1:-1) * Z_HITBOX)) || !isFree(floor(p->x + X_HITBOX), floor(p->z + dz + ((dz > 0)?1:-1) * Z_HITBOX))) && !kTab[NOCLIP_BIT]){
	dz = 0;
    }
    p->x += dx;
    p->y += 0;
    p->z += dz;
}


void lookLeft(player * p){
    p->angle -= TURN_UNIT * deltaMoment;
    while (p->angle < 0) p->angle += 2 * M_PI;
}


void lookRight(player * p){
    p->angle += TURN_UNIT * deltaMoment;
    while (p->angle >= 2 * M_PI) p->angle -= 2 * M_PI;
}


void fire(player * p){
    if (p->proj.n >= MAX_PROJ || p->fire_cooldown != 0){
	return;
    }
    p->proj.p[p->proj.n].x = p->x + cos(p->angle);
    p->proj.p[p->proj.n].y = p->y - 0.1;
    p->proj.p[p->proj.n].z = p->z + sin(p->angle);
    p->proj.p[p->proj.n].d_x = cos(p->angle) * PROJ_MOV;
    p->proj.p[p->proj.n].d_z = sin(p->angle) * PROJ_MOV;
    p->proj.p[p->proj.n].ttl = PROJ_TTL;
    p->proj.n ++;

    p->fire_cooldown = MAX_FIRE_COOLDOWN;
}


void manageAllProj(){
    int i;

    for (i=0; i<pTab.n; i++){
	manageProj(&(pTab.p[i]));
    }
}


void manageProj(player * p){
    int i, j;
    float dx, dz;
    char cont = 1;

    /* Teste le cooldown global de l'arme */    
    if (p->fire_cooldown) p->fire_cooldown -= deltaMoment;
    if (p->fire_cooldown < 0) p->fire_cooldown = 0;

    for (i=0; i<p->proj.n; i++){
///* DEBUG */ printf("P : (%f;%f,%f) [%f] <%d>\n", p->proj.p[i].x, p->proj.p[i].y, p->proj.p[i].z, p->proj.p[i].angle, p->proj.p[i].ttl);
	/* Pour chaque projectile ... */
	p->proj.p[i].ttl -= deltaMoment;
	p->proj.p[i].ttl = (p->proj.p[i].ttl < 0)?0:p->proj.p[i].ttl;
	dx = p->proj.p[i].d_x * deltaMoment;
	dz = p->proj.p[i].d_z * deltaMoment;
	
	/* Si le projectile est trop vieux, il "meurt" */
	if (p->proj.p[i].ttl == 0){
	    delProj(p, i);
	}

	/* S'il heurte un mur, il rebondit */
	if (!isFree(p->proj.p[i].x + dx, p->proj.p[i].z) || p->proj.p[i].x + dx < X_MIN || p->proj.p[i].x + dx > X_MAX){
	    dx = -dx;
	    p->proj.p[i].d_x = -p->proj.p[i].d_x;
	}
	if (!isFree(p->proj.p[i].x, p->proj.p[i].z + dz) || p->proj.p[i].z + dz < Z_MIN || p->proj.p[i].z + dz > Z_MAX){
	    dz = -dz;
	    p->proj.p[i].d_z = -p->proj.p[i].d_z;
	}

	/* Avancée */
	p->proj.p[i].x += dx;
	p->proj.p[i].z += dz;

	/* On teste s'il blesse/tue quelqu'un */
	for (j=0; j<pTab.n && cont; j++){
	    if (p->proj.p[i].x > pTab.p[j].x - X_HITBOX && p->proj.p[i].x < pTab.p[j].x + X_HITBOX && p->proj.p[i].z > pTab.p[j].z - Z_HITBOX && p->proj.p[i].z < pTab.p[j].z + Z_HITBOX && (j != 0 || !kTab[GODMODE_BIT])){
		if (kTab[DEBUG_BIT]) printf("-> %d degats infliges au joueur %d\n", PLASMA_DAMAGE, j);
		pTab.p[j].health -= PLASMA_DAMAGE;
		p->score += PLASMA_DAMAGE;  // La personne à l'origine de ce tir gagne les points correspondants
		delProj(&(pTab.p[j]), i);
		cont = 0;
	    }
	}
	cont = 1;   // On ré-arme la variable
    }
}


void delProj(player * p, int i){
    /* Fait disparaître le projectile n°i du joueur p */
    if (i != p->proj.n - 1){
	p->proj.p[i] = p->proj.p[p->proj.n - 1];
    }
    p->proj.n --;
}


void killMob(int i){
    /* Tue le mob n°i et le fait "disparaître" */
    if (i < 1 && i >= pTab.n){	// évite de "tuer" le joueur par cette méthode
	return;
    }

    if (i != pTab.n - 1){
	pTab.p[i] = pTab.p[pTab.n - 1];
    }
    pTab.n --;

    if (kTab[DEBUG_BIT]) printf("-> Mob n°%d tue\n", i);
}
