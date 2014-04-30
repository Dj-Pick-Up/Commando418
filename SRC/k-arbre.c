	/********************************
	 *	    k-arbre		*
	 *==============================*
	 * Alexis Braine -		*
	 *		  Arslen Remaci *
	 *------------------------------*
	 * Implémente les fonctions de	*
	 * création/traitement/		*
	 * suppression d'un K-arbre	*
	 * (K défini dans k-arbre.h)	*
	 ********************************/



#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "k-arbre.h"


karbre kArbreVide(){
    return(NULL);
}


karbre kConsArbre(element e, ...){
    va_list ite;
    karbre res;
    int i;
    
    if ((res = (karbre) malloc (sizeof(struct karbre_struct))) == NULL){
	return(NULL);
    }
    res->e = e;

    /* On traite les K fils */
    va_start(ite, e);
    for (i=0; i<K; i++){
	res->fils[i] = va_arg(ite, karbre);
    }
    va_end(ite);

    return(res);
}


karbre kfils(int pos, karbre a){
    return((pos>K)?NULL:a->fils[pos]);
}


element kRacine(karbre a){
    return(a->e);
}


int kEstVide(karbre a){
    return(a == NULL);
}


void kAfficher(karbre a, void (*fun)(element e)){
    kAffIndent(a, 0, fun);
}


void kAffIndent(karbre a, int indent, void (*fun)(element e)){
    int i;

    if (a == NULL){
	return;
    }

    for (i=0; i<indent; i++){
	printf("    ");
    }
    /* Affiche le contenu --devrait pouvoir varier en fonction du type element-- */
    printf("└");

    fun(a->e);

    printf("\n");

    for (i=0; i<K; i++){
	kAffIndent(a->fils[i], indent + 1, fun);
    }
}


karbre kArbreCopy(karbre src){
    int i;
    karbre res;

    if (src == NULL){
	return(NULL);
    }
    if ((res = (karbre) malloc (sizeof(struct karbre_struct))) == NULL){
	return(NULL);
    }
    res->e = src->e;
    for (i=0; i<K; i++){
	res->fils[i] = kArbreCopy(src->fils[i]);
    }

    return(res);
}


void kFree(karbre a){
    int i;

    if (a != NULL){
	for (i=0; i<K; i++){
	    kFree(a->fils[i]);
	}
    }
    free(a);
}
