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
char map[X_MAX - X_MIN][Z_MAX - Z_MIN];

#endif
