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
#include "map2arbre.h"
#include "players.h"



int main(int argc, char * argv[]){
    /* VARS INIT */
    int i, j;
    struct timeval startTimeTV;

    srand(time(NULL));
    /* Initialisation de players */
    // Ne contient que le joueur, pour l'instant
    pTab.n = 1;
    pTab.p[0].x = (X_MIN + X_MAX) / 2 + 0.5;
    pTab.p[0].y = 0.3;
    pTab.p[0].z = 0.5;
    pTab.p[0].angle = M_PI / 2;
    pTab.p[0].proj.n = 0;
    pTab.p[0].health = PLAYER_HEALTH;
    pTab.p[0].score = 0;
    for (i=X_MIN; i<X_MAX; i++){
	for (j=Z_MIN; j<Z_MAX; j++){
	    setFree(i,j);
	}
    }
    cam_height = 0;
    cam_range = MIN_RANGE; 
    gettimeofday(&startTimeTV, NULL);
    startTime = (startTimeTV.tv_usec / 1000) + 1000 * startTimeTV.tv_sec;

    /* Placement d'obstacles  */
    printf("> Generation du labyrinthe...\n");
    createLaby();
    printf("¤ Labyrinthe créé\n");
    printf("> Transformation de la map en 4-arbre...\n");
    genTree();
    printf("¤ Arbre généré\n");
///* DEBUG */ printTree();

    /* INSTRUCTIONS */
    printf("Bienvenue dans Commando 418 !\nLe but de ce jeu est d'atteindre la sortie du labyrinthe, signalée par un donut vert.\n\nCONTROLES\n---------\n'%c' pour avancer\n'%c' pour reculer\n'%c' pour aller a droite\n'%c' pour aller a gauche\n'%c' (ou mouvement de la souris) pour regarder à droite\n'%c' (ou mouvement de la souris) pour regarder à gauche\n'%c' ou clic gauche pour tirer\n'%c' pour quitter\n\nCONTROLES AVANCES / CHEAT\n-------------------------\n'%c' pour changer de mode de camera\n'%c' pour changer la portee de vue\n'%c' pour activer/desactiver le son\n'%c' pour activer/desactiver le mode noclip\n'%c' pour passer en mode debug\n'%c' pour activer le godmode\n\n", FORWARD_KEY, BACKWARD_KEY, STRAF_RIGHT_KEY, STRAF_LEFT_KEY, RIGHT_KEY, LEFT_KEY, FIRE_KEY, EXIT_KEY, CAM_KEY, RANGE_KEY, MUTE_KEY, NOCLIP_KEY, DEBUG_KEY, GODMODE_KEY);

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
//    glPushMatrix();
//    glTranslatef((X_MIN + X_MAX) / 2, 0, (Z_MIN + Z_MAX) / 2);
//    glColor3f(0,0,0);
//    glutSolidTeapot((X_MIN + X_MAX) + 1);
//    glColor3f(1,0,1);
//    glutWireTeapot((X_MIN + X_MAX));
//    glPopMatrix();

    /* Les obstacles */
    // Anciennement dispAllObst()
    // Maintenant optimisé grâce au quad-tree
    dispTree();

    /* Les projectiles */
    dispAllProj();

    /* Le personnage et ses ennemis */
    dispAllPlayers();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* POISTIONNEMENT DE L'OBSERVATEUR ET DU FRUSTUM */
    glFrustum(-0.5, 0.5, -0.5, 0.5, 0.6, MAX_RANGE);
    gluLookAt(pTab.p[0].x - 1 * cos(pTab.p[0].angle), pTab.p[0].y + 0.4 + cam_height, pTab.p[0].z - 1 * sin(pTab.p[0].angle), pTab.p[0].x, pTab.p[0].y  + 0.3, pTab.p[0].z, 0, 1, 0);

    glFlush();
}


void anim(void){
    kbManage();
    getDeltaTime();
    if (kTab[DEBUG_BIT]) calcFPS();

    /* Ajuste le niveau de la caméra */
    if (kTab[CAM_BIT] && cam_height < MAX_CAM_HEIGHT){
	cam_height += CAM_MOV * deltaMoment;
    }
    if (!kTab[CAM_BIT] && cam_height > 0){
	cam_height -= CAM_MOV * deltaMoment;
    }
    if (cam_height < 0){
	cam_height = 0;
    }
    /* Ajuste la portée de la caméra */
    if (kTab[RANGE_BIT] && cam_range < MAX_RANGE){
	cam_range += RANGE_MOV * deltaMoment;
    }
    if (!kTab[RANGE_BIT] && cam_range > MIN_RANGE){
	cam_range -= RANGE_MOV * deltaMoment;
    }

    
    /* Calcule la progression automatique des projectiles */
    manageAllProj();

    /* Teste si l'on est mort */
    if (pTab.p[0].health <= 0){
	lose();
    }

    /* Teste si l'on a atteint l'arrivée */
    if (floor(pTab.p[0].z) == Z_MAX - 1 && floor(pTab.p[0].x) == exit_x){
	win();
    }

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
    if (sumMoments > 1000 || sumMoments < 0){
	/* Affichage des FPS */
	printf("FPS : %d\n", (int) (1000 * samplesMoments / sumMoments));
	sumMoments = 0;
	samplesMoments = 0;
    }
    sumMoments += deltaMoment;
    samplesMoments ++;
}


void win(){
    struct timeval nowTV;
    int now;
    int duration, min, sec;

    gettimeofday(&nowTV, NULL); 
    now = (nowTV.tv_usec / 1000) + 1000 * nowTV.tv_sec;
    duration = now - startTime;
    min = duration / 60000;
    sec = (duration % 60000) / 1000;

    printf("¤ Congratulations ! You won !\n>>> time %d:%d\n>>> score : %d", min, sec, pTab.p[0].score);
    properQuit();
}


void lose(){
    printf("¤ Sorry ! You lose the game !\n");
    properQuit();
}


void properQuit(){
    kFree(mapTree);
    printf("¤ Bye !\n¤ Merci d'avoir joue !\n");
    exit(EXIT_SUCCESS);
}
