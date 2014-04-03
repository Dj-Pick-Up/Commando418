#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "structs.h"
#include "config.h"
#include "keyboard.h"
#include "display.h"


void kbDown(unsigned char key, int x, int y){
    switch(key){
	case FORWARD_KEY :
	    kTab[FORWARD_BIT] = 1;
	    break;
	case BACKWARD_KEY :
	    kTab[BACKWARD_BIT] = 1;
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
	p1.x += cos(p1.angle) * MOV_UNIT * deltaMoment;
	p1.y += 0;
	p1.z += sin(p1.angle) * MOV_UNIT * deltaMoment;
    }
    if (kTab[BACKWARD_BIT]){
	p1.x -= cos(p1.angle) * MOV_UNIT * deltaMoment;
	p1.y -= 0;
	p1.z -= sin(p1.angle) * MOV_UNIT * deltaMoment;
    }
    if (kTab[LEFT_BIT]){
	p1.angle -= TURN_UNIT * deltaMoment;
	while (p1.angle < 0) p1.angle += 2 * M_PI;
    }
    if (kTab[RIGHT_BIT]){
	p1.angle += TURN_UNIT * deltaMoment;
	while (p1.angle >= 2 * M_PI) p1.angle -= 2 * M_PI;
    } 
    if (kTab[FIRE_BIT]){   
	fire();
    }
///* DEBUG */ printf("(%f,%f,%f) [%f]\n", p1.x, p1.y, p1.z, p1.angle);
}


void mouseMoveManager(int x, int y){
    if (x < WIN_WIDTH / 2){
	p1.angle -= TURN_UNIT * deltaMoment;
    }
    if (x > WIN_WIDTH / 2){
	p1.angle += TURN_UNIT * deltaMoment;
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
