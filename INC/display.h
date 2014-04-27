#ifndef DEF_DISPLAY
#define DEF_DISPLAY

void ground(void);
void dispProj(void);
void dispAllObst();
void dispObst(int x, int z);

/* AFFICHAGE DEPUIS LE 4-TREE */
void dispWall(int x1, int z1, int x2, int z2);
void dispRoof(int x1, int z1, int x2, int z2);
void dispGround(int x1, int z1, int x2, int z2);

#endif
