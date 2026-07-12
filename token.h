#ifndef TOKEN 
#define TOKEN 
#include"main.h"
void write_num(int , struct files *);
int check_arg( char ** , struct files *); 
void write_char(int ,struct files *); 
void write_string(int , struct files *); 
void write_singlec(int ,char , struct files *); 
void write_multic(int , char ,struct files *);
void write_key(char *,struct files *); 
void write_non_key(char *,struct files *); 
void write_directive(int ,struct files *); 
void write_header(int , struct files *); 
#endif
