	/******************************************
	 *                k-arbre                 *
	 *========================================*
	 * author : BRAINE Alexis                 *
	 *----------------------------------------*
	 * Implémente les fonctions de création/  *
	 * traitement/suppression d'un K-arbre    *
	 * (K défini dans k-arbre.h)              *
	 ******************************************/



#ifndef DEF_K_ARBRE
#define DEF_K_ARBRE

#define K 4

/* STRUCURES */
typedef char element;

typedef struct karbre_struct{
    element e;
    struct karbre_struct * fils[K];
} * karbre;

/* FONCTIONS */
karbre kArbreVide();
karbre kConsArbre(element e, ...);
karbre kfils(int pos, karbre a);
element kRacine(karbre a);
int kEstVide(karbre a);
void kAfficher(karbre k, void (* fun)(element e));
void kAffIndent(karbre a, int indent, void (* fun)(element e));
karbre kArbreCopy(karbre src);
void kFree(karbre a);

#endif
