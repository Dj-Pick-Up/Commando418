#ifndef DEF_CONFIG
#define DEF_CONFIG

/* GLOBALS VARS */
player p1;
keyTab kTab;
/* Mesure du temps */
int lastMoment;
int deltaMoment;
/* Calcul des FPS */
float sumMoments;
float samplesMoments;
/* "Carte" des obstacles */
char map[G_WIDTH][G_HEIGHT];

#endif
