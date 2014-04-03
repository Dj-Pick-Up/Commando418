#include <math.h>
#include "structs.h"
#include "config.h"
#include "players.h"


void goForward(player * p){
    p->x += cos(p1.angle) * MOV_UNIT * deltaMoment;
    p->y += 0;
    p->z += sin(p1.angle) * MOV_UNIT * deltaMoment;
}


void goBackward(player * p){
    p->x -= cos(p->angle) * MOV_UNIT * deltaMoment;
    p->y -= 0;
    p->z -= sin(p->angle) * MOV_UNIT * deltaMoment;
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
    p->proj.p[p->proj.n].x = p->x + 2 * cos(p->angle);
    p->proj.p[p->proj.n].y = p->y - 0.5;
    p->proj.p[p->proj.n].z = p->z + 2 * sin(p->angle);
    p->proj.p[p->proj.n].angle = p->angle;
    p->proj.p[p->proj.n].ttl = PROJ_TTL;
    p->proj.n ++;

    p->fire_cooldown = MAX_FIRE_COOLDOWN;

///* DEBUG */ printf("FIRE\n");
}
