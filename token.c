
#include"token.h"

extern char *key[];
void write_char(int byte,struct files *file)
{
	fputs("<span class=\"character\">",file->f_out);
	fputc(byte,file->f_out);
	int ch;
	while((ch=fgetc(file->f_in)) != '\'')
	{
		fputc(ch,file->f_out);
	}
	fputc(ch,file->f_out);
	fputs("</span>",file->f_out);
}

void write_string(int byte, struct files *file)
{
	fputs("<span class=\"string\">",file->f_out);
	fputc(byte,file->f_out);
	int ch;
	while((ch=fgetc(file->f_in)) != '\"')
	{
		switch(ch)
		{
			case '\\' :fputs("<span class=\"character\">",file->f_out);
				  fputc(ch,file->f_out);
				  ch=fgetc(file->f_in);
				  fputc(ch,file->f_out);
				  fputs("</span>",file->f_out);
				  break;
			case '%' :fputs("<span class=\"character\">",file->f_out);
				  fputc(ch,file->f_out);
				  ch=fgetc(file->f_in);
				 while (ch != 'd' && ch != 'i' && ch != 'u' && ch != 'o' && ch != 'x' && ch != 'X' && ch != 'f' && ch != 'F' && ch != 'e' && ch != 'E' && ch != 'g' &&
				       ch != 'G' && ch != 'a' && ch != 'A' && ch != 'c' && ch != 's' && ch != 'p' && ch != 'n' && ch != '%' && ch!='.' && ( ch<'0' && ch>'9')) 
				{
				  	fputc(ch,file->f_out);
					ch=fgetc(file->f_in);
				}
				ungetc(ch,file->f_in);
				fputs("</span>",file->f_out);
				break;
			default: fputc(ch,file->f_out);
		}
	}
	fputc(ch,file->f_out);
	fputs("</span>",file->f_out);
}

void write_singlec(int ch,char next, struct files *file)
{
	fputs("<span class=\"comment\">",file->f_out);
	fputc(ch,file->f_out);
	fputc(next,file->f_out);
	while((ch=fgetc(file->f_in)) != EOF && ch!='\n')
	{
		fputc(ch,file->f_out);
	}
	fputs("</span>",file->f_out);
	if(ch == '\n')
		fputc(ch,file->f_out);
}

void write_multic(int ch, char next,struct files *file)
{
	fputs("<span class=\"comment\">",file->f_out);
	fputc(ch,file->f_out);
	fputc(next,file->f_out);
	while((ch=fgetc(file->f_in)) != EOF )
	{
		if(ch == '*')
		{
			int ch1=fgetc(file->f_in);
			if(ch1=='/')
			{
				fputc(ch,file->f_out);
				fputc(ch1,file->f_out);
				fputs("</span>",file->f_out);	
				break;
			}
			if(ch1!=EOF)
			ungetc(ch1,file->f_in);
		}
		fputc(ch,file->f_out);
	}
}

void write_key(char *word,struct files *file)
{
	fputs("<span class=\"key\">",file->f_out);
	fputs(word,file->f_out);
	fputs("</span>",file->f_out);
}

void write_non_key(char *word,struct files *file)
{
	fputs("<span class=\"nonkey\">",file->f_out);
	fputs(word,file->f_out);
	fputs("</span>",file->f_out);
}

void write_directive(int ch,struct files *file)
{
	fputs("<span class=\"dir\">",file->f_out);
	while(ch != EOF && ch != '<' && ch!='"')
	{
		fputc(ch,file->f_out);
		ch=fgetc(file->f_in);
	}
	ungetc(ch,file->f_in);
	fputs("</span>",file->f_out);
}

void write_header(int ch, struct files *file)
{
    fputs("<span class=\"header\">", file->f_out);

    while (ch != EOF && ch != '>')
    {
        fputc(ch, file->f_out);
        ch = fgetc(file->f_in);
    }

    if (ch == '>')
        fputc(ch, file->f_out);

    fputs("</span>", file->f_out);
}

void write_num(int ch, struct files *file)
{
    fputs("<span class=\"number\">", file->f_out);

    while (ch >= '0' && ch <= '9')
    {
        fputc(ch, file->f_out);
        ch = fgetc(file->f_in);
    }

    if (ch != EOF)
        ungetc(ch, file->f_in);

    fputs("</span>", file->f_out);
}
