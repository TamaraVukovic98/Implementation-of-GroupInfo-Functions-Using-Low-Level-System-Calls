#ifndef _MYSTRING_H
#define _MYSTRING_H

int mystrlen(char *s);

int mystrcmp(char *s, char *t);

int prefix(char *s, char *prefix);

int infix(char *s, char *infix);

/*int infixmod(char *s, char *infix);*/

int mystrchr(char *s, char c);

int mystrrchr(char *s, char c);

char* mystrcat(char *s, const char *append);

char* mystrcpy(char *to, const char *from);

char* mystrtok(char *string, char *delim);

void tostring(char str[], int num);

#endif
