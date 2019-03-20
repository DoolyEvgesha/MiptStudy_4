#ifndef READER_H
#define READER_H

typedef struct  vars vars;
typedef struct  reader_fn reader_fn;

struct          reader_fn
{
    char * (*read_word) (vars * v);
    int    (*read_file) (vars * v, const char* path);
    int    (*read_stdin)(vars * v);
    int    (*close_file)(const char * path);

    void *  vars;
};

reader_fn *     reader_create();

#endif