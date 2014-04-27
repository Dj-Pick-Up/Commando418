#ifndef DEF_MAP2ARBRE
#define DEF_MAP2ARBRE

#include "k-arbre.h"

#define INSIDE 1
#define OUTSIDE 2
#define MIXED 3

void genTree();
karbre map2tree(int x1, int z1, int x2, int z2);
char moyMap(int x1, int z1, int x2, int z2);
char isLeaf(karbre tree);
void printTree();
void printLeaf(char e);
void dispTree();
void dispTreeRange(int c_x, int c_z, int range, int x1, int z1, int x2, int z2, karbre tree);
void dispCell(karbre tree, int x1, int z1, int x2, int z2);
char inside(int c_x, int c_z, int r, int x1, int z1, int x2, int z2);
int distance(int x1, int z1, int x2, int z2);

#endif
