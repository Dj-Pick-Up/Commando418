#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "main.h"
#include "structs.h"
#include "config.h"
#include "keyboard.h"
#include "display.h"
#include "map.h"
#include "laby.h"



int main(int argc, char * argv[]){
    /* VARS INIT */
    int i, j;

    srand(time(NULL));
    p1.x = (X_MIN + X_MAX) / 2 + 0.5;
    p1.y = 0.3;
    p1.z = 0.5;
    p1.proj.n = 0;
    for (i=X_MIN; i<X_MAX; i++){
	for (j=Z_MIN; j<Z_MAX; j++){
	    setFree(i,j);
	}
    }

    /* Placement d'obstacles  */
    printf("> Generation du labyrinthe...\n");
    createLaby();
    printf("¤ Labyrinthe créé\n");

    /* INITIALISATION D'OPENGL */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Commando 418");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(kbDown);
    glutKeyboardUpFunc(kbUp);
    glutMouseFunc(clickManager);
    glutMotionFunc(mouseMoveManager);
    glutPassiveMotionFunc(mouseMoveManager);
    glutIdleFunc(anim);

    glutSetCursor(GLUT_CURSOR_NONE);
 
    glutMainLoop();

    return(EXIT_SUCCESS);
}


void display(void){
    /* NETTOYAGE DU BUFFER */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* AFFICHAGE */
    /* Le sol */
    ground();
    
    /* La théière céleste */
    glPushMatrix();
    glTranslatef((X_MIN + X_MAX) / 2, 0, (Z_MIN + Z_MAX) / 2);
    glColor3f(0,0,0);
    glutSolidTeapot((X_MIN + X_MAX) + 1);
    glColor3f(1,0,1);
    glutWireTeapot((X_MIN + X_MAX));
    glPopMatrix();

    /* Les obstacles */
    dispAllObst();

    /* Les projectiles */
    dispProj();

    /* Le personnage */
    glPushMatrix();
    glColor3f(0.9, 0, 0);
    glTranslatef(p1.x, p1.y, p1.z);
    glRotatef(((float) - p1.angle) / M_PI * 180 , 0, 1, 0);
    glutWireTeapot(0.3);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* POISTIONNEMENT DE L'OBSERVATEUR ET DU FRUSTUM */
    glFrustum(-0.5, 0.5, -0.5, 0.5, 0.5, RANGE);
    gluLookAt(p1.x - 1 * cos(p1.angle), p1.y + 0.4, p1.z - 1 * sin(p1.angle), p1.x, p1.y  + 0.3, p1.z, 0, 1, 0);

    glFlush();
}


void anim(void){
    kbManage();
    getDeltaTime();
    calcFPS();
    
    /* Calcule la progression automatique des projectiles */
    if (p1.fire_cooldown) p1.fire_cooldown -= deltaMoment;
    if (p1.fire_cooldown < 0) p1.fire_cooldown = 0;
    glutPostRedisplay();
}


void getDeltaTime(void){
    struct timeval curTime;
    int curMoment;

    gettimeofday(&curTime, NULL);
    curMoment = (curTime.tv_usec / 1000) + 1000 * curTime.tv_sec;
    deltaMoment = curMoment - lastMoment;
    lastMoment = curMoment;
}


void calcFPS(){
    /* calcule et affiche le nombre d'image par secondes */
    if (sumMoments > 1000){
	/* Affichage des FPS */
	printf("FPS : %d\n", (int) (1000 * samplesMoments / sumMoments));
	sumMoments = 0;
	samplesMoments = 0;
    }
    sumMoments += deltaMoment;
    samplesMoments ++;
}

