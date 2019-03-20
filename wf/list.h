#ifndef LIST_H
#define LIST_H

typedef struct Node Node;
struct Node {
    int             count; //how many words were met
    wrd         *   data;  //the structure of words that is held
    struct Node *   next;
    struct Node *   prev;
};

#endif