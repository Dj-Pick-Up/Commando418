#ifndef DEF_CONFIG
#define DEF_CONFIG

#include "k-arbre.h"

/* GLOBALS VARS */
player p1;
keyTab kTab;
/* Mesure du temps */
int lastMoment;
int deltaMoment;
/* Calcul des FPS */
int sumMoments;
int samplesMoments;
/* "Carte" des obstacles */
char map[G_WIDTH][G_HEIGHT];
karbre mapTree;
/* Coordonnée de l'arrivée */
int exit_x;
/* hauteur de la caméra */
float cam_height;
/* Portée de la vision */
float cam_range;

#endif
