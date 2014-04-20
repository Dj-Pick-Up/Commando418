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
}


void dispProj(void){
    int i;
    
    for (i=0; i<p1.proj.n; i++){
///* DEBUG */ printf("P : (%f;%f,%f) [%f] <%d>\n", p1.proj.p[i].x, p1.proj.p[i].y, p1.proj.p[i].z, p1.proj.p[i].angle, p1.proj.p[i].ttl);
	p1.proj.p[i].ttl -= deltaMoment;
	p1.proj.p[i].ttl = (p1.proj.p[i].ttl < 0)?0:p1.proj.p[i].ttl;
	if (p1.proj.p[i].ttl == 0){
	    if (i != p1.proj.n - 1){
		p1.proj.p[i] = p1.proj.p[p1.proj.n - 1];
	    }
	    p1.proj.n --;
	}
	p1.proj.p[i].x += cos(p1.proj.p[i].angle) * PROJ_MOV * deltaMoment;
	p1.proj.p[i].z += sin(p1.proj.p[i].angle) * PROJ_MOV * deltaMoment;
	glPushMatrix();
	glColor3f(0.7, 0.7, 0);
	glTranslatef(p1.proj.p[i].x, p1.proj.p[i].y, p1.proj.p[i].z);
	glutWireSphere(0.1, 20, 20);
	glPopMatrix();
    }
}


void dispAllObst(){
    int i, j;

    for (i=X_MIN; i<X_MAX; i++){
	for (j=Z_MIN; j<Z_MAX; j++){
	    if (!isFree(i,j)) dispObst(i,j);
	}
    }
}


void dispObst(int x, int z){
    glPushMatrix();
    glTranslatef(x + 0.5, 0.5, z + 0.5);
    glColor3f(1, 0.5, 0);
    glutSolidCube(1);
    glColor3f(1, 0, 1);
    glutWireCube(1);
    glPopMatrix();
}
