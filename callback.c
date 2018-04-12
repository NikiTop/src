#include "callback.h"

extern int h, w, done, f_scena, i, sh_k, sh_kol, f_help, s_fin, ap_fin, s_kol, ap_kol, flag_SND, final;
extern button_t bt_b, bt_e, bt_m, bt_a, bt_s;
extern magazine_t mag_1, mag_2;
extern bullet_t bullet[12];
extern sprite_t spt_flash;
extern airplane_t ap[10];
extern target_t targ;
extern ship_t ship;
extern bomb_t bomb;
extern gun_t gun;
extern rglMat4f_t pvm,mvm;
extern sound_t m_snd, pr_snd, sh_snd, expl_snd;

rglVec3d_t V, Vn;

int s_f_aim = 0;
double old_x=0.0, old_y;
double sx,sy,sz;

//функция реакции на нажатие клавиши
//GLFW_PRESS GLFW_REPEAT GLFW_RELEASE
void key_press(GLFWwindow *w, int key, int scancode, int action, int mods)
{
	if (( key == GLFW_KEY_ESCAPE ) && ( action == GLFW_PRESS)){
		//printf("Press - %i\n",key);
		if(f_scena==0)
			done = 0; 
		if(f_scena==1){
			f_scena = 0;
			f_help = 0;
			init_sound();
			glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
		}
		if(f_scena==2){
			f_scena = 0;
			init_sound();
			glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
		}
		if(f_scena==3){
			f_scena = 0;
			init_sound();
			glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
		}
		
		
	}
	if (( key == GLFW_KEY_F1) && ( action == GLFW_PRESS)) {
			
		if((f_scena==1)&&(f_help==0)){
			f_help = 1;	
		}
		else
			f_help = 0;
	}
	
	if (( key == GLFW_KEY_F2) && ( action == GLFW_PRESS)) {
	
		/*if((f_scena==1)&&(f_help==1)){
			f_help = 0;

		}*/
	}
	
	
	if (( key == GLFW_KEY_LEFT ) && (( action == GLFW_PRESS))){		//REPEAT

		
	}
	if (( key == GLFW_KEY_RIGHT  ) && (( action == GLFW_PRESS))){

			
	}
	if (( key == GLFW_KEY_DOWN  ) && (( action == GLFW_PRESS))){

	}	
	if (( key == GLFW_KEY_UP  ) && (( action == GLFW_PRESS))){

		
	}
	if (( key == GLFW_KEY_SPACE   ) && ( action == GLFW_PRESS)){
		
	}
	if (( key == GLFW_KEY_ENTER  ) && ( action == GLFW_PRESS)){

	}
}	
	


//функция реакции на ввод символов
void char_input(GLFWwindow *w, unsigned int ch)
{
	if ( ch == 'q' || ch == 'Q' )
		done=0;
	if (ch == 'f' || ch == 'F' )
		printf("Press - %c\n",ch);	
}



//функция реакции на нажатие кнопок мыши
void mouse_button_press(GLFWwindow *w, int button, int action, int mods)
{
	
//action is GLFW_PRESS or GLFW_RELEASE ,MBM_press=0,RBM_press=0
	if ( button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS){

			if((bt_e.f_focus==1)&&(f_scena==0)){
				BASS_ChannelPlay(pr_snd.ch, FALSE);
				done=0;
			}
			if((bt_b.f_focus==1)&&(f_scena==0)){
				BASS_ChannelPlay(pr_snd.ch, FALSE);
				f_scena=1;
				glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
				sh_kol = 13;
				final = 0;
				s_kol = 8, ap_kol = 8;
				s_fin = 8, ap_fin = 8;
				init_draw_object();
				init_airplane();
				init_target();
				init_button();
				init_bullet();
				init_sprite();
				init_ship();
				init_gun();
				init_mag();
				init_ind();
				init_sound();
			}
			if((bt_a.f_focus==1)&&((f_scena==2)||(f_scena==3))){
				BASS_ChannelPlay(pr_snd.ch, FALSE);
				f_scena=1;
				glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
				sh_kol = 13;
				final = 0;
				s_kol = 8, ap_kol = 8;
				s_fin = 8, ap_fin = 8;
				init_draw_object();
				init_airplane();
				init_target();
				init_button();
				init_bullet();
				init_sprite();
				init_ship();
				init_gun();
				init_mag();
				init_ind();
				init_sound();
			}
			if((bt_s.f_focus==1)&&(f_scena==0)&&(m_snd.f_SND==1)){
				m_snd.f_SND = 0;
			}
			else{
				m_snd.f_SND = 1;
				m_snd.ch=BASS_SampleGetChannel(m_snd.sam, FALSE);
			}	
			if((bt_m.f_focus==1)&&(f_scena==2)){
				BASS_ChannelPlay(pr_snd.ch, FALSE);
				done = 0;
				glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
			}
			if((bt_m.f_focus==1)&&(f_scena==3)){
				BASS_ChannelPlay(pr_snd.ch, FALSE);
				done = 0;
				glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
			}
			
			if(f_scena==1){
				
				if(sh_kol > 0){
					sh_kol-=1;
					if(sh_kol >= 6)
						mag_1.f_shell = sh_kol - mag_2.f_shell;
						
					if(sh_kol < 6)
						mag_2.f_shell = mag_2.f_shell - 1;

					for(sh_k=0; sh_k < 12; sh_k+=1){
						if((sh_kol>=0)&&(sh_kol<12)){
							spt_flash.f_expl = 1;
							BASS_ChannelPlay(sh_snd.ch, FALSE);
							bullet[sh_k].f_shell_kd = 1;
							spt_flash.angle_x = gun.angle_x;
							spt_flash.angle_y = gun.angle_y;
							bullet[sh_k].angle_x = gun.angle_x;
							bullet[sh_k].f_vis = 1;
							if(bullet[sh_k].f_vis==1){
							
								bullet[sh_k].sx1 = sx;
								bullet[sh_k].sy1 = sy;
								bullet[sh_k].sz1 = sz;
								
								rglVectorInit3d(&bullet[sh_k].V, ((bullet[sh_k].sx1-bullet[sh_k].sx0)),((bullet[sh_k].sy1-bullet[sh_k].sy0)),((bullet[sh_k].sz1-bullet[sh_k].sz0)));
								rglVectorCopy3d(&bullet[sh_k].Vn , bullet[sh_k].V);
								rglVectorInit3d(&bullet[sh_k].V, (bullet[sh_k].sx0),(bullet[sh_k].sy0),(bullet[sh_k].sz0));
								rglVectorNormalize3d(&bullet[sh_k].Vn);
								
							}
						}
					}
				}
			}
		}
	}
	if ( button == GLFW_MOUSE_BUTTON_MIDDLE){
		if (action == GLFW_PRESS){
			//MBM_press=1; printf("Press middle mouse button\n");;
		}
		else {
			//MBM_press=0; printf("Release middle mouse button\n");
		}
	}	
	if ( button == GLFW_MOUSE_BUTTON_RIGHT){
		if (action == GLFW_PRESS){
		
			
			//RBM_press=1; printf("Press right mouse button\n");
		}
		else {
			//RBM_press=0; printf("Release right mouse button\n");
		}	
	}	
}

int intersection_tmp(double xn, double yn, double zn, double xf, double yf, double zf, airplane_t b, double *rx, double *ry, double *rz)
{
	rglVec3d_t ray, rayn, ab,ad,ba,bc, n, xnv,  A,B,C;
	double k, x,y,z, r1, r2;
	rglVectorInit3d(&xnv, xn,yn,zn);
	rglVectorInit3d(&ray, xf-xn,yf-yn,zf-zn);
	rglVectorCopy3d(&rayn,ray);
	rglVectorNormalize3d(&rayn);
	rglVectorInit3d(&A, ((b.a.x-b.a.dx)),((b.a.y-b.a.dy)),b.a.z);
	rglVectorInit3d(&B, ((b.a.x-b.a.dx)),((b.a.y+b.a.dy)),b.a.z);
	rglVectorInit3d(&C, ((b.a.x+b.a.dx)),((b.a.y+b.a.dy)),b.a.z);
	
	rglVectorCopy3d(&ba,B);
	rglVectorSub3d(&ba,A);
	rglVectorCopy3d(&bc,B);
	rglVectorSub3d(&bc,C);
	rglVectorInit3d(&ab, ((b.a.x+b.a.dx)-(b.a.x-b.a.dx)),((b.a.y+b.a.dy)-(b.a.y+b.a.dy)),b.a.z);
	rglVectorInit3d(&ad, ((b.a.x-b.a.dx)-(b.a.x-b.a.dx)),((b.a.y-b.a.dy)-(b.a.y+b.a.dy)),b.a.z);
	rglVectorCross3d(&n,ba,bc);																			//векторное произведение
	rglVectorNormalize3d(&n);																			//нормализация
	
	
	rglVectorInit3d(&ab, ((b.a.x)-(xn)),((b.a.y)-(yn)),(b.a.z-zn));
	rglVectorInit3d(&ad, ((b.a.x)-(xf)),((b.a.y)-(yf)),(b.a.z-zf));
	r1=rglVectorDot3d(ab,n);																			//скалярное произведение
	r2=rglVectorDot3d(ad,n);																			//скалярное произведение
	if( SIGN(r1) == SIGN(r2) ) return 1;
	k = (-r1)/(r2-r1);
	
	x=xn+k*ray.x; 
	y=yn+k*ray.y; 
	z=zn+k*ray.z; 
	
	*rx = x;
	*ry = y;
	*rz = z;
	
	return 0;
}


int unProj(GLFWwindow *w, airplane_t ap, double *xn, double *yn, double *zn, double *xf, double *yf, double *zf) 
{
	int w_width, w_height;	
	double x,y;
	
	int v[4];
	rglMat4d_t mv,pv;
	glfwGetWindowSize(w, &w_width, &w_height);
	glfwGetCursorPos (w, &x, &y);
	y = w_height - y;
	glGetDoublev(GL_PROJECTION_MATRIX, pv);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, mv);
		
	//rglMatrixPrint4d(mv,"mv");
	//rglMatrixPrint4d(pv,"pv");
	glGetIntegerv(GL_VIEWPORT, v);
	//rglMatrixPrint4f(gl_pvm,"gl_pvm");
	//gluUnProject(x, y, 0.0, mv, pv, v, &fx, &fy, &fz);	
	//printf("glu pos scena: fx= %5.2f fy= %5.2f fz= %5.2f x= %5.2f y= %5.2f\n",fx,fy,fz,x,y);
	//gluUnProject(x, y, 1.0, mv, pv, v, &fx, &fy, &fz);	
	//printf("glu pos scena: fx= %5.2f fy= %5.2f fz= %5.2f x= %5.2f y= %5.2f\n",fx,fy,fz,x,y);
	rglUnProjectd(x, y, 0.0, mv, pv, v, xn, yn, zn);
	//printf("rgl pos scena: xn= %5.2f yn= %5.2f zn= %5.2f x= %5.2f y= %5.2f\n",xn,yn,zn,x,y);
	rglUnProjectd(x, y, 1.0, mv, pv, v, xf, yf, zf);
	//printf("rgl pos scena: xf= %5.2f yf= %5.2f zf= %5.2f x= %5.2f y= %5.2f\n",xf,yf, zf,x,y);
	
	return 0;
}



//функция реакции на движение мыши
void mouse_pos(GLFWwindow *w, double x, double y)
{
	
	int w_width, w_height;	
	double xn,yn,zn, xf,yf,zf, ax, ay, az;
	double dx, dy;
	//rglVec3d_t v1, v2;
	glfwGetWindowSize(w, &w_width, &w_height);
	
	
	y= w_height - y;
	
	//int w_width, w_height;
	//printf("mouse pos: x= %5.2f y= %5.2f\n",x,y);
	if(f_scena==0){
		if(((x>(bt_b.b.x-bt_b.b.dx))&&(x<(bt_b.b.x+bt_b.b.dx)))&&((y>(bt_b.b.y-bt_b.b.dy))&&(y<(bt_b.b.y+bt_b.b.dy)))){
			bt_b.f_focus = 1;
		}
		else{
			bt_b.f_focus = 0;
		}
		if(((x>(bt_e.b.x-bt_e.b.dx))&&(x<(bt_e.b.x+bt_e.b.dx)))&&((y>(bt_e.b.y-bt_e.b.dy))&&(y<(bt_e.b.y+bt_e.b.dy)))){
			bt_e.f_focus = 1;
		}
		else{
			bt_e.f_focus = 0;
		}
		if(((x>(bt_s.b.x-bt_s.b.dx))&&(x<(bt_s.b.x+bt_s.b.dx)))&&((y>(bt_s.b.y-bt_s.b.dy))&&(y<(bt_s.b.y+bt_s.b.dy)))){
			bt_s.f_focus = 1;
		}
		else{
			bt_s.f_focus = 0;
		}
	}
	if((f_scena==2)||(f_scena==3)){
		if(((x>(bt_a.b.x-bt_a.b.dx))&&(x<(bt_a.b.x+bt_a.b.dx)))&&((y>(bt_a.b.y-bt_a.b.dy))&&(y<(bt_a.b.y+bt_a.b.dy)))){
			bt_a.f_focus = 1;
		}
		else{
			bt_a.f_focus = 0;
		}		
	}
	
	if((f_scena==2)||(f_scena==3)){
		if(((x>(bt_m.b.x - bt_m.b.dx))&&(x<(bt_m.b.x + bt_m.b.dx)))&&((y>(bt_m.b.y - bt_m.b.dy))&&(y<(bt_m.b.y + bt_m.b.dy)))){
			bt_m.f_focus = 1;
		}
		else{
			bt_m.f_focus = 0;
		}
	}
	
	if(f_scena==1){

		targ.trg.x = x;
		targ.trg.y = y;
		
		s_f_aim = 0;
		for(i=0;i<8;i+=1){
			if(ap[i].f_vis==1){
				unProj(w,ap[i], &xn,&yn,&zn, &xf,&yf,&zf);
				
				intersection_tmp(xn,yn,zn, xf,yf,zf, ap[i], &ax, &ay, &az);
				sx = ax; sy = ay; sz = az;
				if(((ax>(ap[i].a.x-ap[i].a.dx))&&(ax<(ap[i].a.x+ap[i].a.dx)))&&((ay>(ap[i].a.y-ap[i].a.dy))&&(ay<(ap[i].a.y+ap[i].a.dy)))){
					ap[i].f_aim = 1;
				}
				else{
					ap[i].f_aim = 0;
				}
				s_f_aim += ap[i].f_aim;
			}
		}
		if(s_f_aim > 0)
			targ.f_aim = 1;
		else
			targ.f_aim = 0;
			
			
			dx=(float)(w_width/2.0-x)/(float)(w_width/2.0);
			dx=dx*60;
			gun.angle_x = dx;
			old_x = x;

			if(y > 0){
				dy=(float)(w_height/2+y)/(float)(w_height/2);
				dy=dy*15;
				gun.angle_y=dy;
				old_y = y;
			} 
				
	}
	
	if((f_scena==2)||(f_scena==3)){
	
		if(s_kol==0)				
			glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
				
		if(final==6)	
			glfwSetInputMode(w,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
		
	}

	//ogl_draw_scena_0;
	//c_x=x; c_y=y;	
	//glfwGetWindowSize(w, &w_width, &w_height);
	//cursor_draw(w_width, w_height, x, y, -2.0);
	
	

}

//функция реакции на прокрутку колеса мыши
void mouse_wheel(GLFWwindow *w, double x, double y)
{	
		
		//xx+=x;yy+=y;
	//	printf("Wheel pos x= %5.2f y= %5.2f\n",xx,yy);	
}

