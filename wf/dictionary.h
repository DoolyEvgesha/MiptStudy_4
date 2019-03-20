#ifndef DICT_H
#define DICT_H

#define WRD_SIZE 20

typedef struct wrd
{
    char    w[WRD_SIZE];
    int     num;        //how many times did we came across the word
}wrd;

typedef struct dct
{
    wrd *   w;          //array of words single time
    int     count;      //how many words were met
    int     size;       //how many words can the dictionary hold (capacity)
}dct;

typedef struct  dict_fn dict_fn;
struct          dict_fn
{
    void    (*dict)       (dict_fn * d, char * w);
    void    (*print_dict) (dict_fn * d);
    int     (*size)       (dict_fn * d);
    void *  dct;
};

dict_fn *   dict_create   (void);

#endif