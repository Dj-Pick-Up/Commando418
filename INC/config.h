#ifndef DEF_CONFIG
#define DEF_CONFIG

#include "k-arbre.h"

/* GLOBALS VARS */
/* tableau des joueurs */
players pTab;
/* Tableau des touches/switchs enfoncés */
keyTab kTab;
/* Mesure du temps */
int lastMoment;
int deltaMoment;
int startTime;
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
