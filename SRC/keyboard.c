	/********************************
	 *	    keyboard		*
	 *==============================*
	 * Alexis Braine -		*
	 *		  Arslen Remaci *
	 *------------------------------*
	 * Gestion du clavier / souris	*
	 ********************************/


#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "structs.h"
#include "config.h"
#include "keyboard.h"
#include "display.h"
#include "players.h"
#include "main.h"


void kbDown(unsigned char key, int x, int y){
    switch(key){
	case FORWARD_KEY :
	    kTab[FORWARD_BIT] = 1;
	    break;
	case BACKWARD_KEY :
	    kTab[BACKWARD_BIT] = 1;
	    break;
	case STRAF_LEFT_KEY :
	    kTab[STRAF_LEFT_BIT] = 1;
	    break;
    	case STRAF_RIGHT_KEY :
	    kTab[STRAF_RIGHT_BIT] = 1;
	    break;
	case LEFT_KEY :
	    kTab[LEFT_BIT] = 1;
	    break;
    	case RIGHT_KEY :
	    kTab[RIGHT_BIT] = 1;
	    break;
   	case FIRE_KEY :
	    kTab[FIRE_BIT] = 1;
	    break;
	case NOCLIP_KEY :
	    kTab[NOCLIP_BIT] = !kTab[NOCLIP_BIT];
	    if (kTab[DEBUG_BIT]) printf("¤ NoClip mode %s\n", kTab[NOCLIP_BIT]?"active":"desactive");
	    break;
	case CAM_KEY :
	    kTab[CAM_BIT] = !kTab[CAM_BIT];
	    if (kTab[DEBUG_BIT]) printf("¤ Camera en mode %s\n", kTab[CAM_BIT]?"aerien":"vue 3e personne");
	    break;
	case RANGE_KEY :
	    kTab[RANGE_BIT] = !kTab[RANGE_BIT];
	    if (kTab[DEBUG_BIT]) printf("¤ Portée visuelle à %d\n", kTab[RANGE_BIT]?MAX_RANGE:MIN_RANGE);
	    break;
	case DEBUG_KEY :
	    kTab[DEBUG_BIT] = !kTab[DEBUG_BIT];
	    printf("¤ DEBUG mode %s\n", kTab[DEBUG_BIT]?"active":"desactive");
	    break;
	case MUTE_KEY :
	    kTab[MUTE_BIT] = !kTab[MUTE_BIT];
	    if (kTab[DEBUG_BIT]) printf("¤ Mode silencieux %s\n", kTab[MUTE_BIT]?"active":"desactive");
	    break;
	case EXIT_KEY :
	    properQuit();
	    break;
	case GODMODE_KEY :
	    kTab[GODMODE_BIT] = !kTab[GODMODE_BIT];
	    if (kTab[DEBUG_BIT]) printf("¤ God Mode %s\n", kTab[GODMODE_BIT]?"active":"desactive");
	    break;
    }
}


void kbUp(unsigned char key, int x, int y){
    switch(key){
	case FORWARD_KEY :
	    kTab[FORWARD_BIT] = 0;
	    break;
	case BACKWARD_KEY :
	    kTab[BACKWARD_BIT] = 0;
	    break;
	case STRAF_LEFT_KEY :
	    kTab[STRAF_LEFT_BIT] = 0;
	    break;
    	case STRAF_RIGHT_KEY :
	    kTab[STRAF_RIGHT_BIT] = 0;
	    break;
	case LEFT_KEY :
	    kTab[LEFT_BIT] = 0;
	    break;
    	case RIGHT_KEY :
	    kTab[RIGHT_BIT] = 0;
	    break;
   	case FIRE_KEY :
	    kTab[FIRE_BIT] = 0;
	    break;
    }
}


void kbManage(){
    if (kTab[FORWARD_BIT]){
	goForward(&pTab.p[0]);
    }
    if (kTab[BACKWARD_BIT]){
	goBackward(&pTab.p[0]);
    }
    if (kTab[STRAF_LEFT_BIT]){
	goLeft(&pTab.p[0]);
    }
    if (kTab[STRAF_RIGHT_BIT]){
	goRight(&pTab.p[0]);
    }
    if (kTab[LEFT_BIT]){
	lookLeft(&pTab.p[0]);
    }
    if (kTab[RIGHT_BIT]){
	lookRight(&pTab.p[0]);
    } 
    if (kTab[FIRE_BIT]){   
	fire(&pTab.p[0]);
    }
///* DEBUG */ printf("(%f,%f,%f) [%f]\n", pTab.p[0].x, pTab.p[0].y, pTab.p[0].z, pTab.p[0].angle);
}


void mouseMoveManager(int x, int y){
    if (x < WIN_WIDTH / 2){
	lookLeft(&pTab.p[0]);
    }
    if (x > WIN_WIDTH / 2){
	lookRight(&pTab.p[0]);
    }

   if (x != WIN_WIDTH / 2 || y != WIN_HEIGHT / 2){ 
	glutWarpPointer(WIN_WIDTH / 2, WIN_HEIGHT / 2);
   }
}


void clickManager(int key, int state, int x, int y){
    if (key == GLUT_LEFT_BUTTON){
	if (state == GLUT_DOWN){
	    kTab[FIRE_BIT] = 1;
	}
	if (state == GLUT_UP){
	    kTab[FIRE_BIT] = 0;
	}
    }
}
