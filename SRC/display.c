#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "structs.h"
#include "config.h"
#include "display.h"


void ground(void){
    /* Affiche le sol */
    int x, z;

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
	glutWireSphere(0.2, 20, 20);
	glPopMatrix();
    }
}
