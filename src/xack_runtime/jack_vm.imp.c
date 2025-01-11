#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* dupstr(char* str)
{
    int len = strlen(str);
    char* newstr = malloc(len);
    strcpy(newstr, str);
    return newstr;
}

char* addstr(char* str1, char* str2)
{
    int len = strlen(str1) + strlen(str2);
    char* newstr = malloc(len);
    strcpy(newstr, str1);
    strcat(newstr, str2);
    return newstr;
}

