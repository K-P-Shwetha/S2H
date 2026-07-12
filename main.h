#ifndef MAIN
#define MAIN

#include<stdio.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
struct files
{
	char *input;
	char *output;
	FILE *f_in;
	FILE *f_out;
};
extern char *key[];
void is_identifier(int ,struct files *);
int s_2_h(struct files *);
int open_files(struct files *);
#endif
