// THOR - The God of Thunder
//Source code released to the public domain on March 27th, 2020.

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
#include <alloc.h>
#include <string.h>
#include <fcntl.h>
#include <share.h>
#include <dos.h>
#include <dir.h>

#include <res_man.h>
#include <2_define.h>
#include <2_proto.h>
//============================================================================
extern char far *bg_pics;
extern char far objects[NUM_OBJECTS][262];
extern char far *sd_data;
extern char *tmp_buff;
//extern char file_str[10];
extern char res_file[];
extern THOR_INFO thor_info;
extern int current_area;
extern ACTOR *thor;
extern char *save_filename;
extern union REGS in,out;
extern SETUP setup;
extern char level_type,slow_mode;
extern int  boss_active;
extern char area;
extern char test_sdf[];
extern char far *song;
extern char far *lzss_buff;
extern char *options_yesno[];
extern int music_flag,sound_flag,pcsound_flag;
extern char game_over;
extern unsigned int display_page,draw_page;
extern volatile char key_flag[100];
extern int game_is_over;
//===========================================================================
long file_size(char *path){
long tmpl;
FILE *tmp_fp;

tmp_fp=fopen(path,"rb");
if(!tmp_fp) return -1;
fseek(tmp_fp,0l,SEEK_END);
tmpl=ftell(tmp_fp);
fclose(tmp_fp);
return tmpl;
}
//===========================================================================
int load_bg_data(void){
char s[21];
char str[21];

strcpy(s,"BPICS");
itoa(area,str,10);
strcat(s,str);

bg_pics=farmalloc(60460l);
if(!bg_pics) return 0;
if(res_read(s,bg_pics)<0) return 0;
return 1;
}
//===========================================================================
int load_sd_data(void){
char s[21];
char str[21];

strcpy(s,"SDAT");
itoa(area,str,10);
strcat(s,str);

if(!sd_data) sd_data=farmalloc(61440l);
if(!sd_data) return 0;
if(res_read(s,sd_data)<0) return 0;
return 1;
}
//===========================================================================
int load_objects(void){

if(res_read("OBJECTS",(char far *)objects)<0) return 0;
return 1;
}
//===========================================================================
int load_actor(int file,int num){
char s[21];
char rs[21];

itoa(num,s,10);
strcpy(rs,"ACTOR");
strcat(rs,s);
if(res_read(rs,tmp_buff)<0) return 0;
file=file;
return 1;
}
//===========================================================================
void help(void){


odin_speaks(2008,0);
}
//===========================================================================
void save_game(void){
int handle;
unsigned int total;
char buff[32];

if(game_is_over) return;
setup.area=area;
setup.game_over=game_over;
if(select_option(options_yesno,"Save Game?",0)!=1) return;

if(_dos_open(save_filename,O_RDONLY, &handle)!=0) return;
_dos_read(handle, buff,32,&total);
_dos_close(handle);

if(_dos_open(save_filename,O_WRONLY, &handle)!=0) return;
_dos_write(handle, buff,32,&total);
_dos_write(handle, &setup,sizeof(SETUP),&total);
_dos_write(handle, &thor_info,sizeof(THOR_INFO),&total);
_dos_write(handle, sd_data,61440u,&total);
_dos_close(handle);
odin_speaks(2009,0);
}
//===========================================================================
int load_game(int flag){
int handle;
unsigned int total;
char buff[32];

if(flag) if(select_option(options_yesno,"Load Game?",0)!=1) return 0;

if(_dos_open(save_filename,O_RDONLY, &handle)!=0) return 0;
_dos_read(handle, buff,32,&total);
_dos_read(handle, &setup,sizeof(SETUP),&total);
_dos_read(handle, &thor_info,sizeof(THOR_INFO),&total);
_dos_read(handle, sd_data,61440u,&total);
_dos_close(handle);

current_area=thor_info.last_screen;
area=setup.area;
if(area==0) area=1;

thor->x=(thor_info.last_icon%20)*16;
thor->y=((thor_info.last_icon/20)*16)-1;
if(thor->x<1) thor->x=1;
if(thor->y<0) thor->y=0;
thor->dir=thor_info.last_dir;
thor->last_dir=thor_info.last_dir;
thor->health=thor_info.last_health;
thor->num_moves=1;
thor->vunerable=60;
thor->show=60;
thor->speed_count=6;
load_new_thor();
display_health();
display_magic();
display_jewels();
display_keys();
display_item();
if(!music_flag) setup.music=0;
if(!sound_flag) setup.dig_sound=0;
if(setup.music==1){
  if(current_area==BOSS_LEVEL){
    if(flag) music_play(6,1);
  }
  else if(flag) music_play(level_type,1);
}
else{
  setup.music=1;
  music_pause();
  setup.music=0;
}
game_over=setup.game_over;
slow_mode=setup.speed;
return 1;
}
//==========================================================================
/*
long res_read(char *name,char far *buff){
int num,bytes;
size_t len;
size_t total;
char bf[256];
char far *p;
unsigned int clen;
unsigned int far *up;

if(!res_active) return RES_NOT_ACTIVE;
if(!res_fp) return RES_NOT_OPEN;

num=res_find_name(name);
if(num<0) return RES_CANT_FIND;

if(fseek(res_fp,res_header[num].offset,SEEK_SET)) return RES_CANT_SEEK;
len=(size_t) res_header[num].length;

total=0;
if(res_header[num].key) p=buff;
else p=lzss_buff;
while(total<len){
     if(((len-total) >255) && (len > 255)) bytes=fread(bf,1,256,res_fp);
     else bytes=fread(bf,1,len-total,res_fp);
     if(!bytes) break;
     total+=bytes;
     movedata(FP_SEG(bf),FP_OFF(bf),FP_SEG(p),FP_OFF(p),bytes);
     p+=bytes;
}
if(res_header[num].key) res_decode(buff,len,res_header[num].key);
else{
  p=lzss_buff;
  up=(unsigned int far *) p;
  clen=*up;
  p+=4;
  UnLZSS(p,buff,clen);
}
return res_header[num].length;
}
*/
//==========================================================================
int load_music(int num){

switch(num){
  case 0:
    res_read("SONG21",song);
    break;
  case 1:
    res_read("SONG22",song);
    break;
  case 2:
    res_read("SONG23",song);
    break;
  case 3:
    res_read("SONG24",song);
    break;
  case 4:
    res_read("SONG35",song);
    break;
  case 5:
    res_read("SONG25",song);
    break;
  case 6:
    res_read("WINSONG",song);
    break;
  case 7:
    res_read("BOSSSONG",song);
    break;
}
if(!song) return 0;
return 1;
}
