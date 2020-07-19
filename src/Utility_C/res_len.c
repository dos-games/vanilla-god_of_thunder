#include <stdio.h>

#include <res_man.h>
//==========================================================================
long res_length(char *name){
int num;

num=res_find_name(name);
if(num<0) return (long) RES_ENTRY_NOT_FOUND;
return res_header[num].length;
}
//==========================================================================
long res_original_size(char *name){
int num;

num=res_find_name(name);
if(num<0) return (long) RES_ENTRY_NOT_FOUND;
return res_header[num].original_size;
}
