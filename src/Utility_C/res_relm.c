#include <stdio.h>
#include <string.h>
#include <dos.h>

#include <res_man.h>
//==========================================================================
long res_read_element(char *name,char far *buff,long offset,long size){
int num,bytes;
size_t len;
size_t total;
char bf[256];
char far *p;

if(!res_active) return RES_NOT_ACTIVE;
if(!res_fp) return RES_NOT_OPEN;

num=res_find_name(name);
if(num<0) return RES_CANT_FIND;

if(size>res_header[num].length) return RES_CANT_SEEK;

if(fseek(res_fp,res_header[num].offset+offset,SEEK_SET)) return RES_CANT_SEEK;

len=(size_t) size;
total=0;
p=buff;
while(total<len){
     if(((len-total) >255) && (len > 255)) bytes=fread(bf,1,256,res_fp);
     else bytes=fread(bf,1,len-total,res_fp);
     if(!bytes) break;
     total+=bytes;
     movedata(FP_SEG(bf),FP_OFF(bf),FP_SEG(p),FP_OFF(p),bytes);
     p+=bytes;
}
return res_header[num].length;
}
