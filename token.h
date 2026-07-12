#ifndef TOKEN
#define TOKEN
char *key[] =
{
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

void is_identifier(int ,struct files *);
int s_2_h(struct files *);
void write_char(int ,struct files *);
void write_string(int , struct files *);
void write_singlec(int ,char , struct files *);
void write_multic(int , char ,struct files *);
void write_key(char *,struct files *);
void write_non_key(char *,struct files *);
void write_direcive(int ,struct files *);
void write_header(int , struct files *);
void write_num(int , struct files *);
