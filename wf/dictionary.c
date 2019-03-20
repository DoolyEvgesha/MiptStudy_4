#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

void dict       (dict_fn * d, char * w)
{
    dct * v = d->dct;
    if(v->count == 0)
    {
        v->w = calloc(v->size, sizeof(wrd));
    }


    for(int i = 0; i < v->count + 1; i++)
    {
        if(strcmp(w, v->w->w) == 0)
        {
            v->w[i].num++;
            return;
        }
    }

    if(v->count >= v->size)
    {
        v->size += 100;
        v->w = realloc(v->w, v->size);
    }

    strcpy(v->w[v->count].w, v->w->w);
    v->w[v->count].num++;
    v->count++;
}

void print_dict (dict_fn * d)
{
    dct * v = d->dct;
    for(int i = 0; i < v->count; i++)
    {
        printf("%s : %d\n", v->w[i].w, v->w[i].num);
    }
}

int size(dict_fn * d)
{
    dct * v = d->dct;
    return v->size;
}

dict_fn * dict_create()
{
    dict_fn * d       = malloc(sizeof(dict_fn));
    dct * v           = calloc(1, sizeof(dct));

    d->dict           = dict;
    d->print_dict     = print_dict;
    d->size           = size;

    d->dct            = v;

    return d;
};