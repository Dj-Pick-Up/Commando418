#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "structs.h"
#include "config.h"
#include "display.h"
#include "map.h"


void ground(void){
    int x, z;

    /* Affiche le sol */
    glColor3f(0, 1, 1);
    glBegin(GL_LINES);

    for (x = X_MIN; x <= X_MAX; x++){
	glVertex3f(x, 0, Z_MIN);
	glVertex3f(x, 0, Z_MAX);

    }
    for (z = Z_MIN; z <= Z_MAX; z++){
	glVertex3f(X_MIN, 0, z);
	glVertex3f(X_MAX, 0, z);
    }

    glEnd();

    /* Affiche les contours */
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);

    for (x = X_MIN; x < X_MAX; x++){
	glVertex3f(x, 0, Z_MIN);
	glVertex3f(x+1, 0, Z_MIN);
	glVertex3f(x+1, 1, Z_MIN);
	glVertex3f(x, 1, Z_MIN);
	glVertex3f(x, 0, Z_MAX);
	glVertex3f(x+1, 0, Z_MAX);
	glVertex3f(x+1, 1, Z_MAX);
	glVertex3f(x, 1, Z_MAX);
    }

    for (z = Z_MIN; z < Z_MAX; z++){
	glVertex3f(X_MIN, 0, z);
	glVertex3f(X_MIN, 0, z+1);
	glVertex3f(X_MIN, 1, z+1);
	glVertex3f(X_MIN, 1, z);
	glVertex3f(X_MAX, 0, z);
	glVertex3f(X_MAX, 0, z+1);
	glVertex3f(X_MAX, 1, z+1);
	glVertex3f(X_MAX, 1, z);
    }
    glEnd();

    /* Affiche l'arrivée */
    glBegin(GL_QUADS);
    glColor3f(0, 0.9, 0.1);

    glVertex3f(exit_x, 0, Z_MAX-1);
    glVertex3f(exit_x, 0, Z_MAX);
    glVertex3f(exit_x+1, 0, Z_MAX);
    glVertex3f(exit_x+1, 0, Z_MAX-1);

    glEnd();

    /* Signale l'arrivée */
    glPushMatrix();
    glTranslatef(exit_x + 0.5, 10, Z_MAX - 0.5);
    glutSolidTorus(2, 2.5, 20, 20);
    glPopMatrix();
}   


void dispAllProj(){
    // Affiche tous les projectiles
    int i;

    for (i=0; i<pTab.n; i++){
	dispProj(&(pTab.p[i]));
    }
}


void dispProj(player * p){
    int i;

    for (i=0; i<p->proj.n; i++){
	glPushMatrix();
	glColor3f(0.7, 0.7, 0);
	glTranslatef(p->proj.p[i].x, p->proj.p[i].y, p->proj.p[i].z);
	glutWireSphere(0.1, 20, 20);
	glPopMatrix();
    }
}


void dispAllPlayers(){
    // Affichera tous les joueurs
    int i;

    for (i=0; i<pTab.n; i++){
	dispPlayer(&(pTab.p[i]));
    }
}


void dispPlayer(player * p){
    glPushMatrix();
    glColor3f(0.9, 0, 0);
    glTranslatef(p->x, p->y, p->z);
    glRotatef(((float) - p->angle) / M_PI * 180 , 0, 1, 0);
    glutWireTeapot(0.3);
    glPopMatrix();
}


/* AFFICHAGE DEPUIS LE 4-TREE */
void dispWall(int x1, int z1, int x2, int z2){
    glColor3f(1, 0.5, 0);
    glBegin(GL_QUADS);
    glVertex3f(x1, 0, z1);
    glVertex3f(x2, 0, z2);
    glVertex3f(x2, 1, z2);
    glVertex3f(x1, 1, z1);
    glEnd();
}


void dispRoof(int x1, int z1, int x2, int z2){
    glColor3f(1, 0.5, 0);
    glBegin(GL_QUADS);
    glVertex3f(x1, 1, z1);
    glVertex3f(x1, 1, z2);
    glVertex3f(x2, 1, z2);
    glVertex3f(x2, 1, z1);
    glEnd();
}


void dispGround(int x1, int z1, int x2, int z2){
    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(x1, 0, z1);
    glVertex3f(x1, 0, z2);
    glVertex3f(x2, 0, z2);
    glVertex3f(x2, 0, z1);
    glEnd();
}
