#include "ogl.h"

int f_scena = 0, f_help = 0, sh_kol = 13, final = 0, i, j, k, sh_k, b1, b2, l, tx, ty; 
int w=1024,h=768;																			 //размеры окна
float wf=1024.0,hf=768.0;
float dw=1024.0,dh=768.0;

double expl_time = 0.0, expl_old_time = 0.0;

int s_kol = 8, ap_kol = 8;
int s_fin = 8, ap_fin = 8;

extern double sx,sy,sz;

// pvm - проекционно-видовая матрица
// pvm - модельно-видовая матрица
rglMat4f_t pvm,mvm,t_mvm,s_mvm,e_mvm;



//Текстура для теста
char *Txf_test="../../data/textures/test.png";


//Фон
char *Txf_fon_00="../../data/textures/fon_00.png";
char *Txf_fon_01="../../data/textures/fon_01.png";
char *Txf_fon_02="../../data/textures/fon_02.png";
char *Txf_fon_03="../../data/textures/fon_03.png";

//Заглавие
char *Txf_title_01="../../data/textures/title_01.png";

//Кнопки
char *Txf_button="../../data/textures/button.png";
char *Txf_bt_again="../../data/textures/again.png";
char *Txf_bt_music="../../data/textures/mus.png";

//hud
char *Txf_hud="../../data/textures/hud.png";

//Объекты
char *Txf_ap_air_00="../../data/textures/ap_air_00.png";
char *Txf_ap_air_01="../../data/textures/ap_air_01.png";
char *Txf_ap_air_02="../../data/textures/ap_air_02.png";
char *Txf_ap_air_03="../../data/textures/ap_air_03.png";
char *Txf_ap_air_04="../../data/textures/ap_air_04.png";
char *Txf_ap_air_05="../../data/textures/ap_air_05.png";
char *Txf_ap_air_06="../../data/textures/ap_air_06.png";
char *Txf_ap_air_07="../../data/textures/ap_air_07.png";
char *Txf_ap_air_08="../../data/textures/ap_air_08.png";
char *Txf_ap_air_09="../../data/textures/ap_air_09.png";
char *Txf_ship_00="../../data/textures/ship_00.png";
char *Txf_bomb="../../data/textures/bomb.png";

//Справка
char *Txf_help="../../data/textures/help.png";

//Прицел
char *Txf_target_r="../../data/textures/target_r.png";
char *Txf_target_y="../../data/textures/target_y.png";
char *Txf_target_g="../../data/textures/target_g.png";

//Зенитка, магазин, снаряд
char *Txf_bfg="../../data/textures/bfg.png";
char *Txf_mag="../../data/textures/mag.png";
char *Txf_shell="../../data/textures/bullet.png";
char *Txf_shell_i="../../data/textures/bullet_i.png";

//Вода
char *Txf_water="../../data/textures/water.png";

//Цифры 
char *Txf_number="../../data/textures/number.png";
char *Txf_slash="../../data/textures/slash.png";

//Победа_поражение_ещё раз
char *Txf_lose="../../data/textures/lose_title.png";
char *Txf_win="../../data/textures/win_title.png";

//Спрайт взрыва
char *Txf_spt_expl="../../data/textures/explode.png";
char *Txf_spt_wat_expl="../../data/textures/smoke.png";
char *Txf_spt_flash="../../data/textures/flashes.png";
char *Txf_spt_air_expl="../../data/textures/air_expl.png";

//Звуки
char *snd_m="../../data/sound/main_theme.mp3";
char *snd_pr="../../data/sound/press.wav";
char *snd_sh="../../data/sound/shot.wav";
char *snd_expl="../../data/sound/explosive.wav";


GLuint tex_ap_air_00, tex_ap_air_01, tex_ap_air_02, tex_ap_air_03, tex_ap_air_04, tex_ap_air_05, tex_ap_air_06, tex_ap_air_07, tex_ap_air_08, tex_ap_air_09;
GLuint tex_water, tex_ship_00, tex_fon_00, tex_fon_01, tex_fon_02, tex_fon_03, tex_help, tex_button, tex_bt_menu, tex_shell_i, tex_hud, tex_bt_again;
GLuint tex_bomb, tex_target_r, tex_target_y, tex_target_g, tex_bfg, tex_mag, tex_shell, tex_bt_music;
GLuint tex_title_01, tex_win, tex_lose, tex_test, tex_number, tex_slash;
GLuint tex_spt_expl, tex_spt_wat_expl, tex_spt_flash, tex_spt_air_expl;


rect_t fon_00, fon_01, fon_02, fon_03, title, water, shell, ship_i, ap_i, shell_i, win, lose, hud, help, test, slash1, slash2;
sprite_t spt_expl, spt_wat_expl, spt_flash, spt_air_expl;
number_t numb_s, numb_s_fin, numb_ap, numb_ap_fin, numb_shell;
magazine_t mag_1, mag_2;
button_t bt_b, bt_e, bt_m, bt_a, bt_s;
bullet_t bullet[12];
airplane_t ap[8];
ship_t ship[8];
target_t targ;
gun_t gun;
sound_t m_snd, pr_snd, sh_snd, expl_snd;


double tx_old_time=0.0,tx_time=0.0;
double time, old_time;


rglVec3f_t vec_pos={0.0,1.0,0.0}, vec_dir={0.0,0.0,-100}, vec_up={0.0,1.0,0.0};



int init_draw_object() 
{
	title.x = wf/2.0; title.y = 725; title.z=-3.0;  title.s0=0.0; title.s1=1.0; title.t0=0.0; title.t1=1.0; title.dx=256; title.dy=32; title.dz=0.0;

	fon_00.x = wf/2.0; fon_00.y = hf/2.0; fon_00.z=-5.0;  fon_00.s0=0.0; fon_00.s1=1.0; fon_00.t0=0.0; fon_00.t1=1.0; fon_00.dx=dw/2.0; fon_00.dy=dh/2.0; fon_00.dz=0.0;

	fon_01.x = 0.0; fon_01.y = 11.5; fon_01.z=-100.0;  fon_01.s0=0.0; fon_01.s1=1.0; fon_01.t0=0.0; fon_01.t1=1.0; fon_01.dx=80.0; fon_01.dy=50.0; fon_01.dz=0.0;
	
	fon_02.x = wf/2.0; fon_02.y = hf/2.0; fon_02.z=-5.0;  fon_02.s0=0.0; fon_02.s1=1.0; fon_02.t0=0.0; fon_02.t1=1.0; fon_02.dx=dw/2.0; fon_02.dy=dh/2.0; fon_02.dz=0.0;
	
	fon_03.x = wf/2.0; fon_03.y = hf/2.0; fon_03.z=-5.0;  fon_03.s0=0.0; fon_03.s1=1.0; fon_03.t0=0.0; fon_03.t1=1.0; fon_03.dx=dw/2.0; fon_03.dy=dh/2.0; fon_03.dz=0.0;

	water.x = 0.0; water.y = -10.0; water.z=0.0; water.s0=0.0; water.s1=1.0; water.t0=0.0; water.t1=1.0; water.dx=200.0; water.dy=0.0; water.dz=200.0;

	shell.x	= 14; shell.y = 40; shell.z = -2.0; shell.s0 = 0.0; shell.s1 = 1.0; shell.t0 = 0.0; shell.t1 = 1.0; shell.dx = 6.5; shell.dy = 24; shell.dz = 0;
	
	ship_i.x = 133; ship_i.y = 740; ship_i.z = 10.0; ship_i.s0 = 0.0; ship_i.s1 = 1.0; ship_i.t0 = 0.0; ship_i.t1 = 1.0; ship_i.dx = 75.0; ship_i.dy = 17.0; ship_i.dz = 0;
	
	ap_i.x = 830; ap_i.y = 738; ap_i.z = 10.0; ap_i.s0 = 0.0; ap_i.s1 = 1.0; ap_i.t0 = 0.0; ap_i.t1 = 1.0; ap_i.dx = -40.0; ap_i.dy = 15.0; ap_i.dz = 0;
	
	shell_i.x = wf/2.0 - 30; shell_i.y = 740; shell_i.z = 10.0; shell_i.s0 = 0.0; shell_i.s1 = 1.0; shell_i.t0 = 0.0; shell_i.t1 = 1.0; shell_i.dx = 40.0; shell_i.dy = 10.0; shell_i.dz = 0;
	
	hud.x = wf/2.0; hud.y = 738; hud.z = 9.0; hud.s0 = 0.0; hud.s1 = 1.0; hud.t0 = 0.0; hud.t1 = 1.0; hud.dx = 512.0; hud.dy = 30.0; hud.dz = 0;
	
	win.x = wf/2.0; win.y = 720; win.z = 3.0; win.s0 = 0.0; win.s1 = 1.0; win.t0 = 0.0; win.t1 = 1.0; win.dx = 174.0; win.dy = 51.0; win.dz = 0; 
	
	lose.x = wf/2.0; lose.y = 720; lose.z = 3.0; lose.s0 = 0.0; lose.s1 = 1.0; lose.t0 = 0.0; lose.t1 = 1.0; lose.dx = 256.0; lose.dy = 42.0; lose.dz = 0;
	
	help.x = 255; help.y = 625; help.z = 3.0; help.s0 = 0.0; help.s1 = 1.0; help.t0 = 0.0; help.t1 = 1.0; help.dx = 256.0; help.dy = 82.0; help.dz = 0;
	
	test.x = 0.0; test.y = 0.0; test.z = 0.0; test.s0 = 0.0; test.s1 = 1.0; test.t0 = 0.0; test.t1 = 1.0; test.dx = 0.1; test.dy = 0.0; test.dz = -0.2;
	
	slash1.x = 950.0; slash1.y = 738.0; slash1.z = 0.0; slash1.s0 = 0.0; slash1.s1 = 1.0; slash1.t0 = 0.0; slash1.t1 = 1.0; slash1.dx = 16.0; slash1.dy = 16.0; slash1.dz = 0.0;
	
	slash2.x = 280.0; slash2.y = 738.0; slash2.z = 0.0; slash2.s0 = 0.0; slash2.s1 = 1.0; slash2.t0 = 0.0; slash2.t1 = 1.0; slash2.dx = 16.0; slash2.dy = 16.0; slash2.dz = 0.0;

	return 0;
}

int init_ind()
{
	numb_s.n.x = 250; numb_s.n.y = 738; numb_s.n.z = 10.0; numb_s.n.s0=0.0; numb_s.n.s1=1.0; numb_s.n.t0=0.0; numb_s.n.t1=1.0; numb_s.n.dx=16; numb_s.n.dy=16; numb_s.n.dz=0.0; 
	
	numb_s_fin.n.x = 310; numb_s_fin.n.y = 738; numb_s_fin.n.z = 10.0; numb_s_fin.n.s0=0.0; numb_s_fin.n.s1=1.0; numb_s_fin.n.t0=0.0; numb_s_fin.n.t1=1.0; numb_s_fin.n.dx=16; numb_s_fin.n.dy=16; numb_s_fin.n.dz=0.0; 
	
	numb_ap.n.x = 920; numb_ap.n.y = 738; numb_ap.n.z = 10.0; numb_ap.n.s0=0.0; numb_ap.n.s1=1.0; numb_ap.n.t0=0.0; numb_ap.n.t1=1.0; numb_ap.n.dx=16; numb_ap.n.dy=16; numb_ap.n.dz=0.0; 
	
	numb_ap_fin.n.x = 980; numb_ap_fin.n.y = 738; numb_ap_fin.n.z = 10.0; numb_ap_fin.n.s0=0.0; numb_ap_fin.n.s1=1.0; numb_ap_fin.n.t0=0.0; numb_ap_fin.n.t1=1.0; numb_ap_fin.n.dx=16; numb_ap_fin.n.dy=16; numb_ap_fin.n.dz=0.0; 
	
	numb_shell.n.x = wf/2.0 + 60; numb_shell.n.y = 738; numb_shell.n.z = 10.0; numb_shell.n.s0=0.0; numb_shell.n.s1=1.0; numb_shell.n.t0=0.0; numb_shell.n.t1=1.0; numb_shell.n.dx=16; numb_shell.n.dy=16; numb_shell.n.dz=0.0; 
	
	
	return 0;
}

int init_button()
{
	bt_b.b.x = 143; bt_b.b.y = 170; bt_b.b.z = -3.0; bt_b.b.s0=0.0; bt_b.b.s1=1.0; bt_b.b.t0=0.75; bt_b.b.t1=1.0; bt_b.b.dx=128; bt_b.b.dy=32; bt_b.b.dz=0.0; bt_b.f_focus = 0; bt_b.tx = tex_button;
	
	bt_e.b.x = 143; bt_e.b.y = 70; bt_e.b.z = -3.0; bt_e.b.s0=0.0; bt_e.b.s1=1.0; bt_e.b.t0=0.25; bt_e.b.t1=0.5; bt_e.b.dx=126; bt_e.b.dy=32; bt_e.b.dz=0.0; bt_e.f_focus = 0; bt_e.tx = tex_button;

	bt_m.b.x = 143; bt_m.b.y = 70; bt_m.b.z = -3.0; bt_m.b.s0=0.0; bt_m.b.s1=1.0; bt_m.b.t0=0.25; bt_m.b.t1=0.5; bt_m.b.dx=126; bt_m.b.dy=32; bt_m.b.dz=0.0; bt_m.f_focus = 0; bt_m.tx = tex_button;
	
	bt_a.b.x = 900; bt_a.b.y = 70; bt_a.b.z = -3.0; bt_a.b.s0=0.0; bt_a.b.s1=1.0; bt_a.b.t0=0.5; bt_a.b.t1=1.0; bt_a.b.dx=126; bt_a.b.dy=32; bt_a.b.dz=0.0; bt_a.f_focus = 0; bt_a.tx = tex_bt_again;
	
	bt_s.b.x = 950; bt_s.b.y = 70; bt_s.b.z = -3.0; bt_s.b.s0=0.0; bt_s.b.s1=1.0; bt_s.b.t0=0.25; bt_s.b.t1=0.5; bt_s.b.dx=32; bt_s.b.dy=32; bt_s.b.dz=0.0; bt_s.f_focus = 0; bt_s.tx = tex_bt_music;
	
	
	return 0;
}

int init_target()
{
	targ.trg.x = wf/2.0; targ.trg.y = hf/2.0; targ.trg.z = -3.0;  targ.trg.s0 = 0.0; targ.trg.s1 = 1.0; targ.trg.t0 = 0.0; targ.trg.t1 = 1.0; targ.trg.dx = 16; targ.trg.dy = 16; targ.trg.dz = 0.0;
	targ.f_aim = 0; targ.tx = tex_target_r;

	return 0;
}

int init_gun()
{
	gun.g.x = 0.0; gun.g.y = 0.0; gun.g.z = 0.0;  gun.g.s0 = 0.0; gun.g.s1 = 1.0; gun.g.t0 = 0.0; gun.g.t1 = 1.0; gun.g.dx =0.15; gun.g.dy = 0.0; gun.g.dz = -0.8;
	gun.tx = tex_bfg; 
	
	return 0;
}

int init_bullet()
{
	for(sh_k = 0; sh_k < 12; sh_k+=1){
		bullet[sh_k].sh.x	= 0.0; bullet[sh_k].sh.y = 0.0; bullet[sh_k].sh.z = 0.0; bullet[sh_k].sh.s0 = 0.0; bullet[sh_k].sh.s1 = 1.0; bullet[sh_k].sh.t0 = 0.0; bullet[sh_k].sh.t1 = 1.0; bullet[sh_k].sh.dx = 0.02; bullet[sh_k].sh.dy = 0.04; bullet[sh_k].sh.dz = -0.1;
		bullet[sh_k].tx = tex_shell; 
		bullet[sh_k].sx0 = 0.0; bullet[sh_k].sy0 = 0.0; bullet[sh_k].sz0 = 0.0; bullet[sh_k].sx1 = 0.0; bullet[sh_k].sy1 = 0.0; bullet[sh_k].sz1 = 0.0; bullet[sh_k].angle_x = 0.0;
		bullet[sh_k].f_vis = 0; bullet[sh_k].f_shot = 0; bullet[sh_k].f_shell_kd = 5000; bullet[sh_k].time_rt = 0.0; bullet[sh_k].time_sp = 0.0; 
	
	}
	
	return 0;
}

int init_mag()
{
	mag_1.mg.x = 943.0; mag_1.mg.y = 40.0; mag_1.mg.z = -3.0; mag_1.mg.s0 = 0.0; mag_1.mg.s1 = 1.0; mag_1.mg.t0 = 0.0; mag_1.mg.t1 = 1.0; mag_1.mg.dx = 81; mag_1.mg.dy = 30; mag_1.mg.dz = 0.0; mag_1.tx = tex_mag;
	mag_1.f_full = 1; mag_1.f_shell = 7;
	
	mag_2.mg.x = 80.0; mag_2.mg.y = 40.0; mag_2.mg.z = -3.0; mag_2.mg.s0 = 0.0; mag_2.mg.s1 = 1.0; mag_2.mg.t0 = 0.0; mag_2.mg.t1 = 1.0; mag_2.mg.dx = -81; mag_2.mg.dy = 30; mag_2.mg.dz = 0.0; mag_2.tx = tex_mag;
	mag_2.f_full = 1; mag_2.f_shell = 6;
	
	return 0;
}

int init_airplane()
{
	for(i=0;i<8;i+=1){
		ap[i].a.x = 120.0; ap[i].a.y = 15.0 + (float)(rand()%2); ap[i].a.z = -90.0; ap[i].a.s0 = 0.0; ap[i].a.s1 = 1.0; ap[i].a.t0 = 0.0; ap[i].a.t1 = 1.0; ap[i].a.dx = 4.3; ap[i].a.dy = 1.5; ap[i].a.dz = 0.0;
		ap[i].f_vis = 0; ap[i].speed = 0.05 + (float)(rand()%10)/1000.0 ; ap[i].time_sp=i*9000; ap[i].time_rt=0; ap[i].f_bomb = 0; ap[i].bomb_kd=5000; ap[i].f_bomb_kd = 0; ap[i].bomb_rt = 0; ap[i].f_ind = 1;
		ap[i].f_aim = 0; ap[i].f_kill = 0; ap[i].f_fin = 0;
		
		for(j=0;j<10;j+=1){
			ap[i].bomb[j].bo.x = -150.0; ap[i].bomb[j].bo.y = ap[i].a.y-3.0; ap[i].bomb[j].bo.z = -95.0; ap[i].bomb[j].bo.s0 = 0.0; ap[i].bomb[j].bo.s1 = 1.0; ap[i].bomb[j].bo.t0 = 0.0; ap[i].bomb[j].bo.t1 = 1.0; ap[i].bomb[j].bo.dx= 0.5; ap[i].bomb[j].bo.dy = 1.0; ap[i].bomb[j].bo.dz = 0.0;
			ap[i].bomb[j].f_vis = 0; ap[i].bomb[j].f_strike = 0; ap[i].bomb[j].tx = tex_bomb;
		}
	}

	
	ap[0].f_vis = 1; ap[0].tx = tex_ap_air_00; ap[1].tx = tex_ap_air_01; ap[2].tx = tex_ap_air_02; ap[3].tx = tex_ap_air_03; ap[4].tx = tex_ap_air_04; 
	ap[5].tx = tex_ap_air_05; ap[6].tx = tex_ap_air_06; ap[7].tx = tex_ap_air_07; //ap[8].tx = tex_ap_air_08; //ap[9].tx = tex_ap_air_09;
	
	
	return 0;
}


int init_ship()
{
	for(k=0;k<8;k+=1){
		ship[k].s.x = -70; ship[k].s.y = -2.0; ship[k].s.z = -90.0 + (float)(rand()%10); ship[k].s.s0 = 0.0; ship[k].s.s1 = 1.0; ship[k].s.t0 = 0.0; ship[k].s.t1 = 1.0;ship[k].s.dx = 12.0; ship[k].s.dy = 3.0; ship[k].s.dz = 0.0; 
		ship[k].f_kill = 0; ship[k].f_vis = 0;  ship[k].speed = 0.09 + (float)(rand()%10)/1000.0; ship[k].time_sp=k*10000; ship[k].time_rt=0; 
		ship[k].f_mortal = 0; ship[k].f_fin = 0;
		
	}
	
	
	ship[0].f_vis = 1; ship[0].tx = tex_ship_00; ship[1].tx = tex_ship_00; ship[2].tx = tex_ship_00; ship[3].tx = tex_ship_00; 
	ship[4].tx = tex_ship_00; ship[5].tx = tex_ship_00; ship[6].tx = tex_ship_00; ship[7].tx = tex_ship_00;
	
	return 0;
}

int init_sprite()
{
	spt_expl.spt.x = 0.0; spt_expl.spt.y = 0.0; spt_expl.spt.z = 0.0; spt_expl.spt.s0 = 0.0; spt_expl.spt.s1 = 0.0625; spt_expl.spt.t0 = 0.0; spt_expl.spt.t1 = 1.0; spt_expl.spt.dx = 4.0; spt_expl.spt.dy = 4.0; spt_expl.spt.dz = 0.0;
	spt_expl.tx = tex_spt_expl; spt_expl.f_expl = 0; spt_expl.fr_kol = 0;
	
	spt_wat_expl.spt.x = 0.0; spt_wat_expl.spt.y = 0.0; spt_wat_expl.spt.z = 0.0; spt_wat_expl.spt.s0 = 0.0; spt_wat_expl.spt.s1 = 0.1; spt_wat_expl.spt.t0 = 0.0; spt_wat_expl.spt.t1 = 0.0; spt_wat_expl.spt.dx = 2.0; spt_wat_expl.spt.dy = 6.0; spt_wat_expl.spt.dz = 0.0;
	spt_wat_expl.tx = tex_spt_wat_expl; spt_wat_expl.f_expl = 0; spt_wat_expl.fr_kol = 0;
	
	spt_flash.spt.x = 0.0; spt_flash.spt.y = 0.0; spt_flash.spt.z = 0.0; spt_flash.spt.s0 = 0.0; spt_flash.spt.s1 = 0.3; spt_flash.spt.t0 = 0.0; spt_flash.spt.t1 = 1.0; spt_flash.spt.dx = 0.2; spt_flash.spt.dy = 0.0; spt_flash.spt.dz = -0.4;
	spt_flash.tx = tex_spt_flash; spt_flash.f_expl = 0; spt_flash.fr_kol = 0;
	
	spt_air_expl.spt.x = 0.0; spt_air_expl.spt.y = 0.0; spt_air_expl.spt.z = 0.0; spt_air_expl.spt.s0 = 0.0; spt_air_expl.spt.s1 = 0.125; spt_air_expl.spt.t0 = 0.0; spt_air_expl.spt.t1 = 1.0; spt_air_expl.spt.dx = 2.0; spt_air_expl.spt.dy = 2.0; spt_air_expl.spt.dz = 0.0;
	spt_air_expl.tx = tex_spt_air_expl; spt_air_expl.f_expl = 0; spt_air_expl.fr_kol = 0;
	
	
	return 0;
}

int init_sound()
{
	m_snd.sam = BASS_SampleLoad(FALSE, snd_m,0,0,2 , BASS_SAMPLE_LOOP); m_snd.ch = BASS_SampleGetChannel(m_snd.sam, FALSE ); m_snd.f_SND = 1;
	
	pr_snd.sam = BASS_SampleLoad(FALSE, snd_pr,0,0,2 , 0); pr_snd.ch = BASS_SampleGetChannel(pr_snd.sam, FALSE ); pr_snd.f_SND = 0;
	
	sh_snd.sam = BASS_SampleLoad(FALSE, snd_sh,0,0,2 , 0); sh_snd.ch = BASS_SampleGetChannel(sh_snd.sam, FALSE ); sh_snd.f_SND = 0;
	
	expl_snd.sam = BASS_SampleLoad(FALSE, snd_expl,0,0,2 , 0); expl_snd.ch = BASS_SampleGetChannel(expl_snd.sam, FALSE ); expl_snd.f_SND = 0;
	
	return 0;
}

void rglGetError(void)
{
	GLuint error=glGetError();
	if (error== GL_NO_ERROR)
		printf("NO ERROR \n");
	if (error== GL_INVALID_ENUM)
		printf("ERROR GL_INVALID_ENUM \n");
	if (error== GL_INVALID_VALUE)
		printf("ERROR GL_INVALID_VALUE \n");
	if (error== GL_INVALID_OPERATION)
		printf("ERROR GL_INVALID_OPERATION \n");
	if (error== GL_INVALID_FRAMEBUFFER_OPERATION)
		printf("ERROR GL_INVALID_FRAMEBUFFER_OPERATION \n");
	if (error== GL_OUT_OF_MEMORY)
		printf("ERROR GL_OUT_OF_MEMORY \n");
}

//Функция инициализации библиотеки GLEW
void glew_init(void)
{
	int err = glewInit();
	if (GLEW_OK != err)	{ 
		printf("Error: %s\n", glewGetErrorString(err));	
		glfwTerminate(); exit( EXIT_FAILURE );
	}
	else {
		printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));		
	}	
	}

int set_ortographic(int w, int h)
{
	glMatrixMode(GL_PROJECTION);		
	rglMatrixIdentity4f(pvm);
	glLoadMatrixf(pvm);
	rglOrthof(pvm,0,w,0,h,-10.0f, 10.0f);	
	glLoadMatrixf(pvm);
	glMatrixMode(GL_MODELVIEW);
	rglMatrixIdentity4f(mvm);
	glLoadMatrixf(mvm);

return 0;
}

int set_perspectiv(int w, int h)
{
	glMatrixMode(GL_PROJECTION);		
	rglMatrixIdentity4f(pvm);
	glLoadMatrixf(pvm);
	float rat= (float) w /(float) h;	
	rglPerspectivef(pvm, 45.0f, rat, 0.1f, 1000.0f);
	glLoadMatrixf(pvm);
	glMatrixMode(GL_MODELVIEW);
	rglMatrixIdentity4f(mvm);
	glLoadMatrixf(mvm);

return 0;
}


// flag_pvm: 0 - ortographic 1 - perspectiv
int set_pvm(int flag_pvm)
{
	if (flag_pvm) 
		set_perspectiv(w,h);
	else
		set_ortographic(w,h);

return 0;
}



//Функция изменения размеров окна
void ogl_reshape(GLFWwindow *w, int width, int height)
{
	if (height == 0)
			height = 1;	
		glViewport(0, 0, width, height);	
		ogl_init(width, height);		
}

//Функция инициализации OpenGL
void ogl_init(int width, int height)

{
	//получение размеров окна для модуля ogl
	w=width;
	h=height;
	//perescop_dx=(float)w,perescop_dy=(float)h;
	//fon_dx=(float)w,fon_dy=(float)h;
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);	
	glEnable(GL_DEPTH_TEST);
	set_pvm(0);	
	//set_ortographic(w,  h);
	//load_textures();
	
	init_sound();
	
}


void draw_rect(rect_t r)
{
		glBegin(GL_TRIANGLE_STRIP);	
		
		glColor3f(1.0,0.0,0.0);
			glTexCoord2f(r.s0,r.t0);		
			glVertex3f(r.x-r.dx, r.y-r.dy, r.z-r.dz);				

			glColor3f(0.0,0.0,1.0);
			glTexCoord2f(r.s0,r.t1);		
			glVertex3f(r.x-r.dx, r.y+r.dy, r.z+r.dz);
			
			glColor3f(0.0,1.0,0.0) ;
			glTexCoord2f(r.s1,r.t0);		
			glVertex3f(r.x+r.dx, r.y-r.dy, r.z-r.dz) ;
			
			
			glColor3f(0.0,1.0,1.0) ;
			glTexCoord2f(r.s1,r.t1);			
			glVertex3f(r.x+r.dx, r.y+r.dy, r.z+r.dz) ;
		
			
			
		 glEnd();
		 
}

int sound(sound_t sn)
{	
		if (sn.f_SND==1)
			BASS_ChannelPlay(sn.ch, FALSE);
			
		if (sn.f_SND==0)
			BASS_ChannelStop(sn.ch);
			
	return 0;
}


int draw_ind(int k, rect_t r)
{
	if(k==0){
		r.s0 = 0.0;
		r.s1 = 0.1;
		draw_rect(r);
	}

	while(k>0){
		l = k%10;
		r.s0 = l/10.0;
		r.s1 = r.s0+0.1;
		draw_rect(r);
		k = k/10;
		r.x-=30;
	}
	
return 0;
}

void draw_button()
{
	if(f_scena==0){
				
		if(bt_b.f_focus==0) {
			bt_b.b.t0 = 0.75; bt_b.b.t1 = 1.0;
			glBindTexture(GL_TEXTURE_2D, bt_b.tx); 
		}
		
		if(bt_b.f_focus==1){
			bt_b.b.t0 = 0.5; bt_b.b.t1 = 0.75;
			glBindTexture(GL_TEXTURE_2D, bt_b.tx); 
		}
		
		draw_rect(bt_b.b);	
	
		if(bt_e.f_focus==0){
			bt_e.b.t0 = 0.25; bt_e.b.t1 = 0.5;
			glBindTexture(GL_TEXTURE_2D, bt_e.tx); 
		}
		
		if(bt_e.f_focus==1){
			bt_e.b.t0 = 0.0; bt_e.b.t1 = 0.25;
			glBindTexture(GL_TEXTURE_2D, bt_e.tx); 
		}
		
		draw_rect(bt_e.b);
	}
}

void draw_m_bt()
{
		if(bt_m.f_focus==0){
			bt_m.b.t0 = 0.25; bt_m.b.t1 = 0.5;
		}

		if(bt_m.f_focus==1){
			bt_m.b.t0 = 0.0; bt_m.b.t1 = 0.25;
		}
		glBindTexture(GL_TEXTURE_2D, bt_m.tx);
		draw_rect(bt_m.b);
}

void draw_a_bt()
{
		if(bt_a.f_focus==0){
			bt_a.b.t0 = 0.5; bt_a.b.t1 = 1.0;
		}

		if(bt_a.f_focus==1){
			bt_a.b.t0 = 0.0; bt_a.b.t1 = 0.5;
		}
		glBindTexture(GL_TEXTURE_2D, bt_a.tx);
		draw_rect(bt_a.b);
}

void draw_s_bt()
{
		if((bt_s.f_focus==0)&&(m_snd.f_SND==1)){
			bt_s.b.t0 = 0.25; bt_s.b.t1 = 0.5;
		}
		if((bt_s.f_focus==0)&&(m_snd.f_SND==0)){
			bt_s.b.t0 = 0.75; bt_s.b.t1 = 1.0;
		}
		if((bt_s.f_focus==1)&&(m_snd.f_SND==1)){
			bt_s.b.t0 = 0.0; bt_s.b.t1 = 0.25;
		}
		if((bt_s.f_focus==1)&&(m_snd.f_SND==0)){
			bt_s.b.t0 = 0.5; bt_s.b.t1 = 0.75;
		}
		glBindTexture(GL_TEXTURE_2D, bt_s.tx);
		draw_rect(bt_s.b);
}


int draw_bomb(bomb_t b)
{
			
		if(b.f_vis==1)
			{
				glBindTexture(GL_TEXTURE_2D, b.tx);
				draw_rect(b.bo);
			} 

return 0;
}

int draw_airplane(airplane_t a)
{
		
			if(a.f_vis==1)
				{
					glBindTexture(GL_TEXTURE_2D, a.tx);
					draw_rect(a.a);
					for(j=0;j<10;j+=1){
						 draw_bomb(a.bomb[j]);
					} 
			}

return 0;
}

int draw_ship(ship_t s)
{
	
	if(s.f_vis==1)
		{
			glBindTexture(GL_TEXTURE_2D, s.tx);
			draw_rect(s.s);
		} 

return 0;
}

int draw_target(target_t targ)
{
	if(targ.f_aim==0)
		targ.tx = tex_target_r;
	
	if(targ.f_aim==1)
		targ.tx = tex_target_y;
	
	set_pvm(0);	
			glBindTexture(GL_TEXTURE_2D, targ.tx);
			draw_rect(targ.trg);
	set_pvm(1);

return 0;
}

int draw_gun(gun_t g)
{
			glBindTexture(GL_TEXTURE_2D, g.tx);
			draw_rect(g.g);
			
return 0;
}

int draw_mag(magazine_t mg)
{
	set_pvm(0);
	
		glBindTexture(GL_TEXTURE_2D, tex_mag);
		draw_rect(mg.mg);

		
	set_pvm(1);
	
return 0;
}

int draw_shell(rect_t sh)
{
	set_pvm(0);
	
	glBindTexture(GL_TEXTURE_2D, tex_shell);
	for(b1=0; b1<mag_1.f_shell; b1+=1){	
				draw_rect(sh);			//Отрисовка снаряда	
				sh.x+=26.5; 
			}
	sh.x = 876;
	for(b2=0; b2<mag_2.f_shell; b2+=1){
				draw_rect(sh);			//Отрисовка снаряда
				sh.x+=26.5; 
			}
			
	set_pvm(1);
return 0;
}

int draw_bullet(bullet_t b)
{
	
	if(b.f_vis==1)
		{
			glBindTexture(GL_TEXTURE_2D, b.tx);
			draw_rect(b.sh);
		} 

return 0;
}

int draw_spt(sprite_t s)
{
	if(s.f_expl==1)
		{
			glBindTexture(GL_TEXTURE_2D, s.tx);
			draw_rect(s.spt);
		
		}	
	
return 0;
}


int load_textures()
{
	//Тестовый треугольничек
	rglLoadTextures(Txf_test,&tex_test);

	//Текстура фона 
	rglLoadTextures(Txf_fon_00,&tex_fon_00);
	rglLoadTextures(Txf_fon_01,&tex_fon_01);
	rglLoadTextures(Txf_fon_02,&tex_fon_02);
	rglLoadTextures(Txf_fon_03,&tex_fon_03);
	
	//Помощь
	rglLoadTextures(Txf_help,&tex_help);
	
	//Текстура названия
	rglLoadTextures(Txf_title_01,&tex_title_01);
	
	//Текстуры кнопок 
	rglLoadTextures(Txf_button,&tex_button);
	rglLoadTextures(Txf_bt_again,&tex_bt_again);
	rglLoadTextures(Txf_bt_music,&tex_bt_music);
	
	//Текстуры объектов
	rglLoadTextures(Txf_ap_air_00,&tex_ap_air_00);
	rglLoadTextures(Txf_ap_air_01,&tex_ap_air_01);
	rglLoadTextures(Txf_ap_air_02,&tex_ap_air_02);
	rglLoadTextures(Txf_ap_air_03,&tex_ap_air_03);
	rglLoadTextures(Txf_ap_air_04,&tex_ap_air_04);
	rglLoadTextures(Txf_ap_air_05,&tex_ap_air_05);
	rglLoadTextures(Txf_ap_air_06,&tex_ap_air_06);
	rglLoadTextures(Txf_ap_air_07,&tex_ap_air_07);
	rglLoadTextures(Txf_ap_air_08,&tex_ap_air_08);
	rglLoadTextures(Txf_ap_air_09,&tex_ap_air_09);
	rglLoadTextures(Txf_ship_00,&tex_ship_00);
	
	
	//Текстуры прицела
	rglLoadTextures(Txf_target_r,&tex_target_r);
	rglLoadTextures(Txf_target_y,&tex_target_y);
	rglLoadTextures(Txf_target_g,&tex_target_g);
	
	//Текстура зенитки, магазина, снарядов, бомб
	rglLoadTextures(Txf_bfg,&tex_bfg);
	rglLoadTextures(Txf_mag,&tex_mag);
	rglLoadTextures(Txf_shell,&tex_shell);
	rglLoadTextures(Txf_shell_i,&tex_shell_i);
	rglLoadTextures(Txf_bomb,&tex_bomb);
	
	//Текстура воды
	rglLoadTextures(Txf_water,&tex_water);
	
	//Текстура цифр, победа_поражение
	rglLoadTextures(Txf_number,&tex_number);
	rglLoadTextures(Txf_slash,&tex_slash);
	rglLoadTextures(Txf_hud,&tex_hud);
	rglLoadTextures(Txf_win,&tex_win);
	rglLoadTextures(Txf_lose,&tex_lose);
	
	//Текстуры спрайтов
	rglLoadTextures(Txf_spt_expl,&tex_spt_expl);
	rglLoadTextures(Txf_spt_wat_expl,&tex_spt_wat_expl);
	rglLoadTextures(Txf_spt_flash,&tex_spt_flash);
	rglLoadTextures(Txf_spt_air_expl,&tex_spt_air_expl);

	
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

	
return 0;
}


void timer_explosive(int t)
{

	if(spt_expl.f_expl==1){
	
		expl_time = glfwGetTime();
		
		if ((expl_time - expl_old_time)*1000 >= t) {					
			expl_old_time = expl_time;
				spt_expl.spt.s0 = spt_expl.fr_kol*0.0625;
				spt_expl.spt.s1 = spt_expl.spt.s0 + 0.0625;;
			spt_expl.fr_kol+=1;
			if(spt_expl.fr_kol > 15){
				spt_expl.f_expl = 0;
				spt_expl.fr_kol = 0;
			}
		}
	}
	
	if(spt_air_expl.f_expl==1){
	
		expl_time = glfwGetTime();
		
		if ((expl_time - expl_old_time)*1000 >= t) {					
			expl_old_time = expl_time;
				spt_air_expl.spt.s0 = spt_air_expl.fr_kol*0.125;
				spt_air_expl.spt.s1 = spt_air_expl.spt.s0 + 0.125;
			spt_air_expl.fr_kol+=1;
			if(spt_air_expl.fr_kol > 7){
				spt_air_expl.f_expl = 0;
				spt_air_expl.fr_kol = 0;
			}
		}
	
	}
	
	if(spt_wat_expl.f_expl==1){
		
		expl_time = glfwGetTime();
		
		if ((expl_time - expl_old_time)*1000 >= t) {					
			expl_old_time = expl_time;
			spt_wat_expl.spt.s0 = spt_wat_expl.fr_kol*0.1;
			spt_wat_expl.spt.s1 = spt_wat_expl.spt.s0 + 0.1;
			spt_wat_expl.fr_kol+=1;
			if(spt_wat_expl.fr_kol > 9){
				spt_wat_expl.f_expl = 0;
				spt_wat_expl.fr_kol = 0;
			}
		}
	}
	
	if(spt_flash.f_expl==1){
		
		expl_time = glfwGetTime();
		
		if ((expl_time - expl_old_time)*1000 >= t) {					
			expl_old_time = expl_time;
			spt_flash.spt.s0 = spt_flash.fr_kol*0.3;
			spt_flash.spt.s1 = spt_flash.spt.s0 + 0.3;
			spt_flash.fr_kol+=1;
			if(spt_flash.fr_kol > 2){
				spt_flash.f_expl = 0;
				spt_flash.fr_kol = 0;
			}
		}
	}
	
}


int obj_respawn(int t) 
{		
	//самолёты
	for(i=0;i<8;i+=1){
		if ((ap[i].f_vis==0)&&(ap[i].f_kill==0))
			ap[i].time_rt+=t;
		if ((ap[i].time_rt >= ap[i].time_sp)&&(ap[i].f_kill==0))
			ap[i].f_vis=1; 
		if (ap[i].f_bomb_kd==1)
			ap[i].bomb_rt+=t;
		if (ap[i].bomb_rt >= ap[i].bomb_kd){
			ap[i].f_bomb_kd = 0; 
			ap[i].bomb_rt = 0.0;
		}
		
	}
	
	//корабли			
	for(k=0;k<8;k+=1){
		if ((ship[k].f_vis==0)&&(ship[k].f_kill==0))
			ship[k].time_rt+=t;
		if ((ship[k].time_rt >= ship[k].time_sp)&&(ship[k].f_kill==0)){
			ship[k].f_vis=1;
			ship[k].time_rt = 0.0;
		}
	}
	
return 0;	
} 

int draw_animation(int t){ 											//функция задающая перемещение кораблей, бомб, самолётов
	if(f_scena==1){
		for(k=0;k<8;k+=1){
			if((ship[k].f_vis==1)&&(ship[k].f_kill==0))
				ship[k].s.x+=ship[k].speed;							//ВИДИМЫЙ корабль движется
			if(ship[k].f_kill==1){
				ship[k].s.y-=0.07;
				if(ship[k].s.y<=water.y)
					ship[k].f_vis = 0;
			}		
			for(i=0;i<8;i+=1){
				if((ap[i].f_vis==1)&&(ap[i].f_kill==0)){
					ap[i].a.x-=ap[i].speed;							//ВИДИМЫЙ cамолёт движется
					for(j=0;j<10;j+=1){
						if(ap[i].bomb[j].f_vis==0)
							ap[i].bomb[j].bo.x = ap[i].a.x; 		//НЕВИДИМАЯ бомба движется вместе с самолётом
						else{
							ap[i].bomb[j].bo.y-=0.1;				//бомба стала видимой и полетела вниз
							ap[i].bomb[j].bo.x-=ap[i].speed;
						}	
					}
				}
				if(ap[i].f_kill==1)
					ap[i].f_vis = 0;
			}
		}
	}


return 0;
}

void game_log(int t)				//функция "игровой логики"
{							
	if(f_scena==1){
		for(k=0;k<8;k+=1){
			for(sh_k=0; sh_k<12; sh_k+=1){
				for(i=0;i<8;i+=1){
					if(ap[i].f_bomb_kd==0){
						if((ap[i].a.x <= (ship[k].s.x+ship[k].s.dx))&&(ap[i].f_kill==0)&&(ship[k].f_kill==0)){ 		//проверка того что самолёт над кораблём	
							ap[i].f_bomb_kd = 1;																	//включается таймер "кд" бомбы
							if(ap[i].f_bomb < 10){
								ap[i].bomb[ap[i].f_bomb].f_vis = 1; 												//делаем бомбу видимой
								ap[i].f_bomb+=1;																	//наращиваем кол-во бомб до 10
							}
						}
					}
					if(((ship[k].s.x+(ship[k].s.dx/1.3)) < -50)||((ship[k].s.x+(ship[k].s.dx/1.3) > 55)))
						ship[k].f_mortal = 1;																		//во избежании конфликтов по правому краю сцены, корабль станет бессмертным
					else
						ship[k].f_mortal = 0;	
					
					for(j=0;j<10;j+=1){
						if((ap[i].bomb[j].f_vis==1)&&(ap[i].f_vis==1)){
							if(ap[i].bomb[j].bo.y<=ship[k].s.y)
								if((ap[i].bomb[j].bo.x<=(ship[k].s.x+(ship[k].s.dx/1.3)))&&(ap[i].bomb[j].bo.x>=(ship[k].s.x-(ship[k].s.dx/1.3))))
									if((ship[k].f_kill==0)&&(ship[k].f_mortal==0)){	
										ap[i].bomb[j].f_vis = 0;													//бомба стала невидимой	
											spt_expl.spt.x = ap[i].bomb[j].bo.x;
											spt_expl.spt.y = ap[i].bomb[j].bo.y;
											spt_expl.spt.z = ap[i].bomb[j].bo.z;
										spt_expl.f_expl = 1;														//флаг начала работы спрайта взрыва корабля
										BASS_ChannelPlay(expl_snd.ch, FALSE);
										ship[k].f_kill = 1;															//корабль убит											
										s_kol-=1;																	//количество живых кораблей умньшилось
									}
						}
						if(ap[i].bomb[j].bo.y <= water.y)									
							ap[i].bomb[j].f_vis = 0;																//бомба соприкоснулась с водой и стала невидимой	
					}
					
					if(bullet[sh_k].f_vis==1){
						rglVectorScale3d(&bullet[sh_k].Vn, 1.0);
						rglVectorAdd3d(&bullet[sh_k].V, bullet[sh_k].Vn);
						if(bullet[sh_k].V.z < ap[i].a.z){															//пуля взрывается не опав в самолёт
							bullet[sh_k].f_vis = 0;
								spt_air_expl.spt.x = bullet[sh_k].V.x;
								spt_air_expl.spt.y = bullet[sh_k].V.y;
								spt_air_expl.spt.z = bullet[sh_k].V.z;
							spt_air_expl.f_expl = 1;
						}
						
						if(((bullet[sh_k].V.x > (ap[i].a.x - (ap[i].a.dx/1.3)))&&(bullet[sh_k].V.x < (ap[i].a.x + (ap[i].a.dx/1.3))))&&(bullet[sh_k].V.y > (ap[i].a.y - (ap[i].a.dy/1.3))&&(bullet[sh_k].V.y < (ap[i].a.y + (ap[i].a.dy/1.3))))){
							if(ap[i].f_kill==0){																	//условие поражения самолёта
								bullet[sh_k].f_vis = 0;
									spt_air_expl.spt.x = bullet[sh_k].V.x;
									spt_air_expl.spt.y = bullet[sh_k].V.y;
									spt_air_expl.spt.z = bullet[sh_k].V.z;
								spt_air_expl.f_expl = 1;
								BASS_ChannelPlay(expl_snd.ch, FALSE);
								ap[i].f_kill = 1;																	//самолёт умер
								ap_kol-=1;																			//количесвто живых самолётов уменьшилось
							}
						}
					}
					
					if((ap[i].a.x < -60.0)&&(ap[i].f_kill==0)&&(ap[i].f_fin==0)){									//условие финиша корабля
						ap[i].f_fin = 1;
						ap[i].f_vis = 0;
						ap_fin-=1;
						ap_kol-=1;
					}
					
					if((ship[k].s.x > 60.0)&&(ship[k].f_kill==0)&&(ship[k].f_fin==0)){								//условие финиша корабля
						ship[k].f_vis = 0;
						ship[k].f_fin = 1;
						//printf("final = %d\n",final);
						final+=1;
						s_fin-=1;
						s_kol-=1;
					}	
				}
			}
		}
	}
	
	if(s_kol==0)								//Условие поражения
		f_scena = 2;
		
	if(final==6)								//Условие победы
		f_scena = 3;	
}


void  ogl_draw_scena_0(void)
{
	set_pvm(0);	

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	
	//Отрисовка фона
	glBindTexture(GL_TEXTURE_2D, tex_fon_00); 
	draw_rect(fon_00);
	
	//Отрисовка заглавия
	glBindTexture(GL_TEXTURE_2D, tex_title_01); 
	draw_rect(title);
	
	//Отрисовка кнопок
	draw_button();
	
	//Музыка
	sound(m_snd);
	
	//Кнопка музыки
	draw_s_bt();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
}


void  ogl_draw_scena_1(void)
{
	set_pvm(1);	
	
	rglLookAtf(mvm, vec_pos, vec_dir, vec_up);
	glLoadMatrixf(mvm);
	
	glEnable(GL_TEXTURE_2D);
	

		
	//Отрисовка фона
	glBindTexture(GL_TEXTURE_2D, tex_fon_01); 
	draw_rect(fon_01);

	
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	//Отрисовка кораблей
	for(k=0;k<8;k+=1){
		draw_ship(ship[k]);
	}
	//Отрисовка самолётов
	for(i=0;i<8;i+=1){
		draw_airplane(ap[i]);
	}
	
	//Отрисовка воды
	glBindTexture(GL_TEXTURE_2D, tex_water);
	draw_rect(water);
	
	//Отрисовка "пуль"
	for(sh_k=0; sh_k < 12; sh_k+=1){
		rglMatrixIdentity4f(mvm);
		rglLookAtf(mvm, vec_pos, vec_dir, vec_up);
		glLoadMatrixf(mvm);
		rglTranslatef( mvm, 0.0, 0.0, -2.3);
		rglTranslatef( mvm, bullet[sh_k].V.x, bullet[sh_k].V.y, bullet[sh_k].V.z);
		rglRotatef( mvm, bullet[sh_k].angle_x,0.0, 1.0, 0.0);
		glLoadMatrixf(mvm);
	
		draw_bullet(bullet[sh_k]);
	}
	
		
	rglMatrixIdentity4f(mvm);	
	rglLookAtf(mvm, vec_pos, vec_dir, vec_up);
	glLoadMatrixf(mvm);
	
	
	//Отрисовка спрайта
	draw_spt(spt_expl);
	draw_spt(spt_air_expl);
	
	
	//Отрисовка зенитки
	rglTranslatef( mvm, 0.0, 0.0, -2.3);
	rglRotatef( mvm, gun.angle_x,0.0, 1.0, 0.0);
	rglRotatef( mvm, gun.angle_y,1.0, 0.0, 0.0);
	
	glLoadMatrixf(mvm);

	draw_gun(gun);
	
	//Отрисовка спрайта выстрела	
	rglTranslatef( mvm, -0.05, 0.0, -1.2);
	glLoadMatrixf(mvm);
	glBindTexture(GL_TEXTURE_2D, tex_test); 
	draw_spt(spt_flash);
	
	rglMatrixIdentity4f(mvm);	
	rglLookAtf(mvm, vec_pos, vec_dir, vec_up);
	glLoadMatrixf(mvm);

	
	//Отрисовка прицела
	draw_target(targ);
	
	//Отрисовка магазина
	draw_mag(mag_1);
	draw_mag(mag_2);
	
	//Отрисовка справки
	set_pvm(0);
	
	if(f_help==1){
		glBindTexture(GL_TEXTURE_2D, tex_help);
		draw_rect(help);
	}
	
	set_pvm(1);
	
	//Индикаторы
	set_pvm(0);
	
		glBindTexture(GL_TEXTURE_2D, tex_hud); 
		draw_rect(hud);
	
		glBindTexture(GL_TEXTURE_2D, tex_ship_00); 
		draw_rect(ship_i);
		
		glBindTexture(GL_TEXTURE_2D, tex_shell_i); 
		draw_rect(shell_i);
		
		glBindTexture(GL_TEXTURE_2D, tex_ap_air_04); 
		draw_rect(ap_i);

	set_pvm(1);
	
	//Отрисовка индикатора
	set_pvm(0);
	
	glBindTexture(GL_TEXTURE_2D, tex_slash);
	
		draw_rect(slash1);
		draw_rect(slash2);
	
	glBindTexture(GL_TEXTURE_2D, tex_number);
	
	draw_ind(s_kol, numb_s.n);
	draw_ind(s_fin, numb_s_fin.n);
	draw_ind(ap_kol, numb_ap.n);
	draw_ind(ap_fin, numb_ap_fin.n);
	draw_ind((mag_2.f_shell+mag_1.f_shell), numb_shell.n);
	
	set_pvm(1);
	
	//Отрисовка снарядов в магазине
	draw_shell(shell);


	glEnable(GL_DEPTH_TEST);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
}

//Сцена поражения
void  ogl_draw_scena_2(void)
{
	set_pvm(0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	glBindTexture(GL_TEXTURE_2D, tex_fon_02);
	draw_rect(fon_02);
	
	draw_m_bt();
	
	draw_a_bt();
	
	glBindTexture(GL_TEXTURE_2D, tex_lose);
	draw_rect(lose);
	
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
}

//Сцена победы
void  ogl_draw_scena_3(void)
{
	set_pvm(0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBindTexture(GL_TEXTURE_2D, tex_fon_03);
	draw_rect(fon_03);
	
	//Кнопка "в меню"
	draw_m_bt();
	
	//Кнопка "ещё раз"
	draw_a_bt();
	
	glBindTexture(GL_TEXTURE_2D, tex_win);
	draw_rect(win);
	
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
}

//Функция отрисовки
void  ogl_draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	
	if (f_scena==0)
		ogl_draw_scena_0();
	
	if (f_scena==1){
		ogl_draw_scena_1();
		timer_explosive(50);
	}
	
	if (f_scena==2)
		ogl_draw_scena_2();
	
	if (f_scena==3)
		ogl_draw_scena_3();

}