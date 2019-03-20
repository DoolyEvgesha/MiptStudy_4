#include <stdio.h>
#include "reader.h"
#include "dictionary.h"
#include "list.h"

int main(int argc, char * argv[]){
    dict_fn     * d = LIST();
    reader_fn   * r = reader_create();
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            char * w;
            r->read_file(r->vars, argv[i]);
            while((w = r->read_word(r->vars)) != 0)
                d->dict(d, w);

            r->close_file(argv[i]);//here???
        }
    }
    else {
        char *w;
        r->read_stdin(r->vars);
        while((w = r->read_word(r->vars)) != 0)
            d->dict(d, w);
    }
    d->print_dict(d);
    return 0;
}