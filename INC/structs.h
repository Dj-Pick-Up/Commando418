#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include <math.h>

/* CONSTS */
/* Les durées de vie sont en millisecondes */
/* Les facteurs de vitesse de déplacement (MOV_UNIT, etc) sont en case/milliseconde */
/* Paramètres de la fenêtre */
#define WIN_HEIGHT 1000
#define WIN_WIDTH 1000
/* Dimensions du terrain */
// On doit avoir X_MAX - X_MIN une puissance de 2
// De même pour Z_MAX - Z_MIN
#define X_MIN 0
#define X_MAX 64
#define Z_MIN 0
#define Z_MAX 64
#define G_WIDTH (X_MAX - X_MIN)
#define G_HEIGHT (Z_MAX - Z_MIN)
/* Keybindings */
#define FORWARD_KEY 'z'
#define BACKWARD_KEY 's'
#define LEFT_KEY 'q'
#define RIGHT_KEY 'd'
#define FIRE_KEY ' '
#define NOCLIP_KEY 'n'
#define CAM_KEY 'c'
#define RANGE_KEY 'r'
/* Dimensions de la hitbox du joueur */
#define X_HITBOX 0.4
#define Z_HITBOX 0.4
/* Unités de déplacement du joueur */
#define MOV_UNIT 0.004
#define TURN_UNIT 0.0025
#define MIN_RANGE 10
#define MAX_RANGE G_WIDTH + G_HEIGHT
/* Unités de déplacement des projectiles */
#define MAX_PROJ 16
#define PROJ_MOV 0.01
#define PROJ_TTL 2000
#define MAX_FIRE_COOLDOWN 200
/* Matrice des états des touches */
#define NB_KEYS 8
#define FORWARD_BIT 0
#define BACKWARD_BIT 1
#define LEFT_BIT 2
#define RIGHT_BIT 3
#define FIRE_BIT 4
#define NOCLIP_BIT 5
#define CAM_BIT 6
#define RANGE_BIT 7
/* Nombre maximal de joueurs ou équivalent (IA) */
#define MAX_PLAYERS 4
/* Caractères de la carte */
#define OBSTACLE_CHAR 1
#define FREE_CHAR 0
#define EXIT_CHAR 2
#define MIXED_CHAR -1
/* Camera */
#define MAX_CAM_HEIGHT 30
#define CAM_MOV 0.04
#define RANGE_MOV 0.1

/* STRUCTS */
typedef struct point_struct{
    float x;
    float y;
    float z;
} point;

/* Les projectiles */
typedef struct projectile_struct{
    float x;	    //	|
    float y;	    //	|> coordonnées
    float z;	    //	|
    float angle;    // angle de déplacement sur le plan (x,z)
    int ttl;	    // durée de vie
}projectile;

typedef struct projectiles_struct{
    projectile p[MAX_PROJ];
    int n;	    // nombre de projectiles en cours
}projectiles;

/* Les joueurs (ou IA) */
typedef struct player_struct{
    float x;
    float y;
    float z;
    float angle;
    projectiles proj;
    int fire_cooldown;
}player;

typedef struct players_structs{
    player p[MAX_PLAYERS];
    int n;
}players;

/* Les touches enfoncées */
typedef char keyTab[NB_KEYS];

#endif
