#ifndef _LAB_MAIN_H
#define _LAB_MAIN_H

#include "common.h"
#include "info.h"
#include "ogl.h"
#include "win.h"
#include "callback.h"

//Параметры окна
#define W_CAPTION  "SEA_SHIPS"
#define W_WIDTH 1024
#define W_HEIGHT 768
#define SWAP_INT 0
#define F_TIME 3000


//Список глобальных переменных
GLFWwindow *w_handle=NULL;
int done=1;

//переменные флаги для обработки командной строки
int gl_info=1,glfw_info=0,w_mode=0, fps_enable=0;

//переменные для подсчета fps
double frame=0.0, frame_sum=0.0, old_time=0.0, current_time=0.0, old_time_sp=0.0, current_time_sp=0.0, old_time_gm=0.0, current_time_gm=0.0, old_time_expl=0.0, current_time_expl=0.0;

char str_title[128];


//GL_POINTS=0,GL_LINES=1, GL_LINE_LOOP=2, GL_LINE_STRIP=3, GL_TRIANGLES=4, GL_TRIANGLE_FAN=5, 
//GL_TRIANGLE_STRIP=6, GL_QUADS=7, GL_QUAD_STRIP=8, GL_POLYGON=9
int draw_mode=4;
//-------------------------------------------END--------------------------------------------------//


#endif
