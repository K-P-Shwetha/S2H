#ifndef MAIN
#define MAIN

#define TRUE 1;
#define FLASE 0;
struct files
{
	char *input;
	char *output;
	FILE *f_in;
	FILE *f_out;
};
int number_flag;
int check_arg( char * , struct files *);
void open_files(struct files *file);
