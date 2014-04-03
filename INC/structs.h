#ifndef DEF_STRUCTS
#define DEF_STRUCTS

/* CONSTS */
/* Les durées de vie sont en millisecondes */
/* Les facteurs de vitesse de déplacement (MOV_UNIT, etc) sont en case/milliseconde */
#define WIN_HEIGHT 600
#define WIN_WIDTH 600

#define X_MIN 0
#define X_MAX 200
#define Z_MIN 0
#define Z_MAX 200

#define FORWARD_KEY 'z'
#define BACKWARD_KEY 's'
#define LEFT_KEY 'q'
#define RIGHT_KEY 'd'
#define FIRE_KEY ' '

#define MOV_UNIT 0.005
#define TURN_UNIT 0.0004
#define RANGE 200

#define MAX_PROJ 16
#define PROJ_MOV 0.02
#define PROJ_TTL 2000

#define MAX_PRESSED_KEYS 4

#define NB_KEYS 5
#define FORWARD_BIT 0
#define BACKWARD_BIT 1
#define LEFT_BIT 2
#define RIGHT_BIT 3
#define FIRE_BIT 4

#define MAX_PLAYERS 4

#define MAX_FIRE_COOLDOWN 100

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

/* Les players */
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

/* Les clés enfoncées */
typedef char keyTab[NB_KEYS];

#endif
