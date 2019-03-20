#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "reader.h"

typedef struct vars
{
    int size;
    FILE* fd;
    char* w;
}vars;

static void concat(vars * v, int c)
{
    v->size += 1;
    v->w = realloc(v->w, v->size);
    v->w[v->size-2] = c;
    v->w[v->size-1] = '\0';
}

char * read_word(vars * v)
{
    v->size = 1;
    int c = 0;
    v->w = (char*)calloc(v->size, 1);

    do{
        c = fgetc(v->fd);
        if(c == EOF) return NULL;
    } while(!isalpha(c));

    do{
        concat(v, c);
        c = fgetc(v->fd);
        if(c == EOF) break;
    }while(isalpha(c));

    return v->w;
}

int read_file(vars * v, const char* path)
{
    v->fd =  fopen(path, "r");
}

int close_file(const char * path) // FILE * path
{
    fclose(path); // Where to close the file
}

int read_stdin(vars * v)
{
    v->fd = stdin;
}


reader_fn * reader_create()
{
    vars * v        = calloc(1, sizeof(vars));
    reader_fn * r   = malloc(sizeof(reader_fn));

    //==
    //p = malloc(sizeof(vars)+ sizeof(reader));
    //r = (reader*)p;
    //v = (vars*)((char*)p + sizeof(reader));
    //==

    r->read_word    = read_word;
    r->read_file    = read_file;

    v->fd           = stdin;

    r->vars         = calloc(1, sizeof(vars));

    return r;
};
