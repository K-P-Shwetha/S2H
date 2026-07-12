#include"main.h"
#include"token.h"
char *key[] =
{
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

int number_flag;
int main(int argc, char *argv[])
{
	struct files file;
	if(argc < 3)
	{
		printf("Not enough arguments\n");
		return -1;
	}
	if(argc == 4)
		number_flag=1;
	int ret=check_arg(argv,&file);
	if(ret == FALSE)
	{
		printf("File passed error\n");
		return -1;
	}
	else
		printf("Files passed\n");
	ret = s_2_h(&file);
}

int check_arg( char *argv[] , struct files *file )
{
	if(strstr(argv[1],".c") != NULL)
		file->input=argv[1];
	else
		return FALSE;
	if(strstr(argv[2],".html") !=NULL)
		file->output=argv[2];
	else
		file->output="dest.html";
	return TRUE;
}

int s_2_h(struct files *file)
{
	int ret=open_files(file);
	if(ret == FALSE)
	{
		printf("File open failed\n");
		return 0;
	}
	fputs("<!DOCTYPE html>\n",file->f_out);
	fputs("<html>\n",file->f_out);
	fputs("<title>HTML_PAGE</title>\n",file->f_out);
	fputs("<link rel=\"stylesheet\" href=\"style.css\">\n", file->f_out);
	fputs("</head>\n", file->f_out);
	fputs("<body>\n", file->f_out);
	fputs("<pre>\n", file->f_out);
	int ch=fgetc(file->f_in);
	while(ch != EOF)
	{
		switch(ch)
		{
			case '\'' : write_char(ch,file);
				   break;
			case '\"' : write_string(ch,file);
				   break;
			case '/' : char next=fgetc(file->f_in);
				   switch(next)
				   {
					case '/' : write_singlec(ch,next,file);
						   break;
					case '*' : write_multic(ch,next,file);
						   break;
					default : 
						   fputc(ch,file->f_out);
						   fputc(next,file->f_out);
				   }
				   break;
			case '0' ... '9' :write_num(ch,file);
			     		  break;
			case 'a' ... 'z' :
			case 'A' ... 'Z' :
			case '_' :
					  is_identifier(ch,file);
					  break;
			case '#' :write_directive(ch,file);
				  break;
			case '<' :write_header(ch,file);
				  break;
			default:
    				fputc(ch, file->f_out);
   				 break; 
		}
	}
	fputs("</pre>\n", file->f_out);
	fputs("</body>\n", file->f_out);
	fputs("</html>\n", file->f_out);
}

void is_identifier(int ch,struct files *file)
{
	char byte[50];int i=0;
	int ch1;int found=0;
	byte[i++]=ch;
	ch1=fgetc(file->f_in);
	while((ch1>='a' && ch1<='z') || (ch1>='A' && ch1<='Z') || (ch1>='0' && ch1<='9') || ch1=='_')
	{
		byte[i++]=ch1;
		ch1=fgetc(file->f_in);
	}
	ungetc(ch1,file->f_in);
	byte[i]=0;
	i=0;
	while(i!=32)
	{
		if(!strcmp(byte,key[i]))
		{
			write_key(byte,file);
			found=1;
			break;
		}	
		i++;
	}
	if(found == 0)
	{
		write_non_key(byte,file);
	}
}

int open_files(struct files *file)
{
	file->f_in=fopen(file->input,"r");
	if(file->f_in == NULL)
		return FALSE;
	file->f_out=fopen(file->output,"w");
	if(file->f_out == NULL)
		return FALSE;
}
