#ifndef _LAB_CALLBACK_H
#define _LAB_CALLBACK_H
#include "common.h"
#include "ogl.h"

void key_press(GLFWwindow *w, int key, int scancode, int action, int mods);
void char_input(GLFWwindow *w, unsigned int ch);
void mouse_button_press(GLFWwindow *w, int button, int action, int mods);
void mouse_pos(GLFWwindow *w, double x, double y);
void mouse_wheel(GLFWwindow *w, double x, double y);

int init_ind();
int init_button();
int init_target();
int init_gun();
int init_bullet();
int init_mag();
int init_airplane();
int init_ship();
int init_sprite();
int init_draw_object();
int init_sound();
#endif
