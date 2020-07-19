#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>

//#include <misc.h>
typedef struct _c_time{
       char  hour;
       char  min;
       char  sec;
       char  hun;
       int   year;
       char  month;
       char  day;
       char  dow;
} C_TIME;

extern union REGS in,out;
extern struct SREGS seg;
extern C_TIME ct;

extern char _month_days[];
extern char *_month_names[];
extern char *_day_names[];

//===========================================================================
int is_valid_time(int value){

if((value / 100) > 24) return 0;
if((value % 100) > 59) return 0;
if((value/100)==24 && (value%100)>0) return 0;
return 1;
}
//===========================================================================
int is_valid_date(int value){
int m,d;

m=value/100;
d=value%100;
if(m==0 && d==0) return 1;
if(m > 12 || m < 1) return 0;
if(d < 1 || d > _month_days[m]) return 0;
return 1;
}
//===========================================================================
void get_dos_time(C_TIME *ct){
static char l_min=-1;

in.h.ah=0x2c;
int86(0x21,&in,&out);
ct->hour=out.h.ch;
ct->min=out.h.cl;
ct->sec=out.h.dh;
ct->hun=out.h.dl;

if(ct->min == l_min) return;
l_min=ct->min;

in.h.ah=0x2a;
int86(0x21,&in,&out);
ct->year=out.x.cx;
ct->month=out.h.dh;
ct->day=out.h.dl;
ct->dow=out.h.al;
}
//===========================================================================
void set_dos_time(C_TIME *ct){

in.h.ch=ct->hour;
in.h.cl=ct->min;
in.h.dh=ct->sec;
in.h.dl=0;
in.h.ah=0x2d;
int86(0x21,&in,&out);

in.h.dh=ct->month;
in.h.dl=ct->day;
in.x.cx=ct->year;
in.h.ah=0x2b;
int86(0x21,&in,&out);
}
//===========================================================================
void strmid(char *str1,char *str2,int num,int pos){
int c;

c=0;
while(num--) str2[c++]=str1[pos++];
str2[c]=0;
}
//===========================================================================
void strright(char *str1,char *str2,int num){
int c,l;

l=strlen(str1);
c=num;
if(c>l) return;
num++;
while(num--) str2[c--]=str1[l--];
}
//===========================================================================
void strleft(char *str1,char *str2,int num){
int c;

c=0;
while(num--) str2[c]=str1[c++];
str2[c]=0;
}
/*=========================================================================*/
void format_date(int month,int day,int year,char *buff)
{

strcpy(buff,"00/00/00");
if(month>9) buff[0]=48+(month/10);
buff[1]=48+(month % 10);

if(day>9) buff[3]=48+(day/10);
buff[4]=48+(day % 10);

if(year==-1) buff[5]=0;
else{
  if(year>1999) year-=2000;
  else if(year>1899) year-=1900;
  if(year>9) buff[6]=48+(year/10);
  buff[7]=48+(year % 10);
}
}
/*=========================================================================*/
void format_time(int hour,int min,int sec,char *buff)
{

strcpy(buff,"00:00:00");
if(hour>9) buff[0]=48+(hour/10);
buff[1]=48+(hour % 10);

if(min>9) buff[3]=48+(min/10);
buff[4]=48+(min % 10);

if(sec==-1) buff[5]=0;
else{
  if(sec>9) buff[6]=48+(sec/10);
  buff[7]=48+(sec % 10);
}
}
/*=========================================================================*/
void tone(int pitch,int duration){

sound(pitch);
delay(duration);
nosound();
}
/*=========================================================================*/
int bit_is_on(int num,char *buff){
int x;
int byte;
char bit;

byte=(num/8);                                    // find byte
x=(num % 8);                                     // find bit number

bit=1;
while(x>0){bit*=2;x--;}                           // find bit mask

if(buff[byte] & bit) return 1;                   // test bit
return 0;
}
/*=========================================================================*/
void toggle_bit(int num,char *buff){
int x;
int byte;
char bit;

byte=(num/8);                                    // find byte
x=(num % 8);                                     // find bit number
bit=1;
while(x>0){bit*=2;x--;}                          // find bit mask
buff[byte]=buff[byte] ^ bit;                                 // toggle bit
}
/*=========================================================================*/
void change_bit(int num,char *buff,int mode){
int x;
int byte;
char bit;

byte=(num/8);                                    // find byte
x=(num % 8);                                     // find bit number
bit=1;
while(x>0){bit*=2;x--;}                          // find bit mask
if(mode) buff[byte] |= bit;                      // toggle bit
else buff[byte] &= (255-bit);
}
/*=========================================================================*/
int load_block(char *fname,long int offset,int bytes,char *buff){
int ret;
FILE *fp;

if(offset==-1) fp=fopen(fname,"rb");
else fp=fopen(fname,"r+");
if(!fp) return 0;

if(offset!=-1){
  ret=fseek(fp,offset,SEEK_SET);
  if(ret){fclose(fp);return 0;}
}
ret=fread(buff,bytes,1,fp);
fclose(fp);
if(ret==1) return 1;
return 0;
}
/*=========================================================================*/
int save_block(char *fname,long int offset,int bytes,char *buff){
int ret;
FILE *fp;

if(offset==-1) fp=fopen(fname,"wb");
else fp=fopen(fname,"r+");
if(!fp) return 0;

if(offset!=-1){
  ret=fseek(fp,offset,SEEK_SET);
  if(ret){fclose(fp);return 0;}
}
ret=fwrite(buff,bytes,1,fp);
fclose(fp);
if(ret==1) return 1;
return 0;
}
/*=========================================================================*/
int point_within(int x,int y,int x1,int y1,int x2,int y2){

if((x<x1) || (x>x2)) return 0;
if((y<y1) || (y>y2)) return 0;
return 1;
}
/*=========================================================================*/
void beep(void){
sound(1000);
delay(250);
nosound();
}




