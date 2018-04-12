#include "win.h"

//Функция инициализации обработки функций обратного вызова
void glfw_callback_init(GLFWwindow *w)
{
	glfwSetFramebufferSizeCallback(w,ogl_reshape);  	
	glfwSetKeyCallback(w,key_press);	
	glfwSetCharCallback(w,char_input);	
	glfwSetMouseButtonCallback(w,mouse_button_press);	
	glfwSetCursorPosCallback(w,mouse_pos);	
	glfwSetScrollCallback(w,mouse_wheel);	   
}
//Функция инициализации предварительных параметров окна
void glfw_context_init()
{
	glfwWindowHint(GLFW_CLIENT_API,GLFW_OPENGL_API);
	 //Params:
//GLFW_SAMPLES , GLFW_OPENGL_DEBUG_CONTEXT, GLFW_OPENGL_FORWARD_COMPAT, GLFW_WINDOW_NO_RESIZE
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
 //GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_COMPAT_PROFILE or GLFW_OPENGL_CORE_PROFILE
	  
	  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);  
	//  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); отключить diprecared функционал	   
	 
}

//Функция инициализации предварительных параметров окна
void glfw_window_init_params(GLFWwindow *w)
{
	 //glfwWindowHint(GLFW_SAMPLES, 4);
	 glfw_context_init();
}
//Функция инициализации GLFW и создания окна
GLFWwindow *glfw_window_init(int width, int height, char *caption, int w_mode)
{
	GLFWwindow *temp_handle=NULL;
	const GLFWvidmode *video_mode=NULL;
	GLFWmonitor *primary_monitor=NULL;
	 if( !glfwInit() ){
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
	 }	
	 glfw_window_init_params(temp_handle);
	if(w_mode==0) {
		
		temp_handle=glfwCreateWindow(width,height,caption,NULL,NULL);
	}
	else {
		primary_monitor=glfwGetPrimaryMonitor();
		video_mode=glfwGetVideoMode(primary_monitor);
		
		temp_handle=glfwCreateWindow( video_mode->width,video_mode->height,caption,primary_monitor,NULL);
	}
	if( temp_handle ) {		
		glfwMakeContextCurrent(temp_handle);		
		return 	temp_handle;
	}
	else {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }		
}
//Функция задания параметров окна
void glfw_window_set_params(GLFWwindow *w, char *caption, int swap_int)
{
	glfwSetWindowTitle(w,caption); //заголовок окна
	glfwSetWindowPos(w,100, 100);	// позиция верхнего левого угла на экране
	glfwSwapInterval( swap_int ); // интервал обновления экранного буфера  
	//glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);  //отображение курсора GLFW_CURSOR_NORMAL GLFW_CURSOR_HIDDEN GLFW_CURSOR_DISABLED
	glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_NORMAL); 
	 glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
}




