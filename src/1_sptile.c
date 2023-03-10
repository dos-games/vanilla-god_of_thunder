// THOR - The God of Thunder
//Source code released to the public domain on March 27th, 2020.

#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>

#include <1_define.h>
#include <1_proto.h>
//===========================================================================
extern int new_level,current_level,new_level_tile;
extern int warp_flag;
extern LEVEL scrn;
extern ACTOR actor[MAX_ACTORS];
extern ACTOR *thor;
extern char far *bg_pics;
extern THOR_INFO thor_info;
extern int thor_x1,thor_y1,thor_x2,thor_y2,thor_real_y1;
extern unsigned int display_page,draw_page;
extern int cash1_inform,cash2_inform,door_inform;
extern char diag;
extern char warp_scroll;
extern int exit_flag;
extern char end_tile;
//===========================================================================
int open_door1(int y,int x);
int cash_door1(int y,int x,int amount);
//===========================================================================
int special_tile_thor(int x,int y,int icon){
int cx,cy,f;

f=0;
switch(icon){
      case 201:
           return open_door1(x,y);
      case 202:
           if(thor->x>300) end_tile=1;     //ending bridge
           return 1;
      case 203:
           return 0;
      case 204:
           return 0;
      case 205:
           if(!diag && thor->dir!=1) return 1;
           break;
      case 206:
           if(!diag && thor->dir!=0) return 1;
           break;
      case 207:
           if(!diag && thor->dir!=3) return 1;
           break;
      case 208:
           if(!diag && thor->dir!=2) return 1;
           break;
      case 209:
           return cash_door1(x,y,10);
      case 210:
           return cash_door1(x,y,100);
      case 211:
//           if(thor->center_x=y && thor->center_y==x){
             place_tile(y,x,79);
             exit_flag=2;
//           }
           return 1;
      case 212:
      case 213:
           return 0;
      case 214:        //teleport tiles
      case 215:
      case 216:
      case 217:
           return 0;
      case 218:
      case 219:
           f=1;
      case 220:     //hole tiles
      case 221:
      case 222:
      case 223:
      case 224:
      case 225:
      case 226:
      case 227:
      case 228:
      case 229:
//           mx=(thor->x+6)%16;
//           my=(thor->y+12)%16;
//           if(mx<4 || mx>12) return 1;
//           if(my<4) return 1;

           cx=(thor_x1+7)/16;
           cy=(thor_real_y1+8)/16;
           if(scrn.icon[cy][cx]==icon){
             thor->vunerable=STAMINA;
             if(icon<224 && icon>219) play_sound(FALL,0);
             new_level=scrn.new_level[icon-220+(f*6)];
             warp_scroll=0;
             if(new_level>119){
               warp_scroll=1;
               new_level-=128;
             }
             new_level_tile=scrn.new_level_loc[icon-220+(f*6)];
             warp_flag=1;
             if(warp_scroll){
               if(thor->dir==0) thor->y=175;
               else if(thor->dir==1) thor->y=0;
               else if(thor->dir==2) thor->x=304;
               else if(thor->dir==3) thor->x=0;
             }
             else{
               thor->x=(new_level_tile%20)*16;
               thor->y=((new_level_tile/20)*16)-2;
             }
             thor->last_x[0]=thor->x;
             thor->last_x[1]=thor->x;
             thor->last_y[0]=thor->y;
             thor->last_y[1]=thor->y;
             return 0;
           }
           return 1;
}
return 0;
}
//===========================================================================
int special_tile(ACTOR *actr,int x,int y,int icon){

switch(icon){
      case 201:
      case 202:
      case 203:
      case 204:
           break;
      case 205:
//           if(actr->last_dir==0 || actr->flying) return 1;
//           break;
      case 206:
      case 207:
      case 208:
           return 1;
      case 209:
      case 210:
           return 0;
      case 214:
      case 215:
      case 216:
      case 217:
           return 0;
      case 224:
      case 225:
      case 226:
      case 227:
           if(!actr->flying) return 0;
           return 1;
      default:
           x=x;
           y=y;
//           if(actr->flying) return 1;
           return 1;

}
return 0;
}
//===========================================================================
void erase_door(int x,int y){

play_sound(DOOR,0);
scrn.icon[y][x]=scrn.bg_color;
x=x<<4;
y=y<<4;
xfput(x,y,PAGE2,(char far *) (bg_pics+(scrn.bg_color*262)));
xcopyd2d(x,y,x+16,y+16,x,y,PAGE2,draw_page,320,320);
xcopyd2d(x,y,x+16,y+16,x,y,PAGE2,display_page,320,320);
}
//===========================================================================
int open_door1(int y,int x){

if(thor_info.keys>0){
  erase_door(x,y);
  thor_info.keys--;
  display_keys();
  return 1;
}
else{
  if(!door_inform){
    odin_speaks(2003,0);
    door_inform=1;
  }
}
return 0;
}
//===========================================================================
int cash_door1(int y,int x,int amount){

if(thor_info.jewels>=amount){
  erase_door(x,y);
  thor_info.jewels-=amount;
  display_jewels();
  return 1;
}
else{
  if(amount==10 && !cash1_inform){
    odin_speaks(2005,0);
    cash1_inform=1;
  }
  if(amount==100 && !cash2_inform){
    odin_speaks(2004,0);
    cash2_inform=1;
  }
}
return 0;
}


