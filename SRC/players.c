#include <math.h>
#include "structs.h"
#include "config.h"
#include "players.h"
#include "map.h"


void goForward(player * p){
    float dx = cos(p1.angle) * MOV_UNIT * deltaMoment;
    float dz = sin(p1.angle) * MOV_UNIT * deltaMoment;

    if (p->x + dx < X_MIN || p->x + dx > X_MAX || !isFree(floor(p->x + dx + ((dx > 0)?1:-1) * X_HITBOX), floor(p->z))){
	dx = 0;
    }
    if (p->z + dz < Z_MIN || p->z + dz > Z_MAX || !isFree(floor(p->x), floor(p->z + dz + ((dz > 0)?1:-1) * Z_HITBOX))){
	dz = 0;
    }
    p->x += dx;
    p->y += 0;
    p->z += dz;
}


void goBackward(player * p){
    float dx = cos(p1.angle) * MOV_UNIT * deltaMoment;
    float dz = sin(p1.angle) * MOV_UNIT * deltaMoment;

    if (p->x - dx < X_MIN || p->x - dx > X_MAX || !isFree(floor(p->x - dx - ((dx > 0)?1:-1) * X_HITBOX), floor(p->z))){
	dx = 0;
    }
    if (p->z - dz < Z_MIN || p->z - dz > Z_MAX || !isFree(floor(p->x), floor(p->z - dz - ((dz > 0)?1:-1) * Z_HITBOX))){
	dz = 0;
    }
    p->x -= dx;
    p->y -= 0;
    p->z -= dz;
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
    p->proj.p[p->proj.n].angle = p->angle;
    p->proj.p[p->proj.n].ttl = PROJ_TTL;
    p->proj.n ++;

    p->fire_cooldown = MAX_FIRE_COOLDOWN;

///* DEBUG */ printf("FIRE\n");
}
