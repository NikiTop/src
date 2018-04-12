#include "main.h" //Из моей работы

//sound virable
HSTREAM stream;


float rat=(float) W_WIDTH / (float) W_HEIGHT;

//Функция завершения работы программы
void prog_exit(GLFWwindow *w)
{		
	if (!glfwWindowShouldClose(w))  {
           glfwDestroyWindow(w);
       }	
	glfwTerminate();
	printf("%s\n","Exit Ok");	
}


//Функция подсчета  и вывода FPS
void fps_counter(GLFWwindow *w, int t, char *caption, int w_mode)
{	
	
	if (fps_enable)	{
		current_time=glfwGetTime();
		frame+=1.0;
		if ((current_time - old_time)*1000 >= t) {
			frame_sum+=frame;		
			double fps= frame_sum /  (current_time) ;		
			sprintf(str_title,"%s: FPS:%.2f FPS_AVR:%.2f ",caption, frame/(t/1000), fps);		
			frame=0.0; old_time=current_time;	
			if (!w_mode)	
				glfwSetWindowTitle(w,str_title);
			printf("%s\n",str_title);
		}	
	}		
}

//Функция таймер анимации 
void timer_animation(int t)
{	

		current_time=glfwGetTime();		
		if ((current_time - old_time)*1000 >= t) {					
			old_time=current_time;	
			draw_animation(t);
			obj_respawn(t);
			//printf("timer_run %i\n",t);
		}			
}

int timer_game(int t)
{

		current_time_gm=glfwGetTime();		
		if ((current_time_gm - old_time_gm)*1000 >= t) {					
			old_time_gm = current_time_gm;
			game_log(t);
			//printf("timer_game_log %i\n",t);
		}
		
return 0;
}



//Функция обработки параметров командной строки
void argc_init(int argc, char **argv)
{
	int i;
	for(i=1;i<argc;i++) {	
		if (!strcmp(argv[i],"--info")){
			gl_info=1;glfw_info=1;	
		}
		if (!strcmp(argv[i],"--full")) {
			w_mode=1;
		}
		if (!strcmp(argv[i],"--fps")){
			fps_enable=1;
		}			
	}
}

//Функция основного цикла программы
void glfw_main_loop(GLFWwindow *w)
{
	 while( done )   {
		if( glfwWindowShouldClose(w) )  {
				done = 0;
		}
		glfwPollEvents();
		timer_animation(25);
		timer_game(150);
		ogl_draw();	
		
		
		fps_counter(w,F_TIME,W_CAPTION,w_mode);
		glfwSwapBuffers(w); 	
	}
	prog_exit(w);
}


//Основная программа
int main(int argc, char **argv)
{	
	argc_init(argc, argv);
	
	BASS_Init(-1, 44100, 0, 0, NULL);
	
	w_handle = glfw_window_init(W_WIDTH,W_HEIGHT,W_CAPTION,w_mode) ;
	glfw_window_set_params(w_handle, W_CAPTION, SWAP_INT);
	glew_init();
    ogl_init(W_WIDTH,W_HEIGHT);
    load_textures();
    ogl_print_info(gl_info);
	glfw_print_info(glfw_info);
	glfw_callback_init(w_handle);	
	glfw_main_loop(w_handle);
	return 0;	
}


