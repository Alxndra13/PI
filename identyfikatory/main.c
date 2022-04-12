#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NEWLINE '\n'

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define IN_STRING 4
#define IN_ID 8

#define MAX_ID_LEN 64
#define MAX_IDS 1024

int index_cmp(const void*, const void*);
int cmp(const void*, const void*);

char tab[MAX_IDS][MAX_ID_LEN];

char *keywords[] = {
        "auto", "break", "case", "char",
        "const", "continue", "default", "do",
        "double", "else", "enum", "extern",
        "float", "for", "goto", "if",
        "int", "long", "register", "return",
        "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
};

int find_idents()
{
    char new[300][130];
    char line[128];
    int i,j,indeks = 0;
    int st = 0,len;
    int flag = 0,flag1;

    while(fgets(line, 128, stdin))
    {
        i = 0;
        while(line[i] != NEWLINE)
        {
            flag = 0;
            if(st == 1)
                if(line[i-1]=='*' && line[i] == '/')
                    st = 0;
            if(st == 2)
            {
                if(line[i] == '\"')
                {
                    if(line[i-1] == '\\')
                    {
                        if(line[i-2] == '\\')
                        {
                            st = 0;
                            flag = 1;
                        }
                    }
                    else
                    {
                        st = 0;
                        flag = 1;
                    }
                }
            }
            if(st == 3)
                if(line[i] == '\'')
                {
                    if(line[i-1]=='\\')
                    {
                        if (line[i - 2] == '\\')
                        {
                            st = 0;
                            flag = 1;
                        }
                    }
                    else
                    {
                        st = 0;
                        flag = 1;
                    }
                }
            if(st == 0)
            {
                if(line[i] =='/' && line[i+1] =='/')
                    line[i+1]=NEWLINE;
                if(line[i] =='/' && line[i+1] == '*')
                {
                    st = 1;
                    if(line[i+1] != NEWLINE)i++;
                }
                if(line[i] == '"' && flag == 0)
                    st = 2;
                if(line[i]== '\'' && flag ==0)
                    st = 3;
                if(((((int)line[i+1] >= 65 && (int)line[i+1] <= 90) || ((int)line[i+1] >= 97 && (int)line[i+1] <= 122))||(int)line[i+1]==95) && st == 0)
                {
                    if((((int)line[i] >= 65 && (int)line[i] <= 90) || ((int)line[i] >= 97 && (int)line[i] <= 122))||(int)line[i]==95)
                    {}
                    else
                    {
                        j = i + 2;
                        len = 1;
                        while(((((int)line[j] >= 65 && (int)line[j] <= 90) || ((int)line[j] >= 97 && (int)line[j] <= 122)) || ((int)line[j] >= 48 && (int)line[j] <= 57)) || (int)line[j]==95)
                        {
                            len++;
                            j++;
                        }
                        j = i + 1;
                        for(int k = 0; k <= 31; k++)
                        {
                            flag1 = 0;
                            for(int l = 0; l < len; l++)
                            {
                                if(keywords[k][l] != line[j+l])flag1=1;

                            }
                            if(flag1 == 0)
                            {
                                if(((((int)keywords[k][len]>=65&&(int)keywords[k][len]<=90)||((int)keywords[k][len]>=97&&(int)keywords[k][len]<=122))||((int)keywords[k][len]>=48&&(int)keywords[k][len]<=57))||(int)keywords[k][len]==95)
                                    flag1 = 1;
                                else break;
                            }

                        }
                        if(flag1 == 1)
                        {
                            for(int k = 0; k < indeks; k++)
                            {
                                flag1 = 0;
                                for(int l = 0; l < len;l++)
                                    if(new[k][l] != line[j+l]) flag1=1;
                                if(flag1 == 0)
                                {
                                    if(((((int)new[k][len]>=65&&(int)new[k][len]<=90)||((int)new[k][len]>=97&&(int)new[k][len]<=122))||((int)new[k][len]>=48&&(int)new[k][len]<=57))||(int)new[k][len]==95)
                                        flag1 = 1;
                                    else break;
                                }

                            }
                        }
                        if(flag1 == 1)
                        {
                            for(int k = 0; k < len; k++)
                                new[indeks][k] = line[j+k];
                            indeks ++;
                        }

                    }
                }
                if(i == 0 && (((((int)line[i] >= 65 && (int)line[i] <= 90) || ((int)line[i] >= 97 && (int)line[i] <= 122))) || (int)line[i]==95))
                {
                    j = i + 1;
                    len = 1;
                    while(((((int)line[j] >= 65 && (int)line[j] <= 90) || ((int)line[j] >= 97 && (int)line[j] <= 122)) || ((int)line[j] >= 48 && (int)line[j] <= 57)) || (int)line[j]==95)
                    {
                        len++;
                        j++;
                    }
                    j = i;
                    for(int k = 0; k <= 31; k++)
                    {
                        flag1 = 0;
                        for(int l = 0; l < len;l++)
                            if(keywords[k][l] != line[j+l])flag1=1;
                        if(flag1 == 0)
                        {
                            if(((((int)keywords[k][len]>=65&&(int)keywords[k][len]<=90)||((int)keywords[k][len]>=97&&(int)keywords[k][len]<=122))||((int)keywords[k][len]>=48&&(int)keywords[k][len]<=57))||(int)keywords[k][len]==95)
                                flag1 = 1;
                            else break;
                        }
                    }
                    if(flag1 == 1)
                    {
                        for(int k = 0; k < indeks; k++)
                        {
                            flag1 = 0;
                            for(int l = 0; l < len;l++)
                                if(new[k][l] != line[j+l])flag1=1;
                            if(flag1 == 0)
                            {
                                if(((((int)new[k][len]>=65&&(int)new[k][len]<=90)||((int)new[k][len]>=97&&(int)new[k][len]<=122))||((int)new[k][len]>=48&&(int)new[k][len]<=57))||(int)new[k][len]==95)
                                    flag1 = 1;
                                else break;
                            }

                        }
                    }
                    if(flag1 == 1)
                    {
                        for(int k = 0; k < len; k++)
                            new[indeks][k] = line[j+k];
                        indeks ++;
                    }
                }

            }
            i++;
        }
    }
    return indeks;

}

int cmp(const void* first_arg, const void* second_arg) {
    char *a = *(char**)first_arg;
    char *b = *(char**)second_arg;
    return strcmp(a, b);
}

int index_cmp(const void* first_arg, const void* second_arg) {
    int a = *(int*)first_arg;
    int b = *(int*)second_arg;
    return strcmp(tab[a], tab[b]);
}

int main(void) {
    printf("%d\n", find_idents());
    return 0;
}