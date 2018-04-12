#ifndef _LAB_OGL_H
#define _LAB_OGL_H
#include "common.h"
#include "texture.h"

struct rect
{
float x,y,z;
float t0,s0;
float t1,s1;
float dx,dy,dz;
int vis;
};
typedef struct rect rect_t;

struct sound
{
HSAMPLE sam;
HCHANNEL ch;
int f_SND;
};
typedef struct sound sound_t;

struct number
{
rect_t n;
int tx;
};
typedef struct number number_t;

struct button
{
rect_t b;
int tx;
int f_focus;
};
typedef struct button button_t;

struct target
{
rect_t trg;
int tx;
int f_aim;
};
typedef struct target target_t;

struct gun
{
rect_t g;
float angle_x;
float angle_y;
int tx;
};
typedef struct gun gun_t;

struct bullet
{
rect_t sh;
rglVec3d_t V;
rglVec3d_t Vn;
int tx;
int f_vis;
int f_shot;
int f_shell_kd;
float shell_kd;
float angle_x;
float time_sp; 
float time_rt;
double sx0, sy0, sz0;
double sx1, sy1, sz1;
};
typedef struct bullet bullet_t;

struct magazine
{
rect_t mg;
int tx;
int f_full;
int f_shell;										//число снарядов в магазине 
};
typedef struct magazine magazine_t;

struct bomb
{
rect_t bo;
int tx;
int f_vis;
int f_strike;
float speed;

};
typedef struct bomb bomb_t;

struct airplane
{
rect_t a;
int f_aim;
int tx;
int f_vis;
int f_kill;
int f_ind;
int f_fin;
float time_sp; 
float time_rt;
float speed;
bomb_t bomb[10];
int f_bomb;
float bomb_kd;
float bomb_rt;
int f_bomb_kd;
};
typedef struct airplane airplane_t;

struct ship
{
rect_t s;
int tx;
int hp;
int f_kill;
int f_vis;
int f_fin;
int f_mortal;
float speed;
float time_sp;
float time_rt;
};
typedef struct ship ship_t; 

struct sprite
{
rect_t spt;
int tx;
int f_expl;
int fr_kol;
float angle_x;
float angle_y;
};
typedef struct sprite sprite_t;

int draw_animation(int t);
int obj_respawn(int t);
int shell_kd(int t);
void game_log(int t);

int load_textures();
void ogl_reshape(GLFWwindow *w, int width, int height);
void ogl_init(int width, int height);
void ogl_draw(void);
void glew_init(void);




#endif
